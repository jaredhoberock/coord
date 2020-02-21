#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_initializer_list_constructor()
{
  using namespace coord;

  {
    int expected_origin{0};
    int expected_shape{13};

    // XXX when rank == 1, lattice's shape ctor is selected
    //     how to enable the initializer_list ctor?
    lattice<int> l{expected_shape};

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }

  {
    int2 expected_origin{0,0};
    int2 expected_shape{13,7};

    lattice<int2> l = {expected_shape[0], expected_shape[1]};

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }

  {
    int3 expected_origin{0,0,0};
    int3 expected_shape{13,7,42};

    lattice<int3> l = {expected_shape[0], expected_shape[1], expected_shape[2]};

    assert(expected_origin == l.origin());
    assert(expected_shape == l.shape());
  }
}

