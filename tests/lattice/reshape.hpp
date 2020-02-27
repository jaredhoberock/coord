#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_reshape()
{
  using namespace coord;

  {
    lattice<int> l{13};

    int expected = 7;
    l.reshape(expected);

    assert(expected == l.shape());
  }

  {
    lattice<int2> l{{13,7}};

    int2 expected{1,2};
    l.reshape(expected);

    assert(expected == l.shape());
  }

  {
    lattice<int3> l{{13,7,42}};

    int3 expected{1,2,3};
    l.reshape(expected);

    assert(expected == l.shape());
  }
}

