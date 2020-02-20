// Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include "../detail/prologue.hpp"

#include <tuple>
#include <type_traits>
#include "../detail/index_sequence.hpp"
#include "../detail/tuple_utility.hpp"
#include "is_shape.hpp"
#include "shape_append.hpp"
#include "shape_element.hpp"
#include "shape_size.hpp"


COORD_NAMESPACE_OPEN_BRACE

namespace detail
{
namespace common_shape_detail
{


// given a list of ReboundTypes..., try to rebind Tuple to those types
// in the case that Tuple can't be rebound, instantiate FallbackTupleTemplate<ReboundTypes...> instead
template<class Tuple, template<class...> class FallbackTupleTemplate, class... ReboundTypes>
struct tuple_rebind_or
{
  private:
    template<class Tuple_,
             class Result = tu::tuple_rebind_t<Tuple_, ReboundTypes...>
            >
    static Result rebind(int);

    template<class>
    static FallbackTupleTemplate<ReboundTypes...> rebind(...);

  public:
    using type = decltype(rebind<Tuple>(0));
};


template<class Tuple, template<class...> class FallbackTupleTemplate, class... ReboundTypes>
using tuple_rebind_or_t = typename tuple_rebind_or<Tuple,FallbackTupleTemplate,ReboundTypes...>::type;


template<class T1, class T2>
using common_type_t = typename std::common_type<T1,T2>::type;


// because the implementation of common_shape2 is recursive, we introduce a forward declaration so it may call itself.
template<class Shape1, class Shape2>
struct common_shape2;

template<class Shape1, class Shape2>
using common_shape2_t = typename common_shape2<Shape1,Shape2>::type;


// in the following, we implement the type trait common_shape2 using constexpr functions so that we can use COORD_REQUIRES easily

// First, if the two Shapes are identical (case 0), there is nothing to do.
//
// To create a Shape type which could accomodate either of two other Shape types A or B, the idea is to create a
// Shape "wide" enough to hold either A or B.
// 
// We do this by appending dimensions to the narrower of the two Shapes (cases 1 & 2). 
// When both Shapes have the same number of dimensions (case 3), we recurse into the elements of those dimensions, which are themselves Shapes.
// We terminate the recursion (at case 4) when we compare two scalars to each other.

// case 0: The two Shapes are identical
template<class Shape>
constexpr Shape common_shape_impl(Shape, Shape)
{
  return Shape();
}

// case 1: Shape1 has fewer elements than Shape2
template<class Shape1, class Shape2,
         COORD_REQUIRES(
           shape_size<Shape1>::value < shape_size<Shape2>::value
         )>
constexpr
common_shape2_t<
  shape_append_t<Shape1, shape_element_t<shape_size<Shape1>::value, Shape2>>,
  Shape2
>
  common_shape_impl(Shape1, Shape2)
{
  // append a dimension to the narrower of the two shapes, Shape1
  using type_to_append = shape_element_t<shape_size<Shape1>::value, Shape2>;
  using widened_shape = shape_append_t<Shape1, type_to_append>;

  // recurse
  return common_shape2_t<widened_shape, Shape2>();
};


// case 2: Shape2 has fewer elements than Shape1
template<class Shape1, class Shape2,
         COORD_REQUIRES(
           shape_size<Shape1>::value > shape_size<Shape2>::value
         )>
constexpr
common_shape2_t<
  Shape1,
  shape_append_t<Shape2, shape_element_t<shape_size<Shape2>::value, Shape1>>
>
  common_shape_impl(Shape1, Shape2)
{
  // append a dimension to the narrower of the two shapes, Shape2
  using type_to_append = shape_element_t<shape_size<Shape2>::value, Shape1>;
  using widened_shape = shape_append_t<Shape2, type_to_append>;

  // recurse
  return common_shape2_t<Shape1, widened_shape>();
}


// case 3: Shape1 and Shape2 have the same number of elements, and this number is greater than one
template<class Shape1, class Shape2,
         class Indices>
struct common_shape_case_3_result;

template<class Shape1, class Shape2, size_t... Indices>
struct common_shape_case_3_result<Shape1, Shape2, index_sequence<Indices...>>
{
  // when it's possible to tuple_rebind Shape1, do this to produce the resulting Shape type
  // otherwise, use std::tuple as the resulting tuple type
  // XXX the user might prefer to use something other than std::tuple
  //     in that case, maybe this should accept a template template parameter FallbackTupleTemplate<Types...> or something like that
  using type = tuple_rebind_or_t<
    Shape1,
    std::tuple,
    common_shape2_t<                       // the resulting Shape is composed of the the common shape of Shape1's & Shape2's constituent elements
      shape_element_t<Indices,Shape1>,
      shape_element_t<Indices,Shape2>
    >...
  >;
};

template<class Shape1, class Shape2>
using common_shape_case_3_result_t = typename common_shape_case_3_result<Shape1, Shape2, make_index_sequence<shape_size<Shape1>::value>>::type;


template<class Shape1, class Shape2,
         COORD_REQUIRES(
           shape_size<Shape1>::value != 1 and
           shape_size<Shape2>::value != 1
         ),
         COORD_REQUIRES(
           shape_size<Shape1>::value == shape_size<Shape2>::value
         )>
constexpr common_shape_case_3_result_t<Shape1,Shape2>
  common_shape_impl(Shape1, Shape2)
{
  return common_shape_case_3_result_t<Shape1,Shape2>();
}


// case 4: both Shape1 & Shape2 both have a single element and those elements' types are integral
template<class Shape1, class Shape2,
         COORD_REQUIRES(
           shape_size<Shape1>::value == 1 &&
           shape_size<Shape2>::value == 1
         ),
         COORD_REQUIRES(
           std::is_integral<shape_element_t<0,Shape1>>::value &&
           std::is_integral<shape_element_t<0,Shape2>>::value
         )>
constexpr common_type_t<shape_element_t<0,Shape1>,shape_element_t<0,Shape2>>
  common_shape_impl(Shape1, Shape2)
{
  using element1 = shape_element_t<0,Shape1>;
  using element2 = shape_element_t<0,Shape2>;

  // return the common type of these two scalars
  return common_type_t<element1,element2>();
}


template<class Shape1, class Shape2>
struct common_shape2
{
  using type = decltype(common_shape_detail::common_shape_impl(std::declval<Shape1>(), std::declval<Shape2>()));
};


} // end common_shape_detail
} // end detail


// common_shape is a type trait which, given one or more possibly different Shapes, returns
// a Shape with dimensions sufficient to represent any of the Shapes.
// XXX we should require is_shape of all of these
template<class Shape, class... Shapes>
struct common_shape;

template<class Shape, class... Shapes>
using common_shape_t = typename common_shape<Shape,Shapes...>::type;


// the implementation of common_shape is recursive
// this is the recursive case
template<class Shape1, class Shape2, class... Shapes>
struct common_shape<Shape1, Shape2, Shapes...>
{
  using type = common_shape_t<
    Shape1,
    common_shape_t<Shape2, Shapes...>
  >;
};

// base case 1: a single Shape
template<class Shape>
struct common_shape<Shape>
{
  using type = Shape;
};

// base case 2: two Shapes
template<class Shape1, class Shape2>
struct common_shape<Shape1, Shape2>
{
  // with two Shapes, we lower onto the two Shape implementation inside common_shape_detail
  using type = detail::common_shape_detail::common_shape2_t<Shape1,Shape2>;
};


COORD_NAMESPACE_CLOSE_BRACE


#include "../detail/epilogue.hpp"

