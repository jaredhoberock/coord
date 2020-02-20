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
#include <utility>


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{
namespace has_arithmetic_operators_detail
{


template<typename T1, typename T2> struct is_different : std::true_type {};


template<typename T1> struct is_different<T1,T1> : std::false_type {};


struct any
{
  template<typename T> any(T) {}
};


struct ignore {};


struct no {};


no operator+(any, any);
no operator+=(any, any);

no operator-(any, any);
no operator-=(any, any);

no operator*(any, any);
no operator*=(any, any);

no operator/(any, any);
no operator/=(any, any);

no operator<(any, any);
no operator<=(any, any);

no operator>(any, any);
no operator>=(any, any);


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_plus
  : is_different<
      decltype(std::declval<T1>() + std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_plus_assign
  : is_different<
      decltype(std::declval<T1&>() += std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_minus
  : is_different<
      decltype(std::declval<T1>() - std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_minus_assign
  : is_different<
      decltype(std::declval<T1&>() -= std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_multiplies
  : is_different<
      decltype(std::declval<T1>() * std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_multiplies_assign
  : is_different<
      decltype(std::declval<T1&>() *= std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_divides
  : is_different<
      decltype(std::declval<T1>() / std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_divides_assign
  : is_different<
      decltype(std::declval<T1&>() /= std::declval<T2>()),
      no
    >
{
};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_less
  : is_different<
      decltype(std::declval<T1>() < std::declval<T2>()),
      no
    >
{};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_less_equal
  : is_different<
      decltype(std::declval<T1>() <= std::declval<T2>()),
      no
    >
{};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_greater
  : is_different<
      decltype(std::declval<T1>() > std::declval<T2>()),
      no
    >
{};


template<typename T1, typename T2 = T1, typename Result = ignore>
struct has_operator_greater_equal
  : is_different<
      decltype(std::declval<T1>() >= std::declval<T2>()),
      no
    >
{};


template<typename, typename, typename Enable = void> struct operator_plus_result {};


template<typename T1, typename T2>
struct operator_plus_result<T1, T2, typename std::enable_if<has_operator_plus<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() + std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_plus_assign_result {};


template<typename T1, typename T2>
struct operator_plus_assign_result<T1,T2, typename std::enable_if<has_operator_plus_assign<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() += std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_minus_result {};


template<typename T1, typename T2>
struct operator_minus_result<T1,T2, typename std::enable_if<has_operator_minus<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() - std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_minus_assign_result {};


template<typename T1, typename T2>
struct operator_minus_assign_result<T1, T2, typename std::enable_if<has_operator_minus_assign<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() -= std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_multiplies_result {};


template<typename T1, typename T2>
struct operator_multiplies_result<T1, T2, typename std::enable_if<has_operator_multiplies<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() - std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_multiplies_assign_result {};


template<typename T1, typename T2>
struct operator_multiplies_assign_result<T1,T2, typename std::enable_if<has_operator_multiplies_assign<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() -= std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_divides_result {};


template<typename T1, typename T2>
struct operator_divides_result<T1,T2, typename std::enable_if<has_operator_divides<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() - std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_divides_assign_result {};


template<typename T1, typename T2>
struct operator_divides_assign_result<T1, T2, typename std::enable_if<has_operator_divides_assign<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() -= std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_less_result {};


template<typename T1, typename T2>
struct operator_less_result<T1,T2, typename std::enable_if<has_operator_less<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() < std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_less_equal_result {};


template<typename T1, typename T2>
struct operator_less_equal_result<T1,T2, typename std::enable_if<has_operator_less_equal<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() <= std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_greater_result {};


template<typename T1, typename T2>
struct operator_greater_result<T1,T2, typename std::enable_if<has_operator_greater<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() > std::declval<T2>());
};


template<typename, typename, typename Enable = void> struct operator_greater_equal_result {};


template<typename T1, typename T2>
struct operator_greater_equal_result<T1,T2, typename std::enable_if<has_operator_greater_equal<T1,T2>::value>::type>
{
  using type = decltype(std::declval<T1>() >= std::declval<T2>());
};


} // end has_arithmetic_operators_detail


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_plus = has_arithmetic_operators_detail::has_operator_plus<T1,T2,Result>;


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_plus_assign = has_arithmetic_operators_detail::has_operator_plus_assign<T1,T2,Result>;


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_minus = has_arithmetic_operators_detail::has_operator_minus<T1,T2,Result>;


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_minus_assign = has_arithmetic_operators_detail::has_operator_minus_assign<T1,T2,Result>;


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_multiplies = has_arithmetic_operators_detail::has_operator_multiplies<T1,T2,Result>;


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_multiplies_assign = has_arithmetic_operators_detail::has_operator_multiplies_assign<T1,T2,Result>;


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_divides = has_arithmetic_operators_detail::has_operator_divides<T1,T2,Result>;


template<typename T1, typename T2 = T1, typename Result = has_arithmetic_operators_detail::ignore>
using has_operator_divides_assign = has_arithmetic_operators_detail::has_operator_divides_assign<T1,T2,Result>;


template<typename T1, typename T2 = T1>
using has_arithmetic_operators = std::integral_constant<
  bool,
  has_operator_plus<T1,T2,T1>::value and
  has_operator_plus_assign<T1,T2,T1&>::value and
  has_operator_minus<T1,T2,T1>::value and
  has_operator_minus_assign<T1,T2,T1&>::value and
  has_operator_multiplies<T1,T2,T1>::value and
  has_operator_multiplies_assign<T1,T2,T1&>::value and
  has_operator_divides<T1,T2,T1>::value and
  has_operator_divides_assign<T1,T2,T1&>::value
  // XXX it seems like checks for modulus are missing
>;


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "epilogue.hpp"

