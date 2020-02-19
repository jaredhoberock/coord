#include <utility>
#include <tuple>
#include <array>
#include <coord/shape/first_shape_element.hpp>

void test_first_shape_element()
{
  // test some shapes
  static_assert(std::is_same<int, coord::first_shape_element_t<int>>::value, "Error.");
  static_assert(std::is_same<unsigned int, coord::first_shape_element_t<unsigned int>>::value, "Error.");
  static_assert(std::is_same<std::size_t, coord::first_shape_element_t<std::size_t>>::value, "Error.");
  static_assert(std::is_same<char, coord::first_shape_element_t<std::tuple<char>>>::value, "Error.");

  static_assert(std::is_same<int, coord::first_shape_element_t<std::pair<int,int>>>::value, "Error.");

  static_assert(std::is_same<int, coord::first_shape_element_t<std::tuple<int, unsigned int>>>::value, "Error.");

  static_assert(std::is_same<int, coord::first_shape_element_t<std::array<int, 2>>>::value, "Error.");
  
  static_assert(std::is_same<int, coord::first_shape_element_t<std::tuple<int,unsigned int,std::size_t>>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(std::is_same<int2, coord::first_shape_element_t<std::pair<int2,uint3>>>::value, "Error.");

  static_assert(std::is_same<int2, coord::first_shape_element_t<std::tuple<int2,uint3,std::size_t>>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(std::is_same<uint3, coord::first_shape_element_t<uint2x3>>::value, "Error.");
}

