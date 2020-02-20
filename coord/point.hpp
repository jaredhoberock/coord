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

#include <cassert>
#include <initializer_list>
#include <type_traits>
#include "detail/arithmetic_tuple_facade.hpp"
#include "detail/array.hpp"
#include "detail/conjunction.hpp"
#include "detail/has_arithmetic_operators.hpp"
#include "detail/index_sequence.hpp"
#include "detail/named_array.hpp"


COORD_NAMESPACE_OPEN_BRACE

namespace detail
{
namespace point_detail
{


// in general, point's base class is array<T,Rank> but low-rank points get named elements
template<class T, size_t Rank>
struct point_base
{
  using type = array<T,Rank>;
};

template<class T>
struct point_base<T,1>
{
  using type = named_array<T,1>;
};

template<class T>
struct point_base<T,2>
{
  using type = named_array<T,2>;
};

template<class T>
struct point_base<T,3>
{
  using type = named_array<T,3>;
};

template<class T>
struct point_base<T,4>
{
  using type = named_array<T,4>;
};

template<class T, size_t Rank>
using point_base_t = typename point_base<T,Rank>::type;


} // end point_detail
} // end detail


// T is any type with operators +, +=, -, -=, *, *=,  /, /=, <
template<class T, size_t Rank>
class point : public detail::point_detail::point_base_t<T,Rank>,
              public detail::arithmetic_tuple_facade<point<T,Rank>>
{
  static_assert(detail::has_arithmetic_operators<T>::value, "T must have arithmetic operators.");

  using super_t = detail::point_detail::point_base_t<T,Rank>;

  public:
    using typename super_t::value_type;
    using typename super_t::reference;
    using typename super_t::size_type;
    using typename super_t::pointer;
    using typename super_t::const_pointer;


    // default constructor
    point() = default;


    // copy constructor
    point(const point &) = default;


    // variadic constructor
    template<class... OtherT,
             COORD_REQUIRES(
               detail::conjunction<
                 std::is_convertible<OtherT,value_type>...
               >::value and
               sizeof...(OtherT) == Rank
             )>
    COORD_ANNOTATION
    point(OtherT... args)
      : super_t{{static_cast<value_type>(args)...}}
    {}


    // initializer_list constructor
    // this constructor is included to allow us to pass through interfaces curly-braced
    // lists which eventually get unpacked into points
    //
    // XXX attempts to initialize a point from an initializer_list of the wrong size
    //     should be a compile-time error
    //     the problem is that list.size() can't always be used in static_assert
    template<class OtherT,
             COORD_REQUIRES(
               std::is_convertible<OtherT,value_type>::value
             )>
    COORD_ANNOTATION
    point(std::initializer_list<OtherT> l)
      : super_t(l)
    {
      // l.size() needs to equal Rank
      assert(l.size() == Rank);
    }


    // converting constructor
    template<class OtherT,
             COORD_REQUIRES(
               std::is_convertible<OtherT,value_type>::value
             )>
    COORD_ANNOTATION
    point(const point<OtherT,Rank>& other)
      : super_t(other)
    {}


    // fill constructor
    template<class OtherT,
             COORD_REQUIRES(
               (Rank > 1) and
               std::is_convertible<OtherT,value_type>::value
             )>
    COORD_ANNOTATION
    explicit point(OtherT val)
      : point(replicate_as_point<OtherT>(val, detail::make_index_sequence<Rank>{}))
    {}

  private:
    template<std::size_t, class OtherT>
    COORD_ANNOTATION
    OtherT identity(OtherT val)
    {
      return val;
    }


    template<class OtherT, std::size_t... Indices>
    COORD_ANNOTATION
    point<OtherT,Rank> replicate_as_point(OtherT val, detail::index_sequence<Indices...>)
    {
      return {identity<Indices>(val)...};
    }
};


template<size_t i, class T, size_t Rank>
COORD_ANNOTATION
T& get(point<T,Rank>& p)
{
  return p[i];
}


template<size_t i, class T, size_t Rank>
COORD_ANNOTATION
const T& get(const point<T,Rank>& p)
{
  return p[i];
}


template<size_t i, class T, size_t Rank>
COORD_ANNOTATION
T&& get(point<T,Rank>&& p)
{
  return std::move(COORD_NAMESPACE::get<i>(p));
}


// scalar multiply
// XXX should this use is_arithmetic<T1>, or has_arithmetic_operators<T1>?
template<class T1, class T2, size_t Rank,
         COORD_REQUIRES(std::is_arithmetic<T1>::value),
         COORD_REQUIRES(detail::has_operator_multiplies<T1,T2>::value)
        >
COORD_ANNOTATION
point<typename std::common_type<T1,T2>::type, Rank>
  operator*(T1 val, const point<T2,Rank>& p)
{
  using result_type = point<typename std::common_type<T1,T2>::type, Rank>;

  return result_type(val) * p;
}


using int0  = point<int,0>;
using int1  = point<int,1>;
using int2  = point<int,2>;
using int3  = point<int,3>;
using int4  = point<int,4>;
using int5  = point<int,5>;
using int6  = point<int,6>;
using int7  = point<int,7>;
using int8  = point<int,8>;
using int9  = point<int,9>;
using int10 = point<int,10>;


using uint0  = point<unsigned int,0>;
using uint1  = point<unsigned int,1>;
using uint2  = point<unsigned int,2>;
using uint3  = point<unsigned int,3>;
using uint4  = point<unsigned int,4>;
using uint5  = point<unsigned int,5>;
using uint6  = point<unsigned int,6>;
using uint7  = point<unsigned int,7>;
using uint8  = point<unsigned int,8>;
using uint9  = point<unsigned int,9>;
using uint10 = point<unsigned int,10>;


using size0  = point<size_t,0>;
using size1  = point<size_t,1>;
using size2  = point<size_t,2>;
using size3  = point<size_t,3>;
using size4  = point<size_t,4>;
using size5  = point<size_t,5>;
using size6  = point<size_t,6>;
using size7  = point<size_t,7>;
using size8  = point<size_t,8>;
using size9  = point<size_t,9>;
using size10 = point<size_t,10>;


using float0  = point<float,0>;
using float1  = point<float,1>;
using float2  = point<float,2>;
using float3  = point<float,3>;
using float4  = point<float,4>;
using float5  = point<float,5>;
using float6  = point<float,6>;
using float7  = point<float,7>;
using float8  = point<float,8>;
using float9  = point<float,9>;
using float10 = point<float,10>;


using double0  = point<double,0>;
using double1  = point<double,1>;
using double2  = point<double,2>;
using double3  = point<double,3>;
using double4  = point<double,4>;
using double5  = point<double,5>;
using double6  = point<double,6>;
using double7  = point<double,7>;
using double8  = point<double,8>;
using double9  = point<double,9>;
using double10 = point<double,10>;


COORD_NAMESPACE_CLOSE_BRACE


// specialize Tuple-like interface for COORD_NAMESPACE::point
namespace std
{


template<class >
struct tuple_size;

template<class T, size_t Rank>
struct tuple_size<COORD_NAMESPACE::point<T,Rank>> : public std::integral_constant<std::size_t, Rank> {};


template<std::size_t I, class T>
struct tuple_element;

template<size_t I, class T, size_t Rank>
struct tuple_element<I,COORD_NAMESPACE::point<T,Rank>>
{
  using type = T;
};


} // end std

#include "detail/epilogue.hpp"

