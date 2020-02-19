#include <cassert>
#include <utility>
#include <tuple>
#include <functional>
#include <coord/shape/shape_last.hpp>

template<class T>
const T& const_ref(const T& arg)
{
  return arg;
}

void test_shape_last()
{
  using namespace coord;

  {
    int shape{13};

    assert(&shape_last(shape) == &shape);
    assert(&shape_last(const_ref(shape)) == &const_ref(shape));
    assert(shape_last(std::move(shape)) == std::move(shape));
  }

  {
    std::tuple<int,int> shape{13,7};

    assert(&shape_last(shape) == &std::get<1>(shape));
    assert(&shape_last(const_ref(shape)) == &std::get<1>(const_ref(shape)));
    assert(shape_last(std::move(shape)) == std::get<1>(std::move(shape)));
  }

  {
    std::tuple<int,int,char> shape{13,7,42};

    assert(&shape_last(shape) == &std::get<2>(shape));
    assert(&shape_last(const_ref(shape)) == &std::get<2>(const_ref(shape)));
    assert(shape_last(std::move(shape)) == std::get<2>(std::move(shape)));
  }

  {
    std::tuple<std::pair<int,int>,unsigned int> shape{{13,7},42};

    assert(&shape_last(shape) == &std::get<1>(shape));
    assert(&shape_last(const_ref(shape)) == &std::get<1>(const_ref(shape)));
    assert(shape_last(std::move(shape)) == std::get<1>(std::move(shape)));
  }

  {
    std::array<std::size_t, 2> shape{{13,7}};

    assert(&shape_last(shape) == &std::get<1>(shape));
    assert(&shape_last(const_ref(shape)) == &std::get<1>(const_ref(shape)));
    assert(shape_last(std::move(shape)) == std::get<1>(std::move(shape)));
  }
}

