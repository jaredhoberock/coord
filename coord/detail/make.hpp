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

#include "prologue.hpp"


#include <array>
#include <type_traits>
#include <utility>
#include "../rank.hpp"
#include "../discrete.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class Coord>
struct make_impl
{
  template<class... Args,
           COORD_REQUIRES(std::is_constructible<Coord,Args&&...>::value)
          >
  COORD_ANNOTATION
  constexpr Coord operator()(Args&&... args) const
  {
    return Coord{std::forward<Args>(args)...};
  }
};

// specialization for std::array, which requires the weird doubly-nested brace syntax
template<class T, size_t n>
struct make_impl<std::array<T,n>>
{
  template<class... Args>
  COORD_ANNOTATION
  constexpr std::array<T,n> operator()(Args&&... args) const
  {
    return std::array<T,n>{{std::forward<Args>(args)...}};
  }
};


template<class Integral, class Arg,
         COORD_REQUIRES(std::is_integral<Integral>::value),
         COORD_REQUIRES(std::is_constructible<Integral,Arg&&>::value)
        >
COORD_ANNOTATION
constexpr Integral make(Arg&& arg)
{
  return {std::forward<Arg>(arg)};
}


template<class Coord, class... Args,
         COORD_REQUIRES(!std::is_integral<Coord>::value),
         COORD_REQUIRES(is_discrete_v<Coord>),
         COORD_REQUIRES(rank_v<Coord> == sizeof...(Args))
        >
COORD_ANNOTATION
constexpr Coord make(Args&&... args)
{
  detail::make_impl<Coord> impl;
  return impl(std::forward<Args>(args)...);
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE

#include "epilogue.hpp"

