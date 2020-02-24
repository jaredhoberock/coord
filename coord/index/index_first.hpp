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

#include <type_traits>
#include <utility>
#include "../detail/tuple_utility.hpp"
#include "../detail/is_integral_reference.hpp"
#include "detail/is_index_reference.hpp"


COORD_NAMESPACE_OPEN_BRACE


template<class Integral,
         COORD_REQUIRES(detail::is_integral_reference<Integral&&>::value)
        >
COORD_ANNOTATION
Integral&& index_first(Integral&& index)
{
  return std::forward<Integral>(index);
}


template<class Index,
         COORD_REQUIRES(detail::is_index_reference<Index&&>::value),
         COORD_REQUIRES(!detail::is_integral_reference<Index&&>::value)
        >
COORD_ANNOTATION
auto index_first(Index&& index)
  -> decltype(
       detail::tu::tuple_head(std::forward<Index>(index))
     )
{
  return detail::tu::tuple_head(std::forward<Index>(index));
}


COORD_NAMESPACE_CLOSE_BRACE

#include "../detail/epilogue.hpp"

