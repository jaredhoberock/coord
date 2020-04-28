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
#include "detail/tuple_utility.hpp"
#include "discrete.hpp"


COORD_NAMESPACE_OPEN_BRACE


// scalar case
template<class Integral,
         COORD_REQUIRES(std::is_integral<Integral>::value)
        >
COORD_ANNOTATION
constexpr std::size_t space_size(const Integral& shape)
{
  return static_cast<std::size_t>(shape);
}


// non-scalar case
template<typename Shape,
         COORD_REQUIRES(!std::is_integral<Shape>::value),
         COORD_REQUIRES(is_discrete_v<Shape>)
        >
COORD_ANNOTATION
constexpr std::size_t space_size(const Shape& shape);


namespace detail
{
namespace space_size_detail
{


struct space_size_functor
{
  template<typename Shape,
           COORD_REQUIRES(is_discrete_v<Shape>)
          >
  COORD_ANNOTATION
  constexpr std::size_t operator()(const Shape& shape) const
  {
    return COORD_NAMESPACE::space_size(shape);
  }
};


} // end space_size_detail
} // end detail


// non-scalar case
template<typename Shape,
         COORD_REQUIRES_DEF(!std::is_integral<Shape>::value),
         COORD_REQUIRES_DEF(is_discrete_v<Shape>)
        >
COORD_ANNOTATION
constexpr std::size_t space_size(const Shape& shape)
{
  // XXX we could use something like tuple_transform_reduce here

  // transform shape into a tuple of sizes
  auto tuple_of_sizes = detail::tu::tuple_map(detail::space_size_detail::space_size_functor{}, shape);

  // reduce the sizes
  return detail::tu::tuple_reduce(tuple_of_sizes, std::size_t{1}, [](std::size_t x, std::size_t y)
  {
    return x * y;
  });
}


COORD_NAMESPACE_CLOSE_BRACE


#include "detail/epilogue.hpp"

