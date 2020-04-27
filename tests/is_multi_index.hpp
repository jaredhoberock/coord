#include <utility>
#include <tuple>
#include <array>
#include <coord/is_multi_index.hpp>

void test_is_multi_index()
{
  // test some multi-indices
  static_assert(coord::is_multi_index<int>::value, "Error.");
  static_assert(coord::is_multi_index<unsigned int>::value, "Error.");
  static_assert(coord::is_multi_index<std::size_t>::value, "Error.");
  static_assert(coord::is_multi_index<std::tuple<char>>::value, "Error.");

  static_assert(coord::is_multi_index<std::pair<int,int>>::value, "Error.");
  static_assert(coord::is_multi_index<std::tuple<int>>::value, "Error.");
  static_assert(coord::is_multi_index<std::tuple<int,unsigned int>>::value, "Error.");
  static_assert(coord::is_multi_index<std::tuple<int,unsigned int,std::size_t>>::value, "Error.");
  static_assert(coord::is_multi_index<std::array<std::size_t,3>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(coord::is_multi_index<std::pair<int2,uint3>>::value, "Error.");
  static_assert(coord::is_multi_index<std::tuple<int2,uint3,std::size_t>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(coord::is_multi_index<uint2x3>::value, "Error.");


  // test some non-indices
  using float2 = std::pair<float,float>;
  using double3 = std::tuple<double, double, double>;

  static_assert(!coord::is_multi_index<float>::value, "Error.");
  static_assert(!coord::is_multi_index<void>::value, "Error.");
  static_assert(!coord::is_multi_index<std::pair<float,int>>::value, "Error.");
  static_assert(!coord::is_multi_index<float2>::value, "Error.");
  static_assert(!coord::is_multi_index<double3>::value, "Error.");
  static_assert(!coord::is_multi_index<int*>::value, "Error.");
}

