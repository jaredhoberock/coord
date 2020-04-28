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
#include "rank.hpp"


COORD_NAMESPACE_OPEN_BRACE


template<class Integral1, class Integral2,
         COORD_REQUIRES(std::is_integral<Integral1>::value),
         COORD_REQUIRES(std::is_integral<Integral2>::value)
        >
COORD_ANNOTATION
constexpr bool in_space(const Integral1& coord, const Integral2& shape)
{
  return Integral1{0} <= coord and coord < shape;
}


template<class Coord, class Shape,
         COORD_REQUIRES(!std::is_integral<Coord>::value),
         COORD_REQUIRES(!std::is_integral<Shape>::value),
         COORD_REQUIRES(are_congruent_v<Coord,Shape>),
         COORD_REQUIRES(are_discrete_v<Coord,Shape>)
        >
COORD_ANNOTATION
constexpr bool in_space(const Coord& coord, const Shape& shape);


namespace detail
{


template<class Coord, class Shape>
COORD_ANNOTATION
constexpr bool in_space_impl(const Coord&, const Shape&, index_sequence<>)
{
  return true;
}


template<class Coord, class Shape, std::size_t i0, std::size_t... is>
COORD_ANNOTATION
constexpr bool in_space_impl(const Coord& coord, const Shape& shape, index_sequence<i0,is...>)
{
  return COORD_NAMESPACE::in_space(element<i0>(coord), element<i0>(shape)) and detail::in_space_impl(coord, shape, index_sequence<is...>{});
}


} // end detail


template<class Coord, class Shape,
         COORD_REQUIRES_DEF(!std::is_integral<Coord>::value),
         COORD_REQUIRES_DEF(!std::is_integral<Shape>::value),
         COORD_REQUIRES_DEF(are_congruent_v<Coord,Shape>),
         COORD_REQUIRES_DEF(are_discrete_v<Coord,Shape>)
        >
COORD_ANNOTATION
constexpr bool in_space(const Coord& coord, const Shape& shape)
{
  return detail::in_space_impl(coord, shape, detail::make_index_sequence<rank_v<Shape>>{});
}


COORD_NAMESPACE_CLOSE_BRACE


#include "detail/epilogue.hpp"

