#include <coord/point.hpp>
#include <coord/lattice.hpp>

void test_begin_end()
{
  using namespace coord;

  {
    int origin = 13;
    int shape = 7;

    lattice<int> l(origin, shape);

    int linear_idx = 0;
    for(auto i = l.begin(); i != l.end(); ++i, ++linear_idx)
    {
      auto result = *i;
      auto expected = l[linear_idx];
      assert(expected == result);
    }
  }

  {
    int2 origin = {13,7};
    int2 shape = {3,2};

    lattice<int2> l(origin, shape);

    int linear_idx = 0;
    for(auto i = l.begin(); i != l.end(); ++i, ++linear_idx)
    {
      auto result = *i;
      auto expected = l[linear_idx];
      assert(expected == result);
    }
  }

  {
    int3 origin = {13,7,42};
    int3 shape = {3,2,1};

    lattice<int3> l(origin, shape);

    int linear_idx = 0;
    for(auto i = l.begin(); i != l.end(); ++i, ++linear_idx)
    {
      auto result = *i;
      auto expected = l[linear_idx];
      assert(expected == result);
    }
  }
}

