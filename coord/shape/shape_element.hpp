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


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


// shape_element<i,Shape> is a type trait which returns the
// type of the ith element of the given Shape.
//
// A Shape is either:
// 1. An integral type or
// 2. A tuple of Shapes
//
// shape_element's implementation below needs to handle these two cases.


// case 2: Shape is a Tuple-like type
template<size_t i, class Shape, class Enable = void>
struct shape_element_impl : std::tuple_element<i, Shape> {};


// case 1: Shape is an integral type.
// This case only makes sense when i is 0.
template<size_t i, class Shape>
struct shape_element_impl<
  i,
  Shape,
  typename std::enable_if<
    std::is_integral<Shape>::value and i == 0
  >::type
>
{
  using type = Shape;
};


} // end detail


template<size_t i, class Shape>
struct shape_element
{
  using type = typename detail::shape_element_impl<i,Shape>::type;
};

template<size_t i, class Shape>
using shape_element_t = typename shape_element<i,Shape>::type;


COORD_NAMESPACE_CLOSE_BRACE

#include "../detail/epilogue.hpp"

