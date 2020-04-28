#include <cassert>
#include <coord/colexicographic_index.hpp>
#include <coord/point.hpp>
#include <coord/space_size.hpp>
#include <coord/to_coordinate.hpp>
#include <random>

#include <iostream>

void test_to_coordinate()
{
  using namespace coord;

  {
    // 1D
    std::default_random_engine rng;

    unsigned int from_shape = rng() % 10;
    unsigned int to_shape = from_shape;
    unsigned int to_stride = 1;

    size_t expected_idx = 0; 
    for(unsigned int from_idx = 0; from_idx < from_shape; ++from_idx)
    {
      int to_coord = to_coordinate<int>(from_idx, to_shape, to_stride);

      assert(expected_idx == to_coord);
      ++expected_idx;
    }
  }


  {
    // 2D
    uint2 to_shape{8,2};
    uint2 compact_row_major_stride{2,1};

    unsigned int from_shape = coord::space_size(to_shape);

    for(unsigned int from_idx = 0; from_idx < from_shape; ++from_idx)
    {
      uint2 result = to_coordinate<uint2>(from_idx, to_shape, compact_row_major_stride);
      size_t idx = colexicographic_index(result, to_shape);

      assert(from_idx == idx);
    }
  }


  {
    // 3D
    uint3 to_shape{8,2,16};
    uint3 compact_row_major_stride{32,16,1};

    unsigned int from_shape = coord::space_size(to_shape);

    for(unsigned int from_idx = 0; from_idx < from_shape; ++from_idx)
    {
      uint3 result = to_coordinate<uint3>(from_idx, to_shape, compact_row_major_stride);
      size_t idx = colexicographic_index(result, to_shape);

      assert(from_idx == idx);
    }
  }
}

