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

#include <iostream>
#include <tuple>
#include <type_traits>
#include "tuple_utility.hpp"


COORD_NAMESPACE_OPEN_BRACE


namespace detail
{

template<typename Derived>
class arithmetic_tuple_facade;


// an arithmetic tuple is a tuple-like type whose element types all have arithmetic operators
// XXX the definition of this class doesn't actually implement the above definition
template<class T>
struct is_arithmetic_tuple : std::is_base_of<arithmetic_tuple_facade<T>, T> {};


// the purpose of this class is to act as a base class for arithmetic tuple types
// by deriving from this class, the Derived class inherits arithmetic operators
template<typename Derived>
  class arithmetic_tuple_facade
{
  private:
    struct assign
    {
      template<typename T1, typename T2>
      COORD_ANNOTATION
      T1& operator()(T1 &lhs, const T2& rhs) const
      {
        return lhs = rhs;
      }
    };

    struct plus_assign
    {
      template<typename T1, typename T2>
      COORD_ANNOTATION
      T1& operator()(T1 &lhs, const T2& rhs) const
      {
        return lhs += rhs;
      }
    };

    struct minus_assign
    {
      template<typename T1, typename T2>
      COORD_ANNOTATION
      T1& operator()(T1 &lhs, const T2& rhs) const
      {
        return lhs -= rhs;
      }
    };

    struct multiplies_assign
    {
      template<typename T1, typename T2>
      COORD_ANNOTATION
      T1& operator()(T1 &lhs, const T2& rhs) const
      {
        return lhs *= rhs;
      }
    };

    template<typename T>
    struct assign_constant
    {
      T c;

      template<typename U>
      COORD_ANNOTATION
      U& operator()(U& x) const
      {
        return x = c;
      }
    };

    template<typename T>
    struct multiplies_assign_constant
    {
      T c;

      template<typename U>
      COORD_ANNOTATION
      U& operator()(U& x) const
      {
        return x *= c;
      }
    };

    struct divides_assign
    {
      template<typename T1, typename T2>
      COORD_ANNOTATION
      T1& operator()(T1 &lhs, const T2& rhs) const
      {
        return lhs /= rhs;
      }
    };

    template<typename T>
    struct divides_assign_constant
    {
      T c;

      template<typename U>
      COORD_ANNOTATION
      U& operator()(U& x) const
      {
        return x /= c;
      }
    };

    struct modulus_assign
    {
      template<typename T1, typename T2>
      COORD_ANNOTATION
      T1& operator()(T1 &lhs, const T2& rhs) const
      {
        return lhs %= rhs;
      }
    };

    struct make_derived
    {
      template<class... Args>
      COORD_ANNOTATION
      Derived operator()(Args&&... args) const
      {
        return Derived{std::forward<Args>(args)...};
      }
    };

    COORD_ANNOTATION Derived& derived()
    {
      return static_cast<Derived&>(*this);
    }

    COORD_ANNOTATION const Derived& derived() const
    {
      return static_cast<const Derived&>(*this);
    }

  protected:
    template<class Arithmetic,
             COORD_REQUIRES(std::is_arithmetic<Arithmetic>::value)
             >
    COORD_ANNOTATION
    void fill(const Arithmetic& val)
    {
      return tu::tuple_for_each(assign_constant<Arithmetic>{val}, derived());
    }

    template<class ArithmeticTuple,
             COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
            >
    COORD_ANNOTATION
    void copy(const ArithmeticTuple& src)
    {
      return tu::tuple_for_each(assign{}, derived(), src);
    }

  public:

  // fused op-assignment
  template<class ArithmeticTuple,
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived& operator*=(const ArithmeticTuple& rhs)
  {
    tu::tuple_for_each(multiplies_assign{}, derived(), rhs);
    return derived();
  }

  template<class ArithmeticTuple,
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived& operator/=(const ArithmeticTuple& rhs)
  {
    tu::tuple_for_each(divides_assign{}, derived(), rhs);
    return derived();
  }

  template<class ArithmeticTuple,
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived& operator%=(const ArithmeticTuple& rhs)
  {
    tu::tuple_for_each(modulus_assign{}, derived(), rhs);
    return derived();
  }

  template<class ArithmeticTuple,
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived& operator+=(const ArithmeticTuple& rhs)
  {
    tu::tuple_for_each(plus_assign{}, derived(), rhs);
    return derived();
  }

  template<class ArithmeticTuple,
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived& operator-=(const ArithmeticTuple& rhs)
  {
    tu::tuple_for_each(minus_assign{}, derived(), rhs);
    return derived();
  }


  // multiply by scalar
  template<class Arithmetic,
           COORD_REQUIRES(std::is_arithmetic<Arithmetic>::value)
          >
  COORD_ANNOTATION
  Derived& operator*=(const Arithmetic& rhs)
  {
    tu::tuple_for_each(multiplies_assign_constant<Arithmetic>(rhs), derived());
    return derived();
  }

  // divide by scalar
  template<class Arithmetic,
           COORD_REQUIRES(std::is_arithmetic<Arithmetic>::value)
          >
  Derived& operator/=(const Arithmetic& rhs)
  {
    tu::tuple_for_each(divides_assign_constant<Arithmetic>(rhs), derived());
    return derived();
  }


  // XXX the result type of the following binary operators should involve common_type of the
  //     individual elements rather than simply being the Derived type


  // plus tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived operator+(const ArithmeticTuple& rhs) const
  {
    Derived result = derived();
    static_cast<arithmetic_tuple_facade&>(result) += rhs;
    return result;
  }

  // minus tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived operator-(const ArithmeticTuple& rhs) const
  {
    Derived result = derived();
    static_cast<arithmetic_tuple_facade&>(result) -= rhs;
    return result;
  }

  // multiply by tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived operator*(const ArithmeticTuple& rhs) const
  {
    Derived result = derived();
    static_cast<arithmetic_tuple_facade&>(result) *= rhs;
    return result;
  }

  // divide by tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived operator/(const ArithmeticTuple& rhs) const
  {
    Derived result = derived();
    static_cast<arithmetic_tuple_facade&>(result) /= rhs;
    return result;
  }

  // modulus by tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  Derived operator%(const ArithmeticTuple& rhs) const
  {
    Derived result = derived();
    static_cast<arithmetic_tuple_facade&>(result) %= rhs;
    return result;
  }


  // equals tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  bool operator==(const ArithmeticTuple& rhs) const
  {
    return tu::tuple_equal(derived(), rhs);
  }


  // not equals tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  bool operator!=(const ArithmeticTuple& rhs) const
  {
    return !operator==(rhs);
  }


  // less than tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  bool operator<(const ArithmeticTuple& rhs) const
  {
    return tu::tuple_lexicographical_compare(derived(), rhs);
  }

  // greater than tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  bool operator>(const ArithmeticTuple& rhs) const
  {
    return tu::tuple_lexicographical_compare(rhs, derived());
  }

  // less than or equal to tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  bool operator<=(const ArithmeticTuple& rhs) const
  {
    return !operator>(rhs);
  }

  // greater than or equal to tuple
  template<class ArithmeticTuple,
           COORD_REQUIRES(is_arithmetic_tuple<ArithmeticTuple>::value),
           COORD_REQUIRES(std::tuple_size<Derived>::value == std::tuple_size<ArithmeticTuple>::value)
          >
  COORD_ANNOTATION
  bool operator>=(const ArithmeticTuple& rhs) const
  {
    return !operator<(rhs);
  }

  friend std::ostream& operator<<(std::ostream& os, const arithmetic_tuple_facade& t)
  {
    os << "{";
    tu::tuple_print(t.derived(), os, ", ");
    os << "}";

    return os;
  }
};


} // end detail


COORD_NAMESPACE_CLOSE_BRACE

#include "epilogue.hpp"

