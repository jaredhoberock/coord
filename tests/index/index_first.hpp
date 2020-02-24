#include <cassert>
#include <utility>
#include <tuple>
#include <functional>
#include <coord/index/index_first.hpp>

template<class T>
const T& const_ref(const T& arg)
{
  return arg;
}

void test_index_first()
{
  using namespace coord;

  {
    int index{13};

    assert(&index_first(index) == &index);
    assert(&index_first(const_ref(index)) == &const_ref(index));
    assert(index_first(std::move(index)) == std::move(index));
  }

  {
    std::tuple<int,int> index{13,7};

    assert(&index_first(index) == &std::get<0>(index));
    assert(&index_first(const_ref(index)) == &std::get<0>(const_ref(index)));
    assert(index_first(std::move(index)) == std::get<0>(std::move(index)));
  }

  {
    std::tuple<int,int,char> index{13,7,42};

    assert(&index_first(index) == &std::get<0>(index));
    assert(&index_first(const_ref(index)) == &std::get<0>(const_ref(index)));
    assert(index_first(std::move(index)) == std::get<0>(std::move(index)));
  }

  {
    std::tuple<std::pair<int,int>,unsigned int> index{{13,7},42};

    assert(&index_first(index) == &std::get<0>(index));
    assert(&index_first(const_ref(index)) == &std::get<0>(const_ref(index)));
    assert(index_first(std::move(index)) == std::get<0>(std::move(index)));
  }

  {
    std::array<std::size_t, 2> index{{13,7}};

    assert(&index_first(index) == &std::get<0>(index));
    assert(&index_first(const_ref(index)) == &std::get<0>(const_ref(index)));
    assert(index_first(std::move(index)) == std::get<0>(std::move(index)));
  }
}

