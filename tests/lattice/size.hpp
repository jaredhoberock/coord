#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_size()
{
  using namespace coord;

  {
    int origin = 13;
    int shape = 7;

    lattice<int> l(origin, shape);

    assert(shape == l.size());
  }

  {
    int2 origin = {13,7};
    int2 shape = {1,2};

    lattice<int2> l(origin, shape);

    assert(shape.x * shape.y == l.size());
  }

  {
    int3 origin = {13,7,42};
    int3 shape = {1,2,3};

    lattice<int3> l(origin, shape);

    assert(shape.x * shape.y * shape.z == l.size());
  }
}

