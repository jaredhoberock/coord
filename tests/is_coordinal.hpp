#include <utility>
#include <tuple>
#include <array>
#include <coord/coordinal.hpp>
#include <coord/point.hpp>


struct has_member_functions
{
  static constexpr std::size_t rank()
  {
    return 4;
  }

  template<std::size_t i>
  int& element()
  {
    return a[i];
  }

  int a[4];
};


void test_is_coordinal()
{
  // test some coordinates
  static_assert(coord::is_coordinal_v<has_member_functions>, "Error.");

  static_assert(coord::is_coordinal_v<int>, "Error.");
  static_assert(coord::is_coordinal_v<unsigned int>, "Error.");
  static_assert(coord::is_coordinal_v<std::size_t>, "Error.");
  static_assert(coord::is_coordinal_v<std::tuple<char>>, "Error.");

  static_assert(coord::is_coordinal_v<float>, "Error.");
  static_assert(coord::is_coordinal_v<double>, "Error.");
  static_assert(coord::is_coordinal_v<std::tuple<float>>, "Error.");
  static_assert(coord::is_coordinal_v<std::tuple<double>>, "Error.");

  static_assert(coord::is_coordinal_v<std::pair<int,int>>, "Error.");
  static_assert(coord::is_coordinal_v<std::tuple<int>>, "Error.");
  static_assert(coord::is_coordinal_v<std::tuple<int,unsigned int>>, "Error.");
  static_assert(coord::is_coordinal_v<std::tuple<int,unsigned int,std::size_t>>, "Error.");
  static_assert(coord::is_coordinal_v<std::array<std::size_t,3>>, "Error.");
  static_assert(coord::is_coordinal_v<coord::float2>, "Error");
  static_assert(coord::is_coordinal_v<coord::uint3>, "Error");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(coord::is_coordinal_v<std::pair<int2,uint3>>, "Error.");
  static_assert(coord::is_coordinal_v<std::tuple<int2,uint3,std::size_t>>, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(coord::is_coordinal_v<uint2x3>, "Error.");

  // test some non-coordinates
  static_assert(!coord::is_coordinal_v<std::tuple<int, char*>>, "Error.");
  static_assert(!coord::is_coordinal_v<std::tuple<float&,float>>, "Error.");
}

