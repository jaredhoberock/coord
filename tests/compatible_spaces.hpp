#include <cassert>
#include <coord/compatible_spaces.hpp>
#include <coord/point.hpp>

void test_compatible_spaces()
{
  using namespace coord;

  {
    // 0D
    int shape1{13};
    unsigned int shape2 = shape1;

    assert(compatible_spaces(shape1, shape1));
    assert(compatible_spaces(shape1, shape2));
    assert(compatible_spaces(shape2, shape2));

    assert(!compatible_spaces(shape1, 7));
    assert(!compatible_spaces(shape2, 7));
  }

  {
    // 1D
    std::tuple<int> shape1{13};
    std::array<int,1> shape2{13};

    assert(compatible_spaces(shape1, shape1));
    assert(compatible_spaces(shape1, shape2));
    assert(compatible_spaces(shape2, shape2));

    assert(!compatible_spaces(shape1, std::make_tuple(7)));
    assert(!compatible_spaces(shape2, std::make_tuple(7)));
  }

  {
    // 2D
    int2 shape1{7,13};
    uint2 shape2{7,13};
    std::pair<int,int> shape3{7,13};

    assert(compatible_spaces(shape1, shape1));
    assert(compatible_spaces(shape1, shape2));
    assert(compatible_spaces(shape1, shape3));
    assert(compatible_spaces(shape2, shape2));
    assert(compatible_spaces(shape2, shape3));

    assert(!compatible_spaces(shape1, std::make_tuple(13,7)));
    assert(!compatible_spaces(shape2, std::make_tuple(13,7)));
    assert(!compatible_spaces(shape3, std::make_tuple(13,7)));
  }

  {
    // 3D
    assert(compatible_spaces(int3(7,13,42), uint3(7,13,42)));
    assert(compatible_spaces(uint2(5*3,7), std::make_pair(int2(5,3),7)));

    assert(!compatible_spaces(std::make_pair(int2(7,13),42), uint2(7*13,42)));
  }

  {
    // 4D
    auto shape1 = 1*2*3*4;
    auto shape2 = std::make_tuple(1*2*3,4);
    auto shape3 = std::make_tuple(std::make_tuple(1*2,3),4);
    auto shape4 = std::make_tuple(std::make_tuple(std::make_tuple(1,2),3),4);

    assert(compatible_spaces(shape1, shape1));
    assert(compatible_spaces(shape1, shape2));
    assert(compatible_spaces(shape1, shape3));
    assert(compatible_spaces(shape1, shape4));

    assert(!compatible_spaces(shape2, shape1));
    assert(compatible_spaces(shape2, shape2));
    assert(compatible_spaces(shape2, shape3));
    assert(compatible_spaces(shape2, shape4));

    assert(!compatible_spaces(shape3, shape1));
    assert(!compatible_spaces(shape3, shape2));
    assert(compatible_spaces(shape3, shape3));
    assert(compatible_spaces(shape3, shape4));

    assert(!compatible_spaces(shape4, shape1));
    assert(!compatible_spaces(shape4, shape2));
    assert(!compatible_spaces(shape4, shape3));
    assert(compatible_spaces(shape4, shape4));
  }
}

