#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_bracket_operator()
{
  using namespace coord;

  {
    int origin = 13;
    int shape = 7;

    lattice<int> l(origin, shape);

    for(int idx = 0; idx != l.shape(); ++idx)
    {
      assert(origin + idx == l[idx]);
    }
  }

  {
    int2 origin = {13,7};
    int2 shape = {3,2};

    lattice<int2> l(origin, shape);

    for(int i = 0; i != l.shape().x; ++i)
    {
      for(int j = 0; j != l.shape().y; ++j)
      {
        int2 idx{i,j};
        assert(origin + idx == l[idx]);
      }
    }
  }

  {
    int3 origin = {13,7,42};
    int3 shape = {1,2,3};

    lattice<int3> l(origin, shape);

    for(int i = 0; i != l.shape().x; ++i)
    {
      for(int j = 0; j != l.shape().y; ++j)
      {
        for(int k = 0; k != l.shape().z; ++k)
        {
          int3 idx{i,j,k};
          assert(origin + idx == l[idx]);
        }
      }
    }
  }
}

