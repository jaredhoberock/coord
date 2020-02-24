#include <utility>
#include <tuple>
#include <coord/index/index_size.hpp>

void test_index_size()
{
  // test some indices
  static_assert(1 == coord::index_size<int>::value, "Error.");
  static_assert(1 == coord::index_size<unsigned int>::value, "Error.");
  static_assert(1 == coord::index_size<std::size_t>::value, "Error.");
  static_assert(1 == coord::index_size<std::tuple<char>>::value, "Error.");

  static_assert(2 == coord::index_size<std::pair<int,int>>::value, "Error.");
  static_assert(2 == coord::index_size<std::tuple<int,unsigned int>>::value, "Error.");
  static_assert(3 == coord::index_size<std::tuple<int,unsigned int,std::size_t>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(2 == coord::index_size<std::pair<int2,uint3>>::value, "Error.");
  static_assert(3 == coord::index_size<std::tuple<int2,uint3,std::size_t>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(2 == coord::index_size<uint2x3>::value, "Error.");
}

