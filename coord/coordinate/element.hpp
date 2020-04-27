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

#include "../detail/conjunction.hpp"
#include "../detail/static_const.hpp"
#include "../detail/tuple_utility.hpp"
#include "../detail/type_traits/is_detected.hpp"
#include "../detail/type_traits/is_number.hpp"
#include "../detail/type_traits/remove_cvref.hpp"
#include "rank.hpp"


#include <cstdint>


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class IntegralConstant, class T>
using element_member_function_t = decltype(std::declval<T>().template element<IntegralConstant::value>());

template<std::size_t i, class T>
using has_element_member_function = is_detected<element_member_function_t, std::integral_constant<std::size_t,i>, T>;


namespace element_detail
{


template<std::size_t>
constexpr int element();


template<class IntegralConstant, class T>
using element_free_function_t = decltype(element<IntegralConstant::value>(std::declval<T>()));


} // end element_detail


template<std::size_t i, class T>
using has_element_free_function = is_detected<element_detail::element_free_function_t, std::integral_constant<std::size_t,i>, T>;


template<std::size_t i>
struct dispatch_element
{
  COORD_EXEC_CHECK_DISABLE
  template<class T,
           COORD_REQUIRES(has_element_member_function<i,T&&>::value)
          >
  COORD_ANNOTATION
  constexpr std::size_t operator()(T&& arg) const
  {
    return std::forward<T>(c).template element<i>();
  }

  // XXX according to https://en.cppreference.com/w/cpp/language/adl,
  //     this overload requires C++20 to find element<i>(arg)
  //COORD_EXEC_CHECK_DISABLE
  //template<class T,
  //         COORD_REQUIRES(!has_element_member_function<i,T&&>::value),
  //         COORD_REQUIRES(has_element_free_function<i,T&&>::value)
  //        >
  //COORD_ANNOTATION
  //constexpr std::size_t operator()(T&& arg) const
  //{
  //  return element<i>(std::forward<T>(arg));
  //}

  COORD_EXEC_CHECK_DISABLE
  template<class T,
           COORD_REQUIRES(!has_element_member_function<i,T&&>::value),
           COORD_REQUIRES(!has_element_free_function<i,T&&>::value),
           COORD_REQUIRES(is_number<remove_cvref_t<T&&>>::value),
           COORD_REQUIRES(i == 0)
          >
  COORD_ANNOTATION
  constexpr T&& operator()(T&& arg) const
  {
    return std::forward<T>(arg);
  }

  COORD_EXEC_CHECK_DISABLE
  template<class T,
           COORD_REQUIRES(!has_rank_member_function<T&&>::value),
           COORD_REQUIRES(!has_rank_free_function<T&&>::value),
           COORD_REQUIRES(!is_number<remove_cvref_t<T&&>>::value),
           COORD_REQUIRES(is_tuple_like_of_types_with_rank<remove_cvref_t<T&&>>::value)
          >
  constexpr auto operator()(T&& arg) const
    -> decltype(std::get<i>(std::forward<T>(arg)))
  {
    return std::get<i>(std::forward<T>(arg));
  }
};


} // end detail


namespace
{


// define the element customization point object
#ifndef __CUDA_ARCH__
template<std::size_t i>
constexpr auto const& element = detail::static_const<detail::dispatch_element<i>>::value;
#else
template<std::size_t i>
const __device__ detail::dispatch_element<i> element;
#endif


} // end anonymous namespace


template<std::size_t i, class T>
using element_t = detail::remove_cvref_t<decltype(COORD_NAMESPACE::element<i>(std::declval<T>()))>;


COORD_NAMESPACE_CLOSE_BRACE


#include "../detail/epilogue.hpp"

