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

#include <type_traits>
#include "../space_size.hpp"
#include "../coordinate/element.hpp"
#include "../coordinate/rank.hpp"
#include "../discrete.hpp"
#include "index_sequence.hpp"
#include "make.hpp"
#include "subspace_size.hpp"
#include "tuple_utility.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class Integral1, class Integral2,
         COORD_REQUIRES(std::is_integral<Integral1>::value),
         COORD_REQUIRES(std::is_integral<Integral2>::value)
        >
COORD_ANNOTATION
constexpr Integral2 compact_column_major_stride_impl(const Integral1& shape, const Integral2& current_stride)
{
  return current_stride;
}


template<class Shape, class Integral,
         COORD_REQUIRES(!std::is_integral<Shape>::value)
        >
COORD_ANNOTATION
constexpr Shape compact_column_major_stride_impl(const Shape& shape, const Integral& current_stride);


template<class Shape, class Integral, std::size_t... Is>
COORD_ANNOTATION
constexpr Shape compact_column_major_stride_impl(const Shape& shape,
                                                 const Integral& current_stride,
                                                 index_sequence<Is...>)
{
  return COORD_NAMESPACE::detail::make<Shape>(detail::compact_column_major_stride_impl(element<Is>(shape), current_stride * detail::subspace_size(shape, detail::make_ascending_index_range<0,Is>{}))...);
}


template<class Shape, class Integral,
         COORD_REQUIRES_DEF(!std::is_integral<Shape>::value)
        >
COORD_ANNOTATION
constexpr Shape compact_column_major_stride_impl(const Shape& shape, const Integral& current_stride)
{
  return detail::compact_column_major_stride_impl(shape, current_stride, make_index_sequence<rank_v<Shape>>{});
}


template<class Shape,
         COORD_REQUIRES(is_discrete_v<Shape>)
        >
COORD_ANNOTATION
constexpr Shape compact_column_major_stride(const Shape& shape)
{
  return detail::compact_column_major_stride_impl(shape, 1);
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "epilogue.hpp"

