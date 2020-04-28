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

#include "detail/prologue.hpp"

#include <type_traits>
#include "congruent.hpp"
#include "detail/index_sequence.hpp"
#include "discrete.hpp"
#include "element.hpp"
#include "space_size.hpp"
#include "rank.hpp"


COORD_NAMESPACE_OPEN_BRACE


template<class Integral, class Shape,
         COORD_REQUIRES(std::is_integral<Integral>::value),
         COORD_REQUIRES(is_discrete_v<Shape>)
        >
COORD_ANNOTATION
constexpr bool compatible_spaces(const Integral& shape1, const Shape& shape2)
{
  return COORD_NAMESPACE::space_size(shape1) == COORD_NAMESPACE::space_size(shape2);
}


template<class Shape, class Integral,
         COORD_REQUIRES(!std::is_integral<Shape>::value),
         COORD_REQUIRES(is_discrete_v<Shape>),
         COORD_REQUIRES(std::is_integral<Integral>::value)
        >
COORD_ANNOTATION
constexpr bool compatible_spaces(const Shape&, const Integral&)
{
  return false;
}


template<class Shape1, class Shape2,
         COORD_REQUIRES(!std::is_integral<Shape1>::value),
         COORD_REQUIRES(!std::is_integral<Shape2>::value),
         COORD_REQUIRES(are_discrete_v<Shape1,Shape2>),
         COORD_REQUIRES(rank_v<Shape1> != rank_v<Shape2>)
        >
COORD_ANNOTATION
constexpr bool compatible_spaces(const Shape1& shape1, const Shape2& shape2)
{
  return false;
}


template<class Shape1, class Shape2,
         COORD_REQUIRES(!std::is_integral<Shape1>::value),
         COORD_REQUIRES(!std::is_integral<Shape2>::value),
         COORD_REQUIRES(are_discrete_v<Shape1,Shape2>),
         COORD_REQUIRES(rank_v<Shape1> == rank_v<Shape2>)
        >
COORD_ANNOTATION
constexpr bool compatible_spaces(const Shape1& shape1, const Shape2& shape2);


namespace detail
{


template<class Shape1, class Shape2>
COORD_ANNOTATION
constexpr bool compatible_spaces_impl(const Shape1&, const Shape2&, index_sequence<>)
{
  return true;
}


template<class Shape1, class Shape2, std::size_t i0, std::size_t... is>
COORD_ANNOTATION
constexpr bool compatible_spaces_impl(const Shape1& shape1, const Shape2& shape2, index_sequence<i0,is...>)
{
  return COORD_NAMESPACE::compatible_spaces(element<i0>(shape1), element<i0>(shape2)) and detail::compatible_spaces_impl(shape1, shape2, index_sequence<is...>{});
}


} // end detail


template<class Shape1, class Shape2,
         COORD_REQUIRES_DEF(!std::is_integral<Shape1>::value),
         COORD_REQUIRES_DEF(!std::is_integral<Shape2>::value),
         COORD_REQUIRES_DEF(are_discrete_v<Shape1,Shape2>),
         COORD_REQUIRES_DEF(rank_v<Shape1> == rank_v<Shape2>)
        >
COORD_ANNOTATION
constexpr bool compatible_spaces(const Shape1& shape1, const Shape2& shape2)
{
  return detail::compatible_spaces_impl(shape1, shape2, detail::make_index_sequence<rank_v<Shape1>>{});
}


COORD_NAMESPACE_CLOSE_BRACE


#include "detail/epilogue.hpp"

