#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_shape_constructor()
{
  using namespace coord;

  {
    int expected_origin{0};
    int expected_shape{13};

    lattice<int> l{expected_shape};

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }

  {
    int2 expected_origin{0,0};
    int2 expected_shape{13,7};

    lattice<int2> l{expected_shape};

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }

  {
    int3 expected_origin{0,0,0};
    int3 expected_shape{13,7,42};

    lattice<int3> l{expected_shape};

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }
}

