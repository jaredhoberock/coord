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
#include "../shape/shape_size.hpp"
#include "../shape/is_shape.hpp"
#include "detail/index_subspace_size.hpp"
#include "index_first.hpp"
#include "index_size.hpp"
#include "index_space_size.hpp"
#include "is_index.hpp"


COORD_NAMESPACE_OPEN_BRACE


template<class Integral1, class Integral2,
         COORD_REQUIRES(std::is_integral<Integral1>::value),
         COORD_REQUIRES(std::is_integral<Integral2>::value)
        >
COORD_ANNOTATION
std::size_t colexicographic_rank(const Integral1& index, const Integral2&)
{
  return static_cast<std::size_t>(index);
}


namespace detail
{



template<class Index, class Shape,
         std::size_t i0, std::size_t... is
        >
COORD_ANNOTATION
std::size_t recursive_colexicographic_rank(const Index& index, const Shape& shape, index_sequence<i0, is...>);


} // end detail



template<class Index, class Shape,
         COORD_REQUIRES(is_index<Index>::value and !std::is_integral<Index>::value),
         COORD_REQUIRES(is_shape<Shape>::value and !std::is_integral<Shape>::value),
         COORD_REQUIRES(index_size<Index>::value == shape_size<Shape>::value)
        >
COORD_ANNOTATION
std::size_t colexicographic_rank(const Index& index, const Shape& shape)
{
  return detail::recursive_colexicographic_rank(index, shape, detail::make_reversed_index_sequence<shape_size<Shape>::value>{});
}


namespace detail
{


template<class Shape, class Indices>
struct shape_suffix_indices_impl;

template<class Shape, std::size_t... Indices>
struct shape_suffix_indices_impl<Shape, index_sequence<Indices...>>
{
  using type = index_sequence<(shape_size<Shape>::value - Indices - 1)...>;
};


template<class Shape, std::size_t suffix_size>
using shape_suffix_indices = typename shape_suffix_indices_impl<Shape, make_index_sequence<suffix_size>>::type;


template<std::size_t suffix_size, class Shape>
COORD_ANNOTATION
std::size_t index_space_suffix_size(const Shape& shape)
{
  return detail::index_subspace_size(shape, shape_suffix_indices<Shape, suffix_size>{});
}


template<class Index, class Shape>
COORD_ANNOTATION
std::size_t recursive_colexicographic_rank(const Index&, const Shape&, index_sequence<>)
{
  return 0;
}

template<class Index, class Shape,
         std::size_t i0, std::size_t... is
        >
COORD_ANNOTATION
std::size_t recursive_colexicographic_rank(const Index& index, const Shape& shape, index_sequence<i0, is...> seq)
{
  return COORD_NAMESPACE::colexicographic_rank(detail::tu::get<i0>(index), detail::tu::get<i0>(shape))
    * detail::index_space_suffix_size<shape_size<Shape>::value - i0 - 1>(shape)
    + detail::recursive_colexicographic_rank(index, shape, index_sequence<is...>{})
  ;
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "../detail/epilogue.hpp"

