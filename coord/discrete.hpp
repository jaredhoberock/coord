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
#include "coordinal.hpp"
#include "element.hpp"
#include "detail/conjunction.hpp"
#include "detail/disjunction.hpp"
#include "detail/index_sequence.hpp"
#include "detail/type_traits/remove_cvref.hpp"
#include "rank.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class T>
struct terminal_elements_are_integral;


template<class T>
struct is_discrete_impl
{
  private:
    // integral types are discrete coordinates
    template<class Integral,
             COORD_REQUIRES(std::is_integral<remove_cvref_t<Integral>>::value)
            >
    static constexpr bool test(int)
    {
      return true;
    }

    // floating point types are not discrete coordinates
    template<class Float,
             COORD_REQUIRES(std::is_floating_point<remove_cvref_t<Float>>::value)
            >
    static constexpr bool test(int)
    {
      return false;
    }

    template<class Coord, std::size_t... I>
    static constexpr bool test_elements_of_coordinate(index_sequence<I...>)
    {
      return conjunction<
        is_discrete_impl<
          element_t<I,Coord>
        >...
      >::value;
    }

    // non-scalar coordinates may be discrete
    template<class Coord,
             COORD_REQUIRES(!std::is_integral<remove_cvref_t<Coord>>::value),
             COORD_REQUIRES(!std::is_floating_point<remove_cvref_t<Coord>>::value),
             COORD_REQUIRES(is_coordinal_v<Coord>)
            >
    static constexpr bool test(int)
    {
      return test_elements_of_coordinate<Coord>(make_index_sequence<rank_v<Coord>>{});
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


template<class T>
using is_discrete = std::integral_constant<
  bool,
  detail::is_discrete_impl<T>::value
>;


#ifdef __cpp_variable_templates
template<class T>
static constexpr bool is_discrete_v = is_discrete<T>::value;
#endif


template<class... Types>
using are_discrete = detail::conjunction<is_discrete<Types>...>;


#ifdef __cpp_variable_templates
template<class... Types>
static constexpr bool are_discrete_v = are_discrete<Types...>::value;
#endif


COORD_NAMESPACE_CLOSE_BRACE


#include "detail/epilogue.hpp"

