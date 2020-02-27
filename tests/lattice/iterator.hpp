#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_iterator()
{
  using namespace coord;

  {
    int origin = 13;
    int shape = 7;

    lattice<int> l(origin, shape);

    auto iter = l.begin();
    for(int i = 0; i != l.shape(); ++i, ++iter)
    {
      int idx = i;
      auto result = *iter;
      auto expected = origin + idx;

      assert(l.contains(result));
      assert(expected == result);
    }
  }

  {
    int2 origin = {13,7};
    int2 shape = {3,2};

    lattice<int2> l(origin, shape);

    auto iter = l.begin();
    for(int i = 0; i != l.shape()[0]; ++i)
    {
      for(int j = 0; j != l.shape()[1]; ++j, ++iter)
      {
        int2 idx = {i,j};
        auto result = *iter;
        auto expected = origin + idx;

        assert(l.contains(result));
        assert(expected == result);
      }
    }
  }

  {
    int3 origin = {13,7,42};
    int3 shape = {3,2,1};

    lattice<int3> l(origin, shape);

    auto iter = l.begin();
    for(int i = 0; i != l.shape()[0]; ++i)
    {
      for(int j = 0; j != l.shape()[1]; ++j)
      {
        for(int k = 0; k != l.shape()[2]; ++k, ++iter)
        {
          int3 idx{i,j,k};
          auto result = *iter;
          auto expected = origin + idx;

          assert(l.contains(result));
          assert(expected == result);
        }
      }
    }
  }
}


