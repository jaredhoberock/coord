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

#include "../../detail/prologue.hpp"

#include "../../detail/index_sequence.hpp"
#include "../../detail/tuple_utility.hpp"
#include "../is_shape.hpp"
#include "../shape_size.hpp"
#include "../shape_element.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{
namespace shape_truncate_detail
{


// this metafunction truncates the last element from the end of Shape and the result is an instantiation of TupleTemplate
// XXX maybe the result should be ResultTemplate
template<class Indices, class Shape, template<class...> class ResultTemplate>
struct instantiate_template_with_truncated_shape_elements;


// to truncate a Shape, list the Shape's elements except for the last one, and use this list to instantiate the given template
template<std::size_t... Indices, class Shape, template<class...> class ResultTemplate>
struct instantiate_template_with_truncated_shape_elements<index_sequence<Indices...>, Shape, ResultTemplate>
{
  using type = ResultTemplate<shape_element_t<Indices,Shape>...>;
};


template<class Shape, template<class...> class ResultTemplate>
using instantiate_template_with_truncated_shape_elements_t = typename instantiate_template_with_truncated_shape_elements<
  make_index_sequence<shape_size<Shape>::value - 1>, // drop the final element
  Shape,
  ResultTemplate
>::type;


// when truncating a Shape of size 2, return an untupled scalar
template<class Shape>
struct default_small_shape_truncate_result
{
  template<class T>
  using type = T;
};


// in general, just use std::tuple
template<class Shape>
struct default_large_shape_truncate_result
{
  template<class... Types>
  using type = std::tuple<Types...>;
};


// when truncating an Array, just truncate the Array's length by 1
template<template<class, std::size_t> class ArrayLike, std::size_t n, class T>
struct default_large_shape_truncate_result<ArrayLike<T,n>>
{
  template<class...>
  using type = ArrayLike<T,n-1>;
};


// when truncating a Tuple-like template, rebind the Tuple-like template itself
template<template<class...> class Tuple, class... TupleElements>
struct default_large_shape_truncate_result<Tuple<TupleElements...>>
{
  template<class... Types>
  using type = Tuple<Types...>;
};


// this trait defines a nested template named result
// which is used for the instantiation of the result of shape_truncate_t
template<class Shape, class Enabled = void>
struct default_shape_truncate_result;


// for Shapes whose size is 2, use default_small_shape_truncate_result
template<class Shape>
struct default_shape_truncate_result<Shape, typename std::enable_if<shape_size<Shape>::value == 2>::type> : default_small_shape_truncate_result<Shape> {};


// for Shapes whose size is > 2, use default_large_shape_truncate_result
template<class Shape>
struct default_shape_truncate_result<Shape, typename std::enable_if<(shape_size<Shape>::value > 2)>::type> : default_large_shape_truncate_result<Shape> {};


} // end shape_truncate_detail


template<class Shape, template<class...> class ResultTemplate = detail::shape_truncate_detail::default_shape_truncate_result<Shape>::template type>
using shape_truncate_t = detail::shape_truncate_detail::instantiate_template_with_truncated_shape_elements_t<Shape, ResultTemplate>;


namespace shape_truncate_detail
{


template<class Shape, std::size_t... Indices>
COORD_ANNOTATION
shape_truncate_t<Shape> shape_truncate_impl(const Shape& shape, index_sequence<Indices...>)
{
  return shape_truncate_t<Shape>{tu::get<Indices>(shape)...};
}


} // end shape_truncate_detail


template<class Shape,
         COORD_REQUIRES(is_shape<Shape>::value),
         COORD_REQUIRES(shape_size<Shape>::value > 1)
        >
COORD_ANNOTATION
shape_truncate_t<Shape> shape_truncate(const Shape& shape)
{
  return detail::shape_truncate_detail::shape_truncate_impl(shape, COORD_NAMESPACE::detail::make_index_sequence<shape_size<Shape>::value - 1>{});
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE

#include "../../detail/epilogue.hpp"

