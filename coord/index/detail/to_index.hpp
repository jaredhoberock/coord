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

#include <type_traits>
#include "../../detail/index_sequence.hpp"
#include "../../detail/tuple_utility.hpp"
#include "../../shape/make_shape.hpp"
#include "../../shape/shape_size.hpp"
#include "../index_element.hpp"
#include "../make_index.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class Integral0, class Integral1, class Integral2, class Integral3,
         COORD_REQUIRES(std::is_integral<Integral0>::value and
                        std::is_integral<Integral1>::value and
                        std::is_integral<Integral2>::value and
                        std::is_integral<Integral3>::value)
        >
COORD_ANNOTATION
Integral0 to_index(const Integral1& i, const Integral2& shape, const Integral3& stride)
{
  return (i / stride) % shape;
}


template<class Index, class Integral, class Shape, class Stride>
COORD_ANNOTATION
typename std::enable_if<!std::is_integral<Shape>::value, Index>::type
  to_index(const Integral& i, const Shape& shape, const Stride& stride);


template<class Index, class Integral, class Shape, class Stride, std::size_t... Is,
         COORD_REQUIRES(std::is_integral<Integral>::value),
         COORD_REQUIRES(!std::is_integral<Shape>::value),
         COORD_REQUIRES(!std::is_integral<Stride>::value)
        >
COORD_ANNOTATION
Index to_index_impl(const Integral& i,
                    const Shape& shape,
                    const Stride& stride,
                    index_sequence<Is...>)
{
  return make_index<Index>(detail::to_index<index_element_t<Is, Index>>(i, tu::get<Is>(shape), tu::get<Is>(stride))...);
}


template<class Index, class Integral, class Shape, class Stride>
COORD_ANNOTATION
typename std::enable_if<!std::is_integral<Shape>::value, Index>::type
  to_index(const Integral& i, const Shape& shape, const Stride& stride)
{
  return detail::to_index_impl<Index>(i, shape, stride, make_index_sequence<shape_size<Shape>::value>{});
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "../../detail/epilogue.hpp"

