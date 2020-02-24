#include <utility>
#include <tuple>
#include <array>
#include <coord/index/index_element.hpp>

void test_index_element()
{
  // test some indexs
  static_assert(std::is_same<int, coord::index_element_t<0, int>>::value, "Error.");
  static_assert(std::is_same<unsigned int, coord::index_element_t<0, unsigned int>>::value, "Error.");
  static_assert(std::is_same<std::size_t, coord::index_element_t<0, std::size_t>>::value, "Error.");
  static_assert(std::is_same<char, coord::index_element_t<0, std::tuple<char>>>::value, "Error.");

  static_assert(std::is_same<int, coord::index_element_t<0, std::pair<int,int>>>::value, "Error.");
  static_assert(std::is_same<int, coord::index_element_t<1, std::pair<int,int>>>::value, "Error.");

  static_assert(std::is_same<int, coord::index_element_t<0, std::tuple<int, unsigned int>>>::value, "Error.");
  static_assert(std::is_same<unsigned int, coord::index_element_t<1, std::tuple<int, unsigned int>>>::value, "Error.");

  static_assert(std::is_same<int, coord::index_element_t<0, std::array<int, 2>>>::value, "Error.");
  static_assert(std::is_same<int, coord::index_element_t<1, std::array<int, 2>>>::value, "Error.");
  
  static_assert(std::is_same<int, coord::index_element_t<0, std::tuple<int,unsigned int,std::size_t>>>::value, "Error.");
  static_assert(std::is_same<unsigned int, coord::index_element_t<1, std::tuple<int,unsigned int,std::size_t>>>::value, "Error.");
  static_assert(std::is_same<std::size_t, coord::index_element_t<2, std::tuple<int,unsigned int,std::size_t>>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(std::is_same<int2, coord::index_element_t<0, std::pair<int2,uint3>>>::value, "Error.");
  static_assert(std::is_same<uint3, coord::index_element_t<1, std::pair<int2,uint3>>>::value, "Error.");

  static_assert(std::is_same<int2, coord::index_element_t<0, std::tuple<int2,uint3,std::size_t>>>::value, "Error.");
  static_assert(std::is_same<uint3, coord::index_element_t<1, std::tuple<int2,uint3,std::size_t>>>::value, "Error.");
  static_assert(std::is_same<std::size_t, coord::index_element_t<2, std::tuple<int2,uint3,std::size_t>>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(std::is_same<uint3, coord::index_element_t<0, uint2x3>>::value, "Error.");
  static_assert(std::is_same<uint3, coord::index_element_t<1, uint2x3>>::value, "Error.");
}

