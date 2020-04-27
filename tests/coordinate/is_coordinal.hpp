#include <utility>
#include <tuple>
#include <array>
#include <coord/coordinate/is_coordinal.hpp>


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


void test_is_coordinal()
{
  // test some coordinates
  static_assert(coord::is_coordinal<has_member_functions>::value, "Error.");

  static_assert(coord::is_coordinal<int>::value, "Error.");
  static_assert(coord::is_coordinal<unsigned int>::value, "Error.");
  static_assert(coord::is_coordinal<std::size_t>::value, "Error.");
  static_assert(coord::is_coordinal<std::tuple<char>>::value, "Error.");

  static_assert(coord::is_coordinal<float>::value, "Error.");
  static_assert(coord::is_coordinal<double>::value, "Error.");
  static_assert(coord::is_coordinal<std::tuple<float>>::value, "Error.");
  static_assert(coord::is_coordinal<std::tuple<double>>::value, "Error.");

  static_assert(coord::is_coordinal<std::pair<int,int>>::value, "Error.");
  static_assert(coord::is_coordinal<std::tuple<int>>::value, "Error.");
  static_assert(coord::is_coordinal<std::tuple<int,unsigned int>>::value, "Error.");
  static_assert(coord::is_coordinal<std::tuple<int,unsigned int,std::size_t>>::value, "Error.");
  static_assert(coord::is_coordinal<std::array<std::size_t,3>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(coord::is_coordinal<std::pair<int2,uint3>>::value, "Error.");
  static_assert(coord::is_coordinal<std::tuple<int2,uint3,std::size_t>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(coord::is_coordinal<uint2x3>::value, "Error.");

  // test some non-coordinates
  static_assert(!coord::is_coordinal<std::tuple<int, char*>>::value, "Error.");
  static_assert(!coord::is_coordinal<std::tuple<float&,float>>::value, "Error.");
}

