#include <cassert>
#include <utility>
#include <tuple>
#include <array>
#include <coord/shape/make_shape.hpp>

void test_make_shape()
{
  using namespace coord;

  {
    auto result = make_shape<int>(13);
    assert(13 == result);
  }
  
  {
    auto result = make_shape<std::pair<int,int>>(13,7);
    assert(std::make_pair(13,7) == result);
  }

  {
    auto result = make_shape<std::array<unsigned int, 3>>(13u,7u,42u);
    assert((std::array<unsigned int, 3>{13,7,42} == result));
  }

  {
    auto result = make_shape<std::tuple<int,unsigned int,int,std::size_t>>(13,7,42,1337);
    assert(std::make_tuple(13,7,42,1337) == result);
  }

  {
    std::pair<int,int> p(7,42);
    std::tuple<int,unsigned int> t(13,42);
    std::array<std::size_t,5> a{5,5,5,5,5};
    std::tuple<std::pair<int,int>, std::tuple<int, unsigned int>, std::array<std::size_t,5>> expected = std::make_tuple(p,t,a);
    auto result = make_shape<decltype(expected)>(p,t,a);
    assert(expected == result);
  }
}

