#include <utility>
#include <tuple>
#include <array>
#include <coord/coordinate/is_coordinate.hpp>


struct has_member_functions
{
  constexpr std::size_t rank()
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


void test_is_coordinate()
{
  // test some coordinates
  static_assert(coord::is_coordinate<has_member_functions>::value, "Error.");

  static_assert(coord::is_coordinate<int>::value, "Error.");
  static_assert(coord::is_coordinate<unsigned int>::value, "Error.");
  static_assert(coord::is_coordinate<std::size_t>::value, "Error.");
  static_assert(coord::is_coordinate<std::tuple<char>>::value, "Error.");

  static_assert(coord::is_coordinate<float>::value, "Error.");
  static_assert(coord::is_coordinate<double>::value, "Error.");
  static_assert(coord::is_coordinate<std::tuple<float>>::value, "Error.");
  static_assert(coord::is_coordinate<std::tuple<double>>::value, "Error.");

  static_assert(coord::is_coordinate<std::pair<int,int>>::value, "Error.");
  static_assert(coord::is_coordinate<std::tuple<int>>::value, "Error.");
  static_assert(coord::is_coordinate<std::tuple<int,unsigned int>>::value, "Error.");
  static_assert(coord::is_coordinate<std::tuple<int,unsigned int,std::size_t>>::value, "Error.");
  static_assert(coord::is_coordinate<std::array<std::size_t,3>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(coord::is_coordinate<std::pair<int2,uint3>>::value, "Error.");
  static_assert(coord::is_coordinate<std::tuple<int2,uint3,std::size_t>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(coord::is_coordinate<uint2x3>::value, "Error.");

  // test some non-coordinates
  static_assert(!coord::is_coordinate<std::tuple<int, char*>>::value, "Error.");
  static_assert(!coord::is_coordinate<std::tuple<float&,float>>::value, "Error.");
}

