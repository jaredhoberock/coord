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

#include <cstdint>
#include <type_traits>
#include "coordinate/element.hpp"
#include "coordinate/rank.hpp"
#include "are_congruent.hpp"
#include "detail/index_sequence.hpp"
#include "detail/make.hpp"
#include "detail/tuple_utility.hpp"


COORD_NAMESPACE_OPEN_BRACE


template<class Integral0, class Integral1, class Integral2, class Integral3,
         COORD_REQUIRES(std::is_integral<Integral0>::value),
         COORD_REQUIRES(std::is_integral<Integral1>::value),
         COORD_REQUIRES(std::is_integral<Integral2>::value),
         COORD_REQUIRES(std::is_integral<Integral3>::value)
        >
COORD_ANNOTATION
constexpr Integral0 to_coordinate(const Integral1& index, const Integral2& shape, const Integral3& stride)
{
  return (index / stride) % shape;
}


template<class Coord, class Integral, class Shape, class Stride,
         COORD_REQUIRES(std::is_integral<Integral>::value),
         COORD_REQUIRES(are_discrete_v<Coord,Shape,Stride>),
         COORD_REQUIRES(!std::is_integral<Shape>::value),
         COORD_REQUIRES(are_congruent_v<Shape,Coord>),
         COORD_REQUIRES(are_congruent_v<Shape,Stride>)
        >
COORD_ANNOTATION
constexpr Coord to_coordinate(const Integral& index, const Shape& shape, const Stride& stride);


namespace detail
{


template<class Coord, class Integral, class Shape, class Stride, std::size_t... Is,
         COORD_REQUIRES(std::is_integral<Integral>::value),
         COORD_REQUIRES(are_discrete_v<Coord,Shape,Stride>),
         COORD_REQUIRES(!std::is_integral<Shape>::value),
         COORD_REQUIRES(are_congruent_v<Shape,Coord>),
         COORD_REQUIRES(are_congruent_v<Shape,Stride>)
        >
COORD_ANNOTATION
constexpr Coord to_coordinate_impl(const Integral& index,
                                   const Shape& shape,
                                   const Stride& stride,
                                   index_sequence<Is...>)
{
  return detail::make<Coord>(COORD_NAMESPACE::to_coordinate<element_t<Is, Coord>>(index, element<Is>(shape), element<Is>(stride))...);
}


} // end detail


template<class Coord, class Integral, class Shape, class Stride,
         COORD_REQUIRES_DEF(std::is_integral<Integral>::value),
         COORD_REQUIRES_DEF(are_discrete_v<Coord,Shape,Stride>),
         COORD_REQUIRES_DEF(!std::is_integral<Shape>::value),
         COORD_REQUIRES_DEF(are_congruent_v<Shape,Coord>),
         COORD_REQUIRES_DEF(are_congruent_v<Shape,Stride>)
        >
COORD_ANNOTATION
constexpr Coord to_coordinate(const Integral& index, const Shape& shape, const Stride& stride)
{
  return detail::to_coordinate_impl<Coord>(index, shape, stride, detail::make_index_sequence<rank_v<Shape>>{});
}


COORD_NAMESPACE_CLOSE_BRACE


#include "detail/epilogue.hpp"

