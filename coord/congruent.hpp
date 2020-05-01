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
#include "detail/conjunction.hpp"
#include "detail/index_sequence.hpp"
#include "detail/type_traits/remove_cvref.hpp"
#include "rank.hpp"


COORD_NAMESPACE_OPEN_BRACE


template<class Coord1, class Coord2, class... Coords>
struct are_congruent;


namespace detail
{
namespace are_congruent_detail
{


template<class Coord1, class Coord2>
struct are_congruent_impl
{
  // terminal case 1: both arguments are integers
  template<class Num1, class Num2,
           COORD_REQUIRES(std::is_integral<Num1>::value),
           COORD_REQUIRES(std::is_integral<Num2>::value)
          >
  static constexpr bool test(int)
  {
    return true;
  }

  // terminal case 2: both arguments are floating point
  template<class Num1, class Num2,
           COORD_REQUIRES(std::is_floating_point<Num1>::value),
           COORD_REQUIRES(std::is_floating_point<Num2>::value)
          >
  static constexpr bool test(int)
  {
    return true;
  }

  // terminal case 3: the first argument is integral and the second is floating point
  template<class Num1, class Num2,
           COORD_REQUIRES(std::is_integral<Num1>::value),
           COORD_REQUIRES(std::is_floating_point<Num2>::value)
          >
  static constexpr bool test(int)
  {
    return false;
  }

  // terminal case 4: the first argument is floating point and the second is integral
  template<class Num1, class Num2,
           COORD_REQUIRES(std::is_floating_point<Num1>::value),
           COORD_REQUIRES(std::is_integral<Num2>::value)
          >
  static constexpr bool test(int)
  {
    return false;
  }

  // terminal case 5: the first argument is a number and the second is not
  template<class Num, class Coord,
           COORD_REQUIRES(is_number<Num>::value),
           COORD_REQUIRES(!is_number<Coord>::value)
          >
  static constexpr bool test(int)
  {
    return false;
  }
     
  // terminal case 6: first argument is not a number and the second is a number
  template<class Coord, class Num,
           COORD_REQUIRES(!is_number<Coord>::value),
           COORD_REQUIRES(is_number<Num>::value)
          >
  static constexpr bool test(int)
  {
    return false;
  }


  template<class C1, class C2>
  static constexpr bool recursive_test(index_sequence<>)
  {
    return true;
  }
  
  template<class C1, class C2, std::size_t Index, std::size_t... Indices,
           COORD_REQUIRES(rank_v<C1> == rank_v<C2>)
          >
  static constexpr bool recursive_test(index_sequence<Index,Indices...>)
  {
    // ranks are the same - apply are_congruent element by element
    return are_congruent<element_t<Index,C1>, element_t<Index,C2>>::value and recursive_test<C1,C2>(index_sequence<Indices...>{});
  }

  template<class C1, class C2, std::size_t... Indices,
           COORD_REQUIRES(rank_v<C1> != rank_v<C2>)
          >
  static constexpr bool recursive_test(index_sequence<Indices...>)
  {
    // ranks differ - return false
    return false;
  }

  // recursive case: neither arguments are numbers
  // but both are coordinates
  template<class C1, class C2,
           COORD_REQUIRES(!is_number<C1>::value and is_coordinal<C1>::value),
           COORD_REQUIRES(!is_number<C2>::value and is_coordinal<C2>::value)
          >
  static constexpr bool test(int)
  {
    return recursive_test<C1, C2>(make_index_sequence<rank_v<C1>>{});
  }

  // neither arguments are coordinates
  template<class,class>
  static constexpr bool test(...)
  {
    return false;
  }

  // remove cv ref because is_number and is_floating_point don't like references 
  static constexpr bool value = test<remove_cvref_t<Coord1>, remove_cvref_t<Coord2>>(0);
};



} // end are_congruent_detail
} // end detail


template<class Coord1, class Coord2, class... Coords>
struct are_congruent : detail::conjunction<
  detail::are_congruent_detail::are_congruent_impl<Coord1,Coord2>,
  detail::are_congruent_detail::are_congruent_impl<Coord1,Coords>...
>
{};


template<class T1, class T2, class... Ts>
static constexpr bool are_congruent_v = are_congruent<T1,T2,Ts...>::value;


COORD_NAMESPACE_CLOSE_BRACE


#include "detail/epilogue.hpp"

