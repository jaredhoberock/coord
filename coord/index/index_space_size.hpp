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

#include <cstdint>
#include <type_traits>
#include "../detail/tuple_utility.hpp"
#include "../shape/is_shape.hpp"


COORD_NAMESPACE_OPEN_BRACE


// scalar case of index_space_size
template<class Integral,
         COORD_REQUIRES(std::is_integral<Integral>::value)
        >
COORD_ANNOTATION
std::size_t index_space_size(const Integral& shape)
{
  return static_cast<std::size_t>(shape);
}


namespace detail
{
namespace index_space_size_detail
{


// forward declaration of recursive_index_space_size for index_space_size_functor
// the reason we give this a separate name from index_space_size is so that
// the public-facing index_space_size overloads can use COORD_REQUIRES which
// may not be used elegantly when a function prototype is separated from its definition
template<typename Shape>
COORD_ANNOTATION
std::size_t recursive_index_space_size(const Shape& s);


struct index_space_size_functor
{
  template<typename Shape>
  COORD_ANNOTATION
  std::size_t operator()(const Shape& shape)
  {
    return index_space_size_detail::recursive_index_space_size(shape);
  }
};


} // end index_space_size_detail
} // end detail


// non-scalar case
template<typename Shape,
         COORD_REQUIRES(is_shape<Shape>::value),
         COORD_REQUIRES(!std::is_integral<Shape>::value)
        >
COORD_ANNOTATION
std::size_t index_space_size(const Shape& shape)
{
  // XXX we could use something like tuple_transform_reduce here

  // transform s into a tuple of sizes
  auto tuple_of_sizes = detail::tu::tuple_map(detail::index_space_size_detail::index_space_size_functor{}, shape);

  // reduce the sizes
  return detail::tu::tuple_reduce(tuple_of_sizes, std::size_t{1}, [](std::size_t x, std::size_t y)
  {
    return x * y;
  });
}


namespace detail
{
namespace index_space_size_detail
{


template<typename Shape>
COORD_ANNOTATION
std::size_t recursive_index_space_size(const Shape& s)
{
  return COORD_NAMESPACE::index_space_size(s);
}


} // end index_space_size_detail
} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "../detail/epilogue.hpp"

