#include <utility>
#include <tuple>
#include <array>
#include <coord/shape/is_shape.hpp>
#include <coord/point.hpp>

void test_is_shape()
{
  // test some shapes
  static_assert(coord::is_shape<int>::value, "Error.");
  static_assert(coord::is_shape<unsigned int>::value, "Error.");
  static_assert(coord::is_shape<std::size_t>::value, "Error.");
  static_assert(coord::is_shape<std::tuple<char>>::value, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(coord::is_shape<int2>::value, "Error.");
  static_assert(coord::is_shape<coord::int2>::value, "Error.");
  static_assert(coord::is_shape<uint2>::value, "Error.");
  static_assert(coord::is_shape<coord::uint2>::value, "Error.");
  static_assert(coord::is_shape<std::tuple<int>>::value, "Error.");
  static_assert(coord::is_shape<std::tuple<int,unsigned int>>::value, "Error.");
  static_assert(coord::is_shape<std::tuple<int,unsigned int,std::size_t>>::value, "Error.");
  static_assert(coord::is_shape<std::array<std::size_t,3>>::value, "Error.");

  static_assert(coord::is_shape<std::pair<int2,uint3>>::value, "Error.");
  static_assert(coord::is_shape<std::tuple<int2,uint3,std::size_t>>::value, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(coord::is_shape<uint2x3>::value, "Error.");


  // test some non-shapes
  static_assert(!coord::is_shape<float>::value, "Error.");
  static_assert(!coord::is_shape<void>::value, "Error.");
  static_assert(!coord::is_shape<std::pair<float,int>>::value, "Error.");
  static_assert(!coord::is_shape<int*>::value, "Error.");
}

