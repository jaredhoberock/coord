#include <cassert>
#include <coord/index/colexicographic_rank.hpp>
#include <coord/point.hpp>
#include <cstdio>
#include <random>

void test_colexicographic_rank()
{
  using namespace coord;

  {
    // 1D
    int shape{13};

    std::size_t expected = 0;
    for(int idx = 0; idx < shape; ++idx, ++expected)
    {
      std::size_t result = colexicographic_rank(idx, shape);

      assert(expected == result);
    }
  }

  {
    // 2D
    int2 shape{13,7};

    std::size_t expected = 0;
    for(int i = 0; i < shape[0]; ++i)
    {
      for(int j = 0; j < shape[1]; ++j, ++expected)
      {
        int2 idx{i,j};
        std::size_t result = colexicographic_rank(idx, shape);

        if(expected != result)
        {
          std::cout << "idx: " << idx << std::endl;
          std::cout << "expected: " << expected << std::endl;
          std::cout << "result: " << result << std::endl;
        }

        assert(expected == result);
      }
    }
  }

  {
    // 3D
    int3 shape{13,7,42};

    std::size_t expected = 0;
    for(int i = 0; i < shape[0]; ++i)
    {
      for(int j = 0; j < shape[1]; ++j)
      {
        for(int k = 0; k < shape[2]; ++k, ++expected)
        {
          int3 idx{i,j,k};
          std::size_t result = colexicographic_rank(idx, shape);

          assert(expected == result);
        }
      }
    }
  }

  {
    // 2D x 3D
    // {{i,j}, {x,y,z}}
    std::pair<int2,int3> shape{{13,7}, {42,11,5}};

    std::size_t expected = 0;
    for(int i = 0; i < shape.first[0]; ++i)
    {
      for(int j = 0; j < shape.first[1]; ++j)
      {
        for(int x = 0; x < shape.second[0]; ++x)
        {
          for(int y = 0; y < shape.second[1]; ++y)
          {
            for(int z = 0; z < shape.second[2]; ++z, ++expected)
            {
              std::pair<int2, int3> idx{{i,j}, {x,y,z}};
              std::size_t result = colexicographic_rank(idx, shape);

              assert(expected == result);
            }
          }
        }
      }
    }
  }
}

