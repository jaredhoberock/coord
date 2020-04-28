#include <cassert>
#include <coord/space_size.hpp>
#include <coord/point.hpp>
#include <tuple>

void test_space_size()
{
  using namespace coord;

  // 1D spaces
  assert(13 == space_size(13));
  assert(7 == space_size(7));
  assert(13 == space_size(int1(13)));
  assert(7 == space_size(int1(7)));
  assert(7 == space_size(std::make_tuple(7)));

  // 2D spaces
  assert(7 * 13 == space_size(int2(7,13)));
  assert(7 * 13 == space_size(std::make_tuple(7,13)));
  assert(7 * 13 == space_size(std::make_pair(7,13)));

  // 3D spaces
  assert(7 * 13 * 42 == space_size(int3(7,13,42)));
  assert(7 * 13 * 42 == space_size(std::make_tuple(7,13,42)));
  assert(7 * 13 * 42 == space_size(std::array<int,3>{7,13,42}));

  // nested spaces
  assert(7 * 13 * 42 == space_size(std::make_pair(7, std::make_pair(13, 42))));
  assert(7 * 13 * 42 == space_size(std::make_pair(std::make_pair(7, 13), 42)));
  assert(7 * 13 * 42 * 123 == space_size(std::make_pair(std::make_pair(7, 13), std::make_pair(42, 123))));
  assert(7 * 13 * 42 * 123 == space_size(std::make_pair(int2{7,13}, int2{42,123})));
  assert(7 * 13 * 42 * 123 == space_size(std::make_pair(7, int3{13,42,123})));
}

