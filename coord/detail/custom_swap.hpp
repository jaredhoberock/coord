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
namespace custom_swap_detail
{


// this tests whether a type T is ADL-swappable
template<class T>
struct is_adl_swappable_impl
{
  template<class U,
           class = decltype(swap(std::declval<U&>(), std::declval<U&>()))
          >
  static std::true_type test(int);

  template<class>
  static std::false_type test(...);

  using type = decltype(test<T>(0));
};

template<class T>
using is_adl_swappable = typename is_adl_swappable_impl<T>::type;


// this is the default implementation of swap
// which just uses std::move
COORD_EXEC_CHECK_DISABLE
template<class T,
         COORD_REQUIRES(!is_adl_swappable<T>::value)
        >
COORD_ANNOTATION
void custom_swap_impl(T& a, T& b)
{
  T tmp = std::move(a);
  a = std::move(b);
  b = std::move(tmp);
}


// this is the default implementation of swap
// which calls swap through ADL
COORD_EXEC_CHECK_DISABLE
template<class T,
         COORD_REQUIRES(is_adl_swappable<T>::value)
        >
COORD_ANNOTATION
void custom_swap_impl(T& a, T& b)
{
  swap(a, b);
}


} // end custom_swap_detail


// custom_swap is like std::swap except:
// * custom_swap is not ambiguous with std::swap because it has a different name and
// * custom_swap automatically calls swap() via ADL if such a call is well-formed
//   otherwise, it uses a default implementation of swap
template<class T>
COORD_ANNOTATION
void custom_swap(T& a, T& b)
{
  custom_swap_detail::custom_swap_impl(a, b);
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "epilogue.hpp"

