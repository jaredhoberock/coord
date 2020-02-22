#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_empty()
{
  using namespace coord;

  {
    int origin = 13;
    int shape = 7;

    lattice<int> l(origin, shape);

    assert(!l.empty());
    assert((lattice<int>{}.empty()));
    assert((lattice<int>{origin, {}}.empty()));
  }

  {
    int2 origin = {13,7};
    int2 shape = {1,2};

    lattice<int2> l(origin, shape);

    assert(!l.empty());
    assert((lattice<int2>{}.empty()));
    assert((lattice<int2>{origin, {}}.empty()));
  }

  {
    int3 origin = {13,7,42};
    int3 shape = {1,2,3};

    lattice<int3> l(origin, shape);

    assert(!l.empty());
    assert((lattice<int3>{}.empty()));
    assert((lattice<int3>{origin, {}}.empty()));
  }
}

