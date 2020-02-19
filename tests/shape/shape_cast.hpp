#include <array>
#include <cassert>
#include <cstdio>
#include <random>
#include <tuple>
#include <coord/shape/shape_cast.hpp>

void test_shape_cast()
{
  using namespace coord;

  {
    // 1D -> 1D
    unsigned int from{16};
    int expected{16};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // 1D -> (1D)
    unsigned int from{16};
    std::tuple<int> expected{16};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // (1D) -> 1D
    std::tuple<unsigned int> from{16};
    int expected{16};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // (1D) -> (1D)
    std::tuple<unsigned int> from{16};
    std::tuple<int> expected{16};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // 1D -> 2D
    unsigned int from{16};
    std::array<int,2> expected{{16,1}};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // (1D) -> 2D
    std::array<unsigned int,1> from{{16}};
    std::array<int,2> expected{{16,1}};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // 2D -> 2D
    std::array<unsigned int,2> from{{16,16}};
    std::tuple<int,int> expected{16,16};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // 2D -> 1D
    std::tuple<unsigned int, unsigned int> from{2,8};
    unsigned int expected{16};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }

  {
    // 2D -> (1D)
    std::tuple<unsigned int, unsigned int> from{2,8};
    std::array<unsigned int,1> expected{{16}};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }


  {
    // 2D -> 3D
    std::array<unsigned int, 2> from{4,2};
    std::tuple<int,int,int> expected{4,2,1};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }


  {
    // 3D -> 2D
    std::array<unsigned int, 3> from{2,4,2};
    std::pair<int, unsigned int> expected{2,8};

    assert((expected == shape_cast<decltype(expected)>(from)));
  }


  // XXX KNOWN FAILURE -- see XXX comments inside shape_cast.hpp
  //
  //{
  //  // ((x,y), (x,y,z)) -> (((x,y), (x,y)), x}
  //  std::pair<std::pair<int,int>, std::tuple<int,unsigned int,int>> from{{1,2}, {3,4,5}};
  //  int expected = 1 * 2 * 3 * 4 * 5;

  //  assert((expected == shape_cast<decltype(expected)>(from)));
  //}
}

