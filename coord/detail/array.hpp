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

#include <cstdint>
#include <utility>
#include "custom_swap.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{


template<class T, std::size_t N>
struct array
{
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = pointer;
  using const_iterator = const_pointer;

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
    return elems_;
  }

  COORD_ANNOTATION
  const T* data() const
  {
    return elems_;
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
  void swap(array& other)
  {
    for(size_type i = 0; i < size(); ++i)
    {
      detail::custom_swap((*this)[i], other[i]);
    }
  }

  value_type elems_[N > 0 ? N : 1];
};


template<class T, std::size_t N>
COORD_ANNOTATION
bool operator==(const array<T,N>& lhs,  const array<T,N>& rhs)
{
  for(std::size_t i = 0; i < N; ++i)
  {
    if(lhs[i] != rhs[i]) return false;
  }

  return true;
}


template<std::size_t I, class T, std::size_t N, COORD_REQUIRES(I < N)>
COORD_ANNOTATION
T& get(array<T,N>& a)
{
  return a[I];
}


template<std::size_t I, class T, std::size_t N, COORD_REQUIRES(I < N)>
COORD_ANNOTATION
const T& get(const array<T,N>& a)
{
  return a[I];
}


template<std::size_t I, class T, std::size_t N, COORD_REQUIRES(I < N)>
COORD_ANNOTATION
T&& get(array<T,N>&& a)
{
  return std::move(a[I]);
}


// XXX other relational operators here


template<class T, std::size_t N>
COORD_ANNOTATION
void swap(array<T,N>& a, array<T,N>& b)
{
  a.swap(b);
}


} // end detail


COORD_NAMESPACE_CLOSE_BRACE


// specialize tuple-related functionality for COORD_NAMESPACE::detail::array
namespace std
{


template<class >
class tuple_size;

template<class T, std::size_t N>
class tuple_size<COORD_NAMESPACE::detail::array<T,N>> : std::integral_constant<std::size_t, N> {};


template<std::size_t I, class T>
class tuple_element;

template<std::size_t I, class T, std::size_t N>
class tuple_element<I, COORD_NAMESPACE::detail::array<T,N>>
{
  public:
    using type = T;
};


} // end std


#include "epilogue.hpp"

