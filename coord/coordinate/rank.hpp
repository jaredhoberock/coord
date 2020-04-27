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
#include "../detail/index_sequence.hpp"
#include "../detail/static_const.hpp"
#include "../detail/tuple_utility.hpp"
#include "../detail/type_traits/is_detected.hpp"
#include "../detail/type_traits/is_number.hpp"
#include "../detail/type_traits/remove_cvref.hpp"


#include <cstdint>


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class T>
using rank_member_function_t = decltype(std::declval<T>().rank());

template<class T>
using has_rank_member_function = is_detected<rank_member_function_t, T>;


template<class T>
using rank_free_function_t = decltype(rank(std::declval<T>()));

template<class T>
using has_rank_free_function = is_detected<rank_free_function_t, T>;



template<class T>
struct is_tuple_like_of_types_with_rank;


struct dispatch_rank
{
  COORD_EXEC_CHECK_DISABLE
  template<class T,
           COORD_REQUIRES(has_rank_member_function<T&&>::value)
          >
  COORD_ANNOTATION
  constexpr std::size_t operator()(T&& c) const
  {
    return std::forward<T>(c).rank();
  }

  COORD_EXEC_CHECK_DISABLE
  template<class T,
           COORD_REQUIRES(!has_rank_member_function<T&&>::value),
           COORD_REQUIRES(has_rank_free_function<T&&>::value)
          >
  COORD_ANNOTATION
  constexpr std::size_t operator()(T&& c) const
  {
    return rank(std::forward<T>(c));
  }

  COORD_EXEC_CHECK_DISABLE
  template<class T,
           COORD_REQUIRES(!has_rank_member_function<T&&>::value),
           COORD_REQUIRES(!has_rank_free_function<T&&>::value),
           COORD_REQUIRES(is_number<remove_cvref_t<T&&>>::value)
          >
  COORD_ANNOTATION
  constexpr std::size_t operator()(T&&) const
  {
    return 0;
  }

  COORD_EXEC_CHECK_DISABLE
  template<class T,
           COORD_REQUIRES(!has_rank_member_function<T&&>::value),
           COORD_REQUIRES(!has_rank_free_function<T&&>::value),
           COORD_REQUIRES(!is_number<remove_cvref_t<T&&>>::value),
           COORD_REQUIRES(is_tuple_like_of_types_with_rank<remove_cvref_t<T&&>>::value)
          >
  COORD_ANNOTATION
  constexpr std::size_t operator()(T&&) const
  {
    return std::tuple_size<remove_cvref_t<T&&>>::value;
  }
};


} // end detail


namespace
{


// define the rank customization point object
#ifndef __CUDA_ARCH__
constexpr auto const& rank = detail::static_const<detail::dispatch_rank>::value;
#else
const __device__ detail::dispatch_rank rank;
#endif


} // end anonymous namespace


template<class T>
using rank_t = decltype(COORD_NAMESPACE::rank(std::declval<T>()));


template<class T>
static constexpr auto rank_v = rank(T{});


namespace detail
{


template<class T>
struct is_tuple_like_of_types_with_rank
{
  private:
    template<class U, std::size_t... I>
    static constexpr bool test_elements_of_tuple(index_sequence<I...>)
    {
      return conjunction<
        is_detected<
          rank_t,
          typename std::tuple_element<I,U>::type
        >...
      >::value;
    }

    template<class U = T,
             COORD_REQUIRES(tu::is_tuple_like<U>::value)
            >
    static constexpr bool test(int)
    {
      return test_elements_of_tuple<U>(make_index_sequence<std::tuple_size<U>::value>{});
    }

    template<class>
    static constexpr bool test(...)
    {
      return false;
    }

  public:
    static constexpr bool value = test<T>(0);
};


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


#include "../detail/epilogue.hpp"

