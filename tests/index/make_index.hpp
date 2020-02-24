#include <cassert>
#include <utility>
#include <tuple>
#include <array>
#include <coord/index/make_index.hpp>

void test_make_index()
{
  using namespace coord;

  {
    auto result = make_index<int>(13);
    assert(13 == result);
  }
  
  {
    auto result = make_index<std::pair<int,int>>(13,7);
    assert(std::make_pair(13,7) == result);
  }

  {
    auto result = make_index<std::array<unsigned int, 3>>(13u,7u,42u);
    assert((std::array<unsigned int, 3>{13,7,42} == result));
  }

  {
    auto result = make_index<std::tuple<int,unsigned int,int,std::size_t>>(13,7,42,1337);
    assert(std::make_tuple(13,7,42,1337) == result);
  }

  {
    std::pair<int,int> p(7,42);
    std::tuple<int,unsigned int> t(13,42);
    std::array<std::size_t,5> a{5,5,5,5,5};
    std::tuple<std::pair<int,int>, std::tuple<int, unsigned int>, std::array<std::size_t,5>> expected = std::make_tuple(p,t,a);
    auto result = make_index<decltype(expected)>(p,t,a);
    assert(expected == result);
  }
}

