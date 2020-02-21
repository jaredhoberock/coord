#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_copy_constructor()
{
  using namespace coord;

  {
    lattice<int> expected{13};
    lattice<int> result{expected};

    assert(expected == result);
  }

  {
    lattice<int2> expected{{13,7}};
    lattice<int2> result{expected};

    assert(expected == result);
  }

  {
    lattice<int3> expected{{13,7,42}};
    lattice<int3> result{expected};

    assert(expected == result);
  }
}

