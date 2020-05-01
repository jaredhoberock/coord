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
#include "detail/index_sequence.hpp"
#include "element.hpp"
#include "rank.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{
namespace is_coordinal_detail
{


template<class IntegralConstant, class T>
using has_element_helper = element_t<IntegralConstant::value, T>;


template<class IntegralConstant, class T>
using has_element = is_detected<has_element_helper, IntegralConstant, T>;


template<class T, class IndexSequence>
struct has_elements;

template<class T, std::size_t... I>
struct has_elements<T, index_sequence<I...>> :
  conjunction<
    has_element<std::integral_constant<std::size_t,I>, T>...
  >
{};


template<class T>
struct is_coordinal_impl
{
  template<class U,
           COORD_REQUIRES(is_detected<rank_t, U>::value),
           std::size_t N = rank_v<U>,
           COORD_REQUIRES(has_elements<T, make_index_sequence<N>>::value)
          >
  static constexpr bool test(int)
  {
    return true;
  }

  template<class>
  static constexpr bool test(...)
  {
    return false;
  }

  static constexpr bool value = test<T>(0);
};


} // end is_coordinate_detail
} // end detail


template<class T>
using is_coordinal = std::integral_constant<
  bool, detail::is_coordinal_detail::is_coordinal_impl<T>::value
>;


#ifdef __cpp_variable_templates
template<class T>
static constexpr bool is_coordinal_v = is_coordinal<T>::value;
#endif


COORD_NAMESPACE_CLOSE_BRACE


#include "detail/epilogue.hpp"

