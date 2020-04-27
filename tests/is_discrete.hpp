#include <utility>
#include <tuple>
#include <array>
#include <coord/is_discrete.hpp>

void test_is_discrete()
{
  // test some discrete coordinates
  static_assert(coord::is_discrete<int>::value, "Error.");
  static_assert(coord::is_discrete<unsigned int>::value, "Error.");
  static_assert(coord::is_discrete<std::size_t>::value, "Error.");
  static_assert(coord::is_discrete<std::tuple<char>>::value, "Error.");

  static_assert(coord::is_discrete<std::pair<int,int>>::value, "Error.");
  static_assert(coord::is_discrete<std::tuple<int>>::value, "Error.");
  static_assert(coord::is_discrete<std::tuple<int,unsigned int>>::value, "Error.");
  static_assert(coord::is_discrete<std::tuple<int,unsigned int,std::size_t>>::value, "Error.");
  static_assert(coord::is_discrete<std::array<std::size_t,3>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(coord::is_discrete<std::pair<int2,uint3>>::value, "Error.");
  static_assert(coord::is_discrete<std::tuple<int2,uint3,std::size_t>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(coord::is_discrete<uint2x3>::value, "Error.");


  // test some types that are not discrete coordinates
  using float2 = std::pair<float,float>;
  using double3 = std::tuple<double, double, double>;

  static_assert(!coord::is_discrete<float>::value, "Error.");
  static_assert(!coord::is_discrete<void>::value, "Error.");
  static_assert(!coord::is_discrete<std::pair<float,int>>::value, "Error.");
  static_assert(!coord::is_discrete<float2>::value, "Error.");
  static_assert(!coord::is_discrete<double3>::value, "Error.");
  static_assert(!coord::is_discrete<int*>::value, "Error.");
}

