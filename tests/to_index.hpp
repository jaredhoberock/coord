#include <cassert>
#include <coord/detail/compact_column_major_stride.hpp>
#include <coord/detail/compact_row_major_stride.hpp>
#include <coord/point.hpp>
#include <coord/to_index.hpp>


void test_to_index()
{
  using namespace coord;

  {
    // 1D, column major
    int shape{13};

    std::size_t expected = 0;
    for(int coord = 0; coord < shape; ++coord, ++expected)
    {
      std::size_t result = to_index(coord, shape, coord::detail::compact_column_major_stride(shape));

      assert(expected == result);
    }
  }

  {
    // 1D, row major
    int shape{13};

    std::size_t expected = 0;
    for(int coord = 0; coord < shape; ++coord, ++expected)
    {
      std::size_t result = to_index(coord, shape, coord::detail::compact_row_major_stride(shape));

      assert(expected == result);
    }
  }

  {
    // 2D, column major
    int2 shape{13,7};

    std::size_t expected = 0;
    for(int j = 0; j < shape[1]; ++j)
    {
      for(int i = 0; i < shape[0]; ++i, ++expected)
      {
        int2 coord{i,j};
        std::size_t result = to_index(coord, shape, coord::detail::compact_column_major_stride(shape));

        assert(expected == result);
      }
    }
  }

  {
    // 2D, row major
    int2 shape{13,7};

    std::size_t expected = 0;
    for(int i = 0; i < shape[0]; ++i)
    {
      for(int j = 0; j < shape[1]; ++j, ++expected)
      {
        int2 coord{i,j};
        std::size_t result = to_index(coord, shape, coord::detail::compact_row_major_stride(shape));

        assert(expected == result);
      }
    }
  }

  {
    // 3D, column major
    int3 shape{13,7,42};

    std::size_t expected = 0;
    for(int k = 0; k < shape[2]; ++k)
    {
      for(int j = 0; j < shape[1]; ++j)
      {
        for(int i = 0; i < shape[0]; ++i, ++expected)
        {
          int3 coord{i,j,k};
          std::size_t result = to_index(coord, shape, coord::detail::compact_column_major_stride(shape));

          assert(expected == result);
        }
      }
    }
  }

  {
    // 3D, row major
    int3 shape{13,7,42};

    std::size_t expected = 0;
    for(int i = 0; i < shape[0]; ++i)
    {
      for(int j = 0; j < shape[1]; ++j)
      {
        for(int k = 0; k < shape[2]; ++k, ++expected)
        {
          int3 coord{i,j,k};
          std::size_t result = to_index(coord, shape, coord::detail::compact_row_major_stride(shape));

          assert(expected == result);
        }
      }
    }
  }

  {
    // 2D x 3D, column major
    // {{i,j}, {x,y,z}}
    std::pair<int2,int3> shape{{13,7}, {42,11,5}};

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
              std::size_t result = to_index(coord, shape, coord::detail::compact_column_major_stride(shape));

              assert(expected == result);
            }
          }
        }
      }
    }
  }

  {
    // 2D x 3D, row major
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
              std::size_t result = to_index(coord, shape, coord::detail::compact_row_major_stride(shape));

              assert(expected == result);
            }
          }
        }
      }
    }
  }
}

