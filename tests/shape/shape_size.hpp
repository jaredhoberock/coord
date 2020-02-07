#include <utility>
#include <tuple>
#include <coord/shape/shape_size.hpp>

void test_shape_size()
{
  // test some shapes
  static_assert(1 == coord::shape_size<int>::value, "Error.");
  static_assert(1 == coord::shape_size<unsigned int>::value, "Error.");
  static_assert(1 == coord::shape_size<std::size_t>::value, "Error.");
  static_assert(1 == coord::shape_size<std::tuple<char>>::value, "Error.");

  static_assert(2 == coord::shape_size<std::pair<int,int>>::value, "Error.");
  static_assert(2 == coord::shape_size<std::tuple<int,unsigned int>>::value, "Error.");
  static_assert(3 == coord::shape_size<std::tuple<int,unsigned int,std::size_t>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(2 == coord::shape_size<std::pair<int2,uint3>>::value, "Error.");
  static_assert(3 == coord::shape_size<std::tuple<int2,uint3,std::size_t>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(2 == coord::shape_size<uint2x3>::value, "Error.");
}

