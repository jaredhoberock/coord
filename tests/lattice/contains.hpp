#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_contains()
{
  using namespace coord;

  {
    int origin = 13;
    int shape = 7;

    lattice<int> l(origin, shape);

    for(int pt = origin; pt != origin + shape; ++pt)
    {
      assert(l.contains(pt));
    }

    assert(!l.contains(origin + shape));
  }

  {
    int2 origin = {13,7};
    int2 shape = {3,2};

    lattice<int2> l(origin, shape);

    for(int i = origin.x; i != origin.x + shape.x; ++i)
    {
      for(int j = origin.y; j != origin.y + shape.y; ++j)
      {
        assert(l.contains({i,j}));
      }
    }

    assert(!l.contains(origin + shape));
  }

  {
    int3 origin = {13,7,42};
    int3 shape = {1,2,3};

    lattice<int3> l(origin, shape);

    for(int i = origin.x; i != origin.x + shape.x; ++i)
    {
      for(int j = origin.y; j != origin.y + shape.y; ++j)
      {
        for(int k = origin.z; k != origin.z + shape.z; ++k)
        {
          assert(l.contains({i,j,k}));
        }
      }
    }

    assert(!l.contains(origin + shape));
  }
}

