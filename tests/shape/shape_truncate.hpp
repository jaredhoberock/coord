#include <cassert>
#include <utility>
#include <tuple>
#include <coord/shape/shape_truncate.hpp>


template<class T1, class>
using size_two_array = std::array<T1, 2>;


void test_shape_truncate()
{
  using namespace coord;

  {
    using input_t = std::pair<int,int>;
    using expected_t = int;
    using result_t = shape_truncate_t<input_t>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::tuple<int,int> input{13,7};
    int expected = 13;
    auto result = shape_truncate(input);
    assert(expected == result);
  }

  {
    using input_t = std::pair<char,char>;
    using expected_t = std::tuple<char>;
    using result_t = shape_truncate_t<input_t, std::tuple>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::tuple<char,char> input{13,7};
    char expected{13};
    auto result = shape_truncate(input);
    assert(expected == result);
  }

  {
    std::tuple<int,int,char> input{13,7,42};
    std::tuple<int,int> expected{13,7};
    auto result = shape_truncate(input);
    assert(expected == result);
  }

  {
    std::tuple<int,int,unsigned int> input{13,7,42};
    std::tuple<int,int> expected{13,7};
    auto result = shape_truncate(input);
    assert(expected == result);
  }

  {
    std::tuple<std::pair<int,int>,unsigned int> input{{13,7},42};
    std::pair<int,int> expected{13,7};
    auto result = shape_truncate(input);
    assert(expected == result);
  }

  {
    using input_t = std::pair<std::pair<int,int>,unsigned int>;
    using expected_t = std::pair<int,int>;
    using result_t = shape_truncate_t<input_t>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::array<std::size_t, 2> input{{13,7}};
    std::size_t expected{13};
    auto result = shape_truncate(input);
    assert(expected == result);
  }

  {
    using input_t = std::array<std::size_t, 3>;
    using expected_t = std::pair<std::size_t, std::size_t>;
    using result_t = shape_truncate_t<input_t, std::pair>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    using input_t = std::pair<std::size_t, std::size_t>;
    using expected_t = std::tuple<std::size_t>;
    using result_t = shape_truncate_t<input_t, std::tuple>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    using input_t = std::tuple<std::size_t, std::size_t, std::size_t>;
    using expected_t = std::array<std::size_t, 2>;
    using result_t = shape_truncate_t<input_t, size_two_array>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::array<std::size_t, 3> input{{13,7,42}};
    std::array<std::size_t, 2> expected{{13,7}};
    auto result = shape_truncate(input);
    assert(expected == result);
  }
}

