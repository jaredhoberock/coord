#include <utility>
#include <tuple>
#include <array>
#include <coord/discrete.hpp>
#include <coord/point.hpp>

void test_discrete()
{
  // test some discrete coordinates
  static_assert(coord::is_discrete_v<int>, "Error.");
  static_assert(coord::is_discrete_v<unsigned int>, "Error.");
  static_assert(coord::is_discrete_v<std::size_t>, "Error.");
  static_assert(coord::is_discrete_v<std::tuple<char>>, "Error.");
  static_assert(coord::is_discrete_v<coord::point<int,1>>, "Error.");
  static_assert(coord::are_discrete_v<int, unsigned int, std::size_t, std::tuple<char>, coord::point<int,1>>, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(coord::is_discrete_v<int2>, "Error.");
  static_assert(coord::is_discrete_v<coord::int2>, "Error.");
  static_assert(coord::is_discrete_v<uint3>, "Error.");
  static_assert(coord::is_discrete_v<coord::uint3>, "Error.");
  static_assert(coord::is_discrete_v<std::tuple<int>>, "Error.");
  static_assert(coord::is_discrete_v<std::tuple<int,unsigned int>>, "Error.");
  static_assert(coord::is_discrete_v<std::tuple<int,unsigned int,std::size_t>>, "Error.");
  static_assert(coord::is_discrete_v<std::array<std::size_t,3>>, "Error.");

  static_assert(coord::is_discrete_v<std::pair<int2,uint3>>, "Error.");
  static_assert(coord::is_discrete_v<std::tuple<int2,uint3,std::size_t>>, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(coord::is_discrete_v<uint2x3>, "Error.");


  // test some types that are not discrete coordinates
  using float2 = std::pair<float,float>;
  using double3 = std::tuple<double, double, double>;

  static_assert(!coord::is_discrete_v<float>, "Error.");
  static_assert(!coord::is_discrete_v<void>, "Error.");
  static_assert(!coord::is_discrete_v<std::pair<float,int>>, "Error.");
  static_assert(!coord::is_discrete_v<float2>, "Error.");
  static_assert(!coord::is_discrete_v<coord::float2>, "Error.");
  static_assert(!coord::is_discrete_v<double3>, "Error.");
  static_assert(!coord::is_discrete_v<coord::double3>, "Error.");
  static_assert(!coord::is_discrete_v<int*>, "Error.");
  static_assert(!coord::are_discrete_v<int,float>, "Error.");
}

