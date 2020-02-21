#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_default_constructor()
{
  using namespace coord;

  assert(lattice<int>{}.empty());
  assert(lattice<int2>{}.empty());
  assert(lattice<int3>{}.empty());
  assert(lattice<int4>{}.empty());

  assert(lattice<unsigned int>{}.empty());
  assert(lattice<uint2>{}.empty());
  assert(lattice<uint3>{}.empty());
  assert(lattice<uint4>{}.empty());
}

