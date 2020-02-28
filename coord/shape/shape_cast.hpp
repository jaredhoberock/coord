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

#include <utility>
#include <type_traits>
#include "detail/first_shape_element.hpp"
#include "detail/last_shape_element.hpp"
#include "detail/shape_append.hpp"
#include "detail/shape_first.hpp"
#include "detail/shape_last.hpp"
#include "detail/shape_truncate.hpp"
#include "is_shape.hpp"
#include "make_shape.hpp"
#include "shape_size.hpp"
#include "../detail/tuple_utility.hpp"


COORD_NAMESPACE_OPEN_BRACE


// Scalar -> Scalar (terminal case)
template<class ToShape, class FromShape,
         COORD_REQUIRES(shape_size<ToShape>::value == 1),
         COORD_REQUIRES(shape_size<FromShape>::value == 1)
        >
COORD_ANNOTATION
ToShape shape_cast(const FromShape& shape)
{
  // be sure to explicitly cast the first element of FromShape to the type of ToShape's first element
  // otherwise, the compiler complains about narrowing conversions inside of make_shape below
  using to_element_type = detail::first_shape_element_t<ToShape>;

  return make_shape<ToShape>(static_cast<to_element_type>(detail::shape_first(shape)));
}


// shape_cast is recursive and has various cases
// declare the cases here before their definitions
namespace detail
{
namespace shape_cast_detail
{


template<class ToShape, class FromShape>
COORD_ANNOTATION
ToShape shape_crosscast(const FromShape& shape);


template<class ToShape, class FromShape>
COORD_ANNOTATION
ToShape shape_downcast(const FromShape& shape);


template<class ToShape, class FromShape>
COORD_ANNOTATION
ToShape shape_upcast(const FromShape& shape);


} // end shape_cast_detail
} // end detail


// case for casting two shapes of equal size (crosscast)
template<class ToShape, class FromShape,
         COORD_REQUIRES(shape_size<ToShape>::value == shape_size<FromShape>::value),
         COORD_REQUIRES(shape_size<ToShape>::value > 1)
        >
COORD_ANNOTATION
ToShape shape_cast(const FromShape& shape)
{
  return detail::shape_cast_detail::shape_crosscast<ToShape>(shape);
}


// case for casting a shape to a lower-dimensional shape (downcast)
template<class ToShape, class FromShape,
         COORD_REQUIRES(shape_size<ToShape>::value < shape_size<FromShape>::value)
        >
COORD_ANNOTATION
ToShape shape_cast(const FromShape& shape)
{
  return detail::shape_cast_detail::shape_downcast<ToShape>(shape);
}


// case for casting a shape to a higher-dimensional shape (upcast)
template<class ToShape, class FromShape,
         COORD_REQUIRES(shape_size<ToShape>::value > shape_size<FromShape>::value)
        >
COORD_ANNOTATION
ToShape shape_cast(const FromShape& shape)
{
  return detail::shape_cast_detail::shape_upcast<ToShape>(shape);
}


namespace detail
{
namespace shape_cast_detail
{


template<class Shape>
struct shape_factory
{
  template<class... Args>
  COORD_ANNOTATION
  Shape operator()(Args&&... args) const
  {
    return COORD_NAMESPACE::make_shape<Shape>(std::forward<Args>(args)...);
  }
};


// reduces the dimensionality of shape by eliding the last dimension
// and multiplying the second-to-last dimension by the last
// this function does not return single element tuples -- it unwraps them into integral types
template<class Shape,
         COORD_REQUIRES(is_shape<Shape>::value),
         COORD_REQUIRES(shape_size<Shape>::value > 1)
        >
COORD_ANNOTATION
detail::shape_truncate_t<Shape> project_shape(const Shape& shape)
{
  auto last = detail::shape_last(shape);

  detail::shape_truncate_t<Shape> result = detail::shape_truncate(shape);

  // XXX this multiplication assumes that both shape_last(result) and last are scalars
  //     but combining dimensions needs to be another recursive process
  //     the "innermost, rightmost" element of shape_last(result) should receive this multiplication, shouldn't it?
  //
  // XXX this should look more like this:
  //
  //         innermost_rightmost_element(result) *= domain_size(last);
  //
  // In other words, we traverse the result to the right, and descend, and continue this process until we arrive at a scalar
  // then, we multiply this scalar by the size of the domain spanned by last
  detail::shape_last(result) *= last;

  return result;
}


// increases the dimensionality of x
// by appending a dimension (and setting it to 1)
template<class Shape,
         COORD_REQUIRES(is_shape<Shape>::value)
        >
COORD_ANNOTATION
detail::shape_append_t<Shape, detail::last_shape_element_t<Shape>> lift_shape(const Shape& shape)
{
  return detail::shape_append(shape, detail::last_shape_element_t<Shape>{1});
}


struct shape_cast_functor
{
  template<class ToShape, class FromShape>
  COORD_ANNOTATION
  auto operator()(const ToShape&, const FromShape& x)
    -> decltype(
         shape_cast<ToShape>(x)
       )
  {
    return shape_cast<ToShape>(x);
  }
};


template<class ToShape, class FromShape>
COORD_ANNOTATION
ToShape shape_crosscast(const FromShape& x)
{
  // XXX rename tuple_map_with_make to tuple_map_with_factory
  return detail::tu::tuple_map_with_make(detail::shape_cast_detail::shape_cast_functor{}, detail::shape_cast_detail::shape_factory<ToShape>{}, ToShape{}, x);
}


template<class ToShape, class FromShape>
COORD_ANNOTATION
ToShape shape_downcast(const FromShape& x)
{
  return COORD_NAMESPACE::shape_cast<ToShape>(project_shape(x));
}


template<class ToShape, class FromShape>
COORD_ANNOTATION
ToShape shape_upcast(const FromShape& x)
{
  return COORD_NAMESPACE::shape_cast<ToShape>(detail::shape_cast_detail::lift_shape(x));
}


} // end shape_cast_detail
} // end detail


COORD_NAMESPACE_CLOSE_BRACE

#include "../detail/epilogue.hpp"

