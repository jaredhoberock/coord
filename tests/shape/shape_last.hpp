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
    static_assert(std::is_same<shape_last_t<int&>, int&>::value, "Error.h");

    assert(&shape_last(const_ref(shape)) == &const_ref(shape));
    static_assert(std::is_same<shape_last_t<const int&>, const int&>::value, "Error.h");

    assert(shape_last(std::move(shape)) == std::move(shape));
    static_assert(std::is_same<shape_last_t<int&&>, int&&>::value, "Error.h");
  }

  {
    std::tuple<int,int> shape{13,7};

    assert(&shape_last(shape) == &std::get<1>(shape));
    static_assert(std::is_same<shape_last_t<std::tuple<int,int>&>, int&>::value, "Error.h");

    assert(&shape_last(const_ref(shape)) == &std::get<1>(const_ref(shape)));
    static_assert(std::is_same<shape_last_t<const std::tuple<int,int>&>, const int&>::value, "Error.h");

    assert(shape_last(std::move(shape)) == std::get<1>(std::move(shape)));
    static_assert(std::is_same<shape_last_t<std::tuple<int,int>&&>, int&&>::value, "Error.h");
  }

  {
    std::tuple<int,int,char> shape{13,7,42};

    assert(&shape_last(shape) == &std::get<2>(shape));
    static_assert(std::is_same<shape_last_t<std::tuple<int,int,char>&>, char&>::value, "Error.h");

    assert(&shape_last(const_ref(shape)) == &std::get<2>(const_ref(shape)));
    static_assert(std::is_same<shape_last_t<const std::tuple<int,int,char>&>, const char&>::value, "Error.h");

    assert(shape_last(std::move(shape)) == std::get<2>(std::move(shape)));
    static_assert(std::is_same<shape_last_t<std::tuple<int,int,char>&&>, char&&>::value, "Error.h");
  }

  {
    std::tuple<std::pair<int,int>,unsigned int> shape{{13,7},42};

    assert(&shape_last(shape) == &std::get<1>(shape));
    static_assert(std::is_same<shape_last_t<std::tuple<std::pair<int,int>,unsigned int>&>, unsigned int&>::value, "Error.h");

    assert(&shape_last(const_ref(shape)) == &std::get<1>(const_ref(shape)));
    static_assert(std::is_same<shape_last_t<const std::tuple<std::pair<int,int>,unsigned int>&>, const unsigned int&>::value, "Error.h");

    assert(shape_last(std::move(shape)) == std::get<1>(std::move(shape)));
    static_assert(std::is_same<shape_last_t<std::tuple<std::pair<int,int>,unsigned int>&&>, unsigned int&&>::value, "Error.h");
  }

  {
    std::array<std::size_t, 2> shape{{13,7}};

    assert(&shape_last(shape) == &std::get<1>(shape));
    static_assert(std::is_same<shape_last_t<std::array<std::size_t, 1>&>, std::size_t&>::value, "Error.h");

    assert(&shape_last(const_ref(shape)) == &std::get<1>(const_ref(shape)));
    static_assert(std::is_same<shape_last_t<const std::array<std::size_t, 1>&>, const std::size_t&>::value, "Error.h");

    assert(shape_last(std::move(shape)) == std::get<1>(std::move(shape)));
    static_assert(std::is_same<shape_last_t<std::array<std::size_t, 1>&&>, std::size_t&&>::value, "Error.h");
  }
}

