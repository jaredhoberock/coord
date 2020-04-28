#include <cassert>
#include <coord/colexicographic_index.hpp>
#include <coord/point.hpp>
#include <cstdio>
#include <random>

void test_colexicographic_index()
{
  using namespace coord;

  {
    // 1D
    int shape{13};

    std::size_t expected = 0;
    for(int coord = 0; coord < shape; ++coord, ++expected)
    {
      std::size_t result = colexicographic_index(coord, shape);

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
        int2 coord{i,j};
        std::size_t result = colexicographic_index(coord, shape);

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
          int3 coord{i,j,k};
          std::size_t result = colexicographic_index(coord, shape);

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
              std::pair<int2, int3> coord{{i,j}, {x,y,z}};
              std::size_t result = colexicographic_index(coord, shape);

              assert(expected == result);
            }
          }
        }
      }
    }
  }
}

