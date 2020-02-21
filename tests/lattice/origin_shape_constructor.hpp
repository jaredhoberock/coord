#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_origin_shape_constructor()
{
  using namespace coord;

  {
    int expected_origin = 13;
    int expected_shape = 7;

    lattice<int> l(expected_origin, expected_shape);

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }

  {
    int2 expected_origin = {13,7};
    int2 expected_shape = {1,2};

    lattice<int2> l(expected_origin, expected_shape);

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }

  {
    int3 expected_origin = {13,7,42};
    int3 expected_shape = {1,2,3};

    lattice<int3> l(expected_origin, expected_shape);

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }
}

