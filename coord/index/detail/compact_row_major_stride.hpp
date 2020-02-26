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

#include "../../detail/prologue.hpp"

#include <tuple>
#include <type_traits>
#include "../../detail/index_sequence.hpp"
#include "../../detail/tuple_utility.hpp"
#include "../../shape/make_shape.hpp"
#include "../../shape/shape_size.hpp"
#include "index_subspace_size.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class Integral1, class Integral2,
         COORD_REQUIRES(std::is_integral<Integral1>::value),
         COORD_REQUIRES(std::is_integral<Integral2>::value)
        >
COORD_ANNOTATION
Integral2 compact_row_major_stride_impl(const Integral1& shape, const Integral2& current_stride)
{
  return current_stride;
}


template<class Shape, class Integral>
COORD_ANNOTATION
typename std::enable_if<!std::is_integral<Shape>::value, Shape>::type
  compact_row_major_stride_impl(const Shape& shape, const Integral& current_stride);


template<class Shape, class Integral, std::size_t... Is>
COORD_ANNOTATION
Shape compact_row_major_stride_impl(const Shape& shape,
                                    const Integral& current_stride,
                                    index_sequence<Is...>)
{
  return COORD_NAMESPACE::make_shape<Shape>(detail::compact_row_major_stride_impl(tu::get<Is>(shape), current_stride * detail::index_subspace_size(shape, detail::make_ascending_index_range<Is+1,shape_size<Shape>::value>{}))...);
}


template<class Shape, class Integral>
COORD_ANNOTATION
typename std::enable_if<!std::is_integral<Shape>::value, Shape>::type
  compact_row_major_stride_impl(const Shape& shape, const Integral& current_stride)
{
  return detail::compact_row_major_stride_impl(shape, current_stride, make_index_sequence<shape_size<Shape>::value>{});
}


template<class Shape,
         COORD_REQUIRES(is_shape<Shape>::value)
        >
COORD_ANNOTATION
Shape compact_row_major_stride(const Shape& shape)
{
  return detail::compact_row_major_stride_impl(shape, 1);
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "../../detail/epilogue.hpp"

