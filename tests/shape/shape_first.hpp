#include <cassert>
#include <utility>
#include <tuple>
#include <functional>
#include <coord/shape/shape_first.hpp>

template<class T>
const T& const_ref(const T& arg)
{
  return arg;
}

void test_shape_first()
{
  using namespace coord;

  {
    int shape{13};

    assert(&shape_first(shape) == &shape);
    assert(&shape_first(const_ref(shape)) == &const_ref(shape));
    assert(shape_first(std::move(shape)) == std::move(shape));
  }

  {
    std::tuple<int,int> shape{13,7};

    assert(&shape_first(shape) == &std::get<0>(shape));
    assert(&shape_first(const_ref(shape)) == &std::get<0>(const_ref(shape)));
    assert(shape_first(std::move(shape)) == std::get<0>(std::move(shape)));
  }

  {
    std::tuple<int,int,char> shape{13,7,42};

    assert(&shape_first(shape) == &std::get<0>(shape));
    assert(&shape_first(const_ref(shape)) == &std::get<0>(const_ref(shape)));
    assert(shape_first(std::move(shape)) == std::get<0>(std::move(shape)));
  }

  {
    std::tuple<std::pair<int,int>,unsigned int> shape{{13,7},42};

    assert(&shape_first(shape) == &std::get<0>(shape));
    assert(&shape_first(const_ref(shape)) == &std::get<0>(const_ref(shape)));
    assert(shape_first(std::move(shape)) == std::get<0>(std::move(shape)));
  }

  {
    std::array<std::size_t, 2> shape{{13,7}};

    assert(&shape_first(shape) == &std::get<0>(shape));
    assert(&shape_first(const_ref(shape)) == &std::get<0>(const_ref(shape)));
    assert(shape_first(std::move(shape)) == std::get<0>(std::move(shape)));
  }
}

