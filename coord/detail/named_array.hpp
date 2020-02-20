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

#include <cstddef>
#include <tuple>
#include <utility>
#include "index_sequence.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class T, size_t Index>
struct named_array_element;

template<class T>
struct named_array_element<T,0>
{
  named_array_element() = default;

  named_array_element(const named_array_element&) = default;

  COORD_ANNOTATION
  explicit named_array_element(const T& value) : x(value) {}

  // converting constructor
  template<class OtherT,
           COORD_REQUIRES(std::is_convertible<OtherT,T>::value)
           >
  COORD_ANNOTATION
  named_array_element(const named_array_element<OtherT,0>& other)
    : named_array_element(other.x)
  {}

  T x;
};

template<class T>
struct named_array_element<T,1>
{
  named_array_element() = default;

  named_array_element(const named_array_element&) = default;

  COORD_ANNOTATION
  explicit named_array_element(const T& value) : y(value) {}

  // converting constructor
  template<class OtherT,
           COORD_REQUIRES(std::is_convertible<OtherT,T>::value)
           >
  COORD_ANNOTATION
  named_array_element(const named_array_element<OtherT,1>& other)
    : named_array_element(other.y)
  {}

  T y;
};

template<class T>
struct named_array_element<T,2>
{
  named_array_element() = default;

  named_array_element(const named_array_element&) = default;

  COORD_ANNOTATION
  explicit named_array_element(const T& value) : z(value) {}

  // converting constructor
  template<class OtherT,
           COORD_REQUIRES(std::is_convertible<OtherT,T>::value)
           >
  COORD_ANNOTATION
  named_array_element(const named_array_element<OtherT,2>& other)
    : named_array_element(other.z)
  {}

  T z;
};

template<class T>
struct named_array_element<T,3>
{
  named_array_element() = default;

  named_array_element(const named_array_element&) = default;

  COORD_ANNOTATION
  explicit named_array_element(const T& value) : w(value) {}

  // converting constructor
  template<class OtherT,
           COORD_REQUIRES(std::is_convertible<OtherT,T>::value)
           >
  COORD_ANNOTATION
  named_array_element(const named_array_element<OtherT,3>& other)
    : named_array_element(other.w)
  {}

  T w;
};


template<class T, class Indices>
struct named_array_base;

template<class T, size_t... Indices>
struct named_array_base<T, index_sequence<Indices...>> : named_array_element<T,Indices>...
{
  named_array_base() = default;

  named_array_base(const named_array_base&) = default;

  COORD_ANNOTATION
  named_array_base(std::initializer_list<T> values)
    : named_array_element<T,Indices>(values.begin()[Indices])...
  {}

  // converting constructor
  template<class OtherT,
           COORD_REQUIRES(std::is_convertible<OtherT,T>::value)
          >
  COORD_ANNOTATION
  named_array_base(const named_array_base<OtherT, index_sequence<Indices...>>& other)
    : named_array_element<T,Indices>(other)...
  {}
};


// a named_array is an array where each element has its own name, e.g. [x, y, z, w]
template<class T, size_t N>
struct named_array : named_array_base<T,make_index_sequence<N>>
{
  static_assert(0 < N && N < 5, "named_array's size must be at least one and less than five.");

  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = pointer;
  using const_iterator = const_pointer;

  named_array() = default;

  named_array(const named_array&) = default;

  COORD_ANNOTATION
  named_array(std::initializer_list<T> values)
    : named_array_base<T,make_index_sequence<N>>(values)
  {}

  // converting constructor
  template<class OtherT,
           COORD_REQUIRES(std::is_convertible<OtherT,value_type>::value)
          >
  COORD_ANNOTATION
  named_array(const named_array<OtherT, N>& other)
    : named_array_base<T,make_index_sequence<N>>(other)
  {}
  
  COORD_ANNOTATION
  reference operator[](size_type pos)
  {
    return begin()[pos];
  }
  
  COORD_ANNOTATION
  const_reference operator[](size_type pos) const
  {
    return begin()[pos];
  }
  
  COORD_ANNOTATION
  reference front()
  {
    return *begin();
  }
  
  COORD_ANNOTATION
  const_reference front() const
  {
    return *begin();
  }
  
  COORD_ANNOTATION
  reference back()
  {
    // return *rbegin();
    return operator[](N-1);
  }
  
  COORD_ANNOTATION
  const_reference back() const
  {
    // return *rbegin();
    return operator[](N-1);
  }
  
  COORD_ANNOTATION
  T* data()
  {
    return &this->x;
  }
  
  COORD_ANNOTATION
  const T* data() const
  {
    return &this->x;
  }
  
  COORD_ANNOTATION
  iterator begin()
  {
    return data();
  }
  
  COORD_ANNOTATION
  const_iterator begin() const
  {
    return data();
  }
  
  COORD_ANNOTATION
  const_iterator cbegin()
  {
    return begin();
  }
  
  COORD_ANNOTATION
  const_iterator cbegin() const
  {
    return begin();
  }
  
  COORD_ANNOTATION
  iterator end()
  {
    return data() + size();
  }
  
  COORD_ANNOTATION
  const_iterator end() const
  {
    return data() + size();
  }
  
  COORD_ANNOTATION
  const_iterator cend()
  {
    return end();
  }
  
  COORD_ANNOTATION
  const_iterator cend() const
  {
    return end();
  }
  
  COORD_ANNOTATION
  constexpr bool empty() const
  {
    return size() == 0;
  }
  
  COORD_ANNOTATION
  constexpr size_type size() const
  {
    return N;
  }
  
  COORD_ANNOTATION
  constexpr size_type max_size() const
  {
    return size();
  }
  
  COORD_ANNOTATION
  void fill(const T& value)
  {
    for(auto& e : *this)
    {
      e = value;
    }
  }
  
  COORD_ANNOTATION
  void swap(named_array& other)
  {
    for(size_type i = 0; i < size(); ++i)
    {
      detail::custom_swap((*this)[i], other[i]);
    }
  }


  template<std::size_t I, COORD_REQUIRES(I < N)>
  COORD_ANNOTATION
  T& get() &
  {
    return operator[](I);
  }
  
  
  template<std::size_t I, COORD_REQUIRES(I < N)>
  COORD_ANNOTATION
  const T& get() const &
  {
    return operator[](I);
  }
  
  
  template<std::size_t I, COORD_REQUIRES(I < N)>
  COORD_ANNOTATION
  T&& get() &&
  {
    return std::move(operator[](I));
  }
};


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


// specialize tuple-related functionality for COORD_NAMESPACE::detail::named_array
namespace std
{


template<class T, std::size_t N>
struct tuple_size<COORD_NAMESPACE::detail::named_array<T,N>> : std::integral_constant<std::size_t, N> {};


template<std::size_t I, class T, std::size_t N>
struct tuple_element<I, COORD_NAMESPACE::detail::named_array<T,N>>
{
  using type = T;
};


} // end std


#include "epilogue.hpp"

