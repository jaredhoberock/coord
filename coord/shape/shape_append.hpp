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
#include "../detail/index_sequence.hpp"
#include "shape_size.hpp"
#include "shape_element.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


// this function appends a type Appended to the end of Shape and the result is an instantiation of TupleTemplate
template<class Indices, class Shape, class T, template<class...> class TupleTemplate>
struct instantiate_tuple_template_with_shape_elements_and_appended;


// to append a type T to a Shape, list the Shape's elements, add T at the end of this list, and use this list to instantiate the given tuple template
template<size_t... Indices, class Shape, class T, template<class...> class TupleTemplate>
struct instantiate_tuple_template_with_shape_elements_and_appended<index_sequence<Indices...>, Shape, T, TupleTemplate>
{
  using type = TupleTemplate<shape_element_t<Indices,Shape>..., T>;
};


template<class Shape, class Appended, template<class...> class TupleTemplate>
using instantiate_tuple_template_with_shape_elements_and_appended_t = typename instantiate_tuple_template_with_shape_elements_and_appended<
  make_index_sequence<shape_size<Shape>::value>,
  Shape,
  Appended,
  TupleTemplate
>::type;


// this trait defines a nested template named tuple
// which is used for the instantiation of the result of shape_append_t
template<class InputShape, class ToAppend>
struct default_shape_append_tuple
{
  // by default, just use a std::tuple
  template<class... Types>
  using tuple = std::tuple<Types...>;
};

// when appending a type T to an Array of Ts, just extend the Array's length by 1
template<template<class, std::size_t> class ArrayLike, std::size_t n, class T>
struct default_shape_append_tuple<ArrayLike<T,n>, T>
{
  template<class...>
  using tuple = ArrayLike<T,n+1>;
};


// when appending a type to a Tuple-like template, just use the Tuple-like template itself
template<template<class...> class Tuple, class... TupleElements, class ToAppend>
struct default_shape_append_tuple<Tuple<TupleElements...>, ToAppend>
{
  template<class... Types>
  using tuple = Tuple<Types...>;
};


// when appending a type to a std::pair, use std::tuple
// this case is introduced to disambiguate the partial specialization above
template<class T1, class T2, class ToAppend>
struct default_shape_append_tuple<std::pair<T1,T2>,ToAppend>
{
  template<class... Types>
  using tuple = std::tuple<Types...>;
};


} // end detail


template<class Shape, class T, template<class...> class ResultTemplate = detail::default_shape_append_tuple<Shape,T>::template tuple>
using shape_append_t = detail::instantiate_tuple_template_with_shape_elements_and_appended_t<Shape, T, ResultTemplate>;


// the reason that there is no type trait named shape_append is to reserve this name for the hypothetical function:
//
// template<class Shape, class T>
// shape_append_t<Shape,T> shape_append(const Shape& shape, const T& value);


COORD_NAMESPACE_CLOSE_BRACE


#include "../detail/epilogue.hpp"

