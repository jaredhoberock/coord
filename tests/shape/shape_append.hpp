#include <cassert>
#include <utility>
#include <tuple>
#include <coord/shape/shape_append.hpp>

void test_shape_append()
{
  using namespace coord;

  {
    using input_t = int;
    using to_append_t = int;
    using expected_t = std::pair<int,int>;
    using result_t = shape_append_t<input_t, to_append_t, std::pair>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    int input = 13;
    int to_append = 7;
    std::tuple<int,int> expected{13,7};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }

  {
    using input_t = std::tuple<char>;
    using to_append_t = char;
    using expected_t = std::pair<char,char>;
    using result_t = shape_append_t<input_t, to_append_t, std::pair>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::tuple<char> input{13};
    char to_append = 7;
    std::tuple<char,char> expected{13,7};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }

  {
    std::pair<int,int> input{13,7};
    char to_append = 42;
    std::tuple<int,int,char> expected{13,7,42};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }

  {
    std::pair<int,int> input{13,7};
    unsigned int to_append = 42;
    std::tuple<int,int,unsigned int> expected{13,7,42};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }

  {
    std::tuple<std::pair<int,int>> input{{13,7}};
    unsigned int to_append = 42;
    std::tuple<std::pair<int,int>,unsigned int> expected{{13,7},42};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }

  {
    using input_t = std::tuple<std::pair<int,int>>;
    using to_append_t = unsigned int;
    using expected_t = std::pair<std::pair<int,int>,unsigned int>;
    using result_t = shape_append_t<input_t, to_append_t, std::pair>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::array<std::size_t, 1> input{{13}};
    std::size_t to_append = 7;
    std::array<std::size_t, 2> expected{{13,7}};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }

  {
    using input_t = std::array<std::size_t, 1>;
    using to_append_t = std::size_t;
    using expected_t = std::pair<std::size_t, std::size_t>;
    using result_t = shape_append_t<input_t, to_append_t, std::pair>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    using input_t = std::array<std::size_t, 1>;
    using to_append_t = std::size_t;
    using expected_t = std::tuple<std::size_t, std::size_t>;
    using result_t = shape_append_t<input_t, to_append_t, std::tuple>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::array<std::size_t, 1> input{13};
    std::size_t to_append = 7;
    std::array<std::size_t, 2> expected{{13,7}};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }

  {
    using input_t = std::array<std::size_t, 2>;
    using to_append_t = std::size_t;
    using expected_t = std::tuple<std::size_t, std::size_t, std::size_t>;
    using result_t = shape_append_t<input_t,to_append_t,std::tuple>;
    static_assert(std::is_same<expected_t, result_t>::value, "Error.");
  }

  {
    std::array<std::size_t, 2> input{{13,7}};
    std::size_t to_append = 42;
    std::array<std::size_t, 3> expected{{13,7,42}};
    auto result = shape_append(input, to_append);
    assert(expected == result);
  }
}

