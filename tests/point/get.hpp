#include <array>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <coord/point.hpp>


constexpr bool all_true()
{
  return true;
}

template<class Boolean, class... Booleans>
constexpr bool all_true(Boolean b, Booleans... bs)
{
  return b and all_true(bs...);
}


template<class T>
const T& const_ref(const T& ref)
{
  return ref;
}


template<class T>
struct is_const_reference : std::false_type {};

template<class T>
struct is_const_reference<const T&> : std::true_type {};


template<class T, std::size_t... Indices>
void test()
{
  coord::point<T, sizeof...(Indices)> p(Indices...);

  assert(all_true(Indices == coord::get<Indices>(p)...));

  static_assert(all_true(std::is_lvalue_reference<decltype(coord::get<Indices>(p))>::value...), "Error.");
  static_assert(all_true(std::is_rvalue_reference<decltype(coord::get<Indices>(std::move(p)))>::value...), "Error.");
  static_assert(all_true(is_const_reference<decltype(coord::get<Indices>(const_ref(p)))>::value...), "Error.");
}


void test_get()
{
  test<char, 0>();
  test<char, 0, 1>();
  test<char, 0, 1, 2>();
  test<char, 0, 1, 2, 3>();
  test<char, 0, 1, 2, 3, 4>();

  test<unsigned char, 0>();
  test<unsigned char, 0, 1>();
  test<unsigned char, 0, 1, 2>();
  test<unsigned char, 0, 1, 2, 3>();
  test<unsigned char, 0, 1, 2, 3, 4>();

  test<short, 0>();
  test<short, 0, 1>();
  test<short, 0, 1, 2>();
  test<short, 0, 1, 2, 3>();
  test<short, 0, 1, 2, 3, 4>();

  test<unsigned short, 0>();
  test<unsigned short, 0, 1>();
  test<unsigned short, 0, 1, 2>();
  test<unsigned short, 0, 1, 2, 3>();
  test<unsigned short, 0, 1, 2, 3, 4>();

  test<int, 0>();
  test<int, 0, 1>();
  test<int, 0, 1, 2>();
  test<int, 0, 1, 2, 3>();
  test<int, 0, 1, 2, 3, 4>();

  test<unsigned int, 0>();
  test<unsigned int, 0, 1>();
  test<unsigned int, 0, 1, 2>();
  test<unsigned int, 0, 1, 2, 3>();
  test<unsigned int, 0, 1, 2, 3, 4>();

  test<std::size_t, 0>();
  test<std::size_t, 0, 1>();
  test<std::size_t, 0, 1, 2>();
  test<std::size_t, 0, 1, 2, 3>();
  test<std::size_t, 0, 1, 2, 3, 4>();

  test<float, 0>();
  test<float, 0, 1>();
  test<float, 0, 1, 2>();
  test<float, 0, 1, 2, 3>();
  test<float, 0, 1, 2, 3, 4>();

  test<double, 0>();
  test<double, 0, 1>();
  test<double, 0, 1, 2>();
  test<double, 0, 1, 2, 3>();
  test<double, 0, 1, 2, 3, 4>();
}

