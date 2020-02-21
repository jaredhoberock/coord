#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_rank()
{
  using namespace coord;

  assert(1 == lattice<int>::rank());
  assert(2 == lattice<int2>::rank());
  assert(3 == lattice<int3>::rank());
  assert(4 == lattice<int4>::rank());

  assert(1 == lattice<unsigned int>::rank());
  assert(2 == lattice<uint2>::rank());
  assert(3 == lattice<uint3>::rank());
  assert(4 == lattice<uint4>::rank());
}

