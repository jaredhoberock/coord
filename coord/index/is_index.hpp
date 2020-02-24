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
#include "../detail/conjunction.hpp"
#include "../detail/disjunction.hpp"
#include "../detail/index_sequence.hpp"
#include "../detail/tuple_utility.hpp"


COORD_NAMESPACE_OPEN_BRACE


// a forward declaration for the benefit of detail::is_tuple_like_of_indices below
template<class T>
struct is_index;


namespace detail
{


template<class T>
struct is_tuple_like_of_indices
{
  private:
    template<class U, std::size_t... I>
    static constexpr bool test_elements_of_tuple(index_sequence<I...>)
    {
      return conjunction<
        is_index<
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


// a type is a index if it
//   * is an integral type, or 
//   * it is a tuple-like type with elements which are themselves indices
template<class T>
struct is_index : detail::disjunction<std::is_integral<T>, detail::is_tuple_like_of_indices<T>> {};


COORD_NAMESPACE_CLOSE_BRACE

#include "../detail/epilogue.hpp"

