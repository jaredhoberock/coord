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
    // 2D X 3D
    std::pair<int2,int3> shape1{{13,7}, {42,11,5}};
    std::tuple<uint2,int3> shape2{{13,7}, {42,11,5}};
    std::pair<int2,std::array<int,3>> shape3{{13,7}, {42,11,5}};

    assert(compatible_spaces(shape1, shape1));
    assert(compatible_spaces(shape1, shape2));
    assert(compatible_spaces(shape1, shape3));
    assert(compatible_spaces(shape2, shape2));
    assert(compatible_spaces(shape2, shape3));

    assert(!compatible_spaces(shape1, std::make_tuple(int2(1,2), int3(1,2,3))));
    assert(!compatible_spaces(shape2, std::make_tuple(int2(1,2), int3(1,2,3))));
    assert(!compatible_spaces(shape3, std::make_tuple(int2(1,2), int3(1,2,3))));
  }
}

