#include <cassert>
#include <coord/in_space.hpp>
#include <coord/point.hpp>

void test_in_space()
{
  using namespace coord;

  {
    // 1D
    int shape{13};

    std::size_t expected = 0;
    for(int coord = 0; coord < shape; ++coord, ++expected)
    {
      assert(in_space(coord, shape));
    }

    assert(!in_space(-1, shape));
    assert(!in_space(shape, shape));
    assert(!in_space(shape+1, shape));
  }

  {
    // 2D
    int2 shape{13,7};

    std::size_t expected = 0;
    for(int j = 0; j < shape[1]; ++j)
    {
      for(int i = 0; i < shape[0]; ++i, ++expected)
      {
        int2 coord{i,j};

        assert(in_space(coord, shape));
      }
    }

    assert(!in_space(int2(-1,0), shape));
    assert(!in_space(int2(0,-1), shape));
    assert(!in_space(shape, shape));
    assert(!in_space(shape + int2(1,0), shape));
    assert(!in_space(shape + int2(0,1), shape));
  }

  {
    // 3D
    int3 shape{13,7,42};

    std::size_t expected = 0;
    for(int k = 0; k < shape[2]; ++k)
    {
      for(int j = 0; j < shape[1]; ++j)
      {
        for(int i = 0; i < shape[0]; ++i, ++expected)
        {
          int3 coord{i,j,k};

          assert(in_space(coord, shape));
        }
      }
    }

    assert(!in_space(int3(-1,0,0), shape));
    assert(!in_space(int3(0,-1,0), shape));
    assert(!in_space(int3(0,0,-1), shape));
    assert(!in_space(shape, shape));
    assert(!in_space(shape + int3(1,0,0), shape));
    assert(!in_space(shape + int3(0,1,0), shape));
    assert(!in_space(shape + int3(0,0,1), shape));
  }


  {
    // 2D x 3D
    // {{i,j}, {x,y,z}}
    using type = std::pair<int2,int3>;
    type shape{{13,7}, {42,11,5}};

    std::size_t expected = 0;
    for(int z = 0; z < shape.second[2]; ++z)
    {
      for(int y = 0; y < shape.second[1]; ++y)
      {
        for(int x = 0; x < shape.second[0]; ++x)
        {
          for(int j = 0; j < shape.first[1]; ++j)
          {
            for(int i = 0; i < shape.first[0]; ++i, ++expected)
            {
              std::pair<int2, int3> coord{{i,j}, {x,y,z}};

              assert(in_space(coord, shape));
            }
          }
        }
      }
    }

    assert(!in_space(type{{-1,0},{0,0,0}}, shape));
    assert(!in_space(type{{0,-1},{0,0,0}}, shape));
    assert(!in_space(type{{0,0},{-1,0,0}}, shape));
    assert(!in_space(type{{0,0},{0,-1,0}}, shape));
    assert(!in_space(type{{0,0},{0,0,-1}}, shape));
    assert(!in_space(shape, shape));
  }
}

