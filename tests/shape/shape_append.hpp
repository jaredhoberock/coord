#include <utility>
#include <tuple>
#include <coord/shape/shape_append.hpp>

void test_shape_append()
{
  using namespace coord;

  {
    using input = int;
    using to_append = int;
    using expected = std::pair<int,int>;
    using result = shape_append_t<input, to_append, std::pair>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = int;
    using to_append = int;
    using expected = std::tuple<int,int>;
    using result = shape_append_t<input, to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::tuple<char>;
    using to_append = char;
    using expected = std::pair<char,char>;
    using result = shape_append_t<input, to_append, std::pair>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::tuple<char>;
    using to_append = char;
    using expected = std::tuple<char,char>;
    using result = shape_append_t<input, to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::pair<int,int>;
    using to_append = char;
    using expected = std::tuple<int,int,char>;
    using result = shape_append_t<input,to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::pair<int,int>;
    using to_append = unsigned int;
    using expected = std::tuple<int,int,unsigned int>;
    using result = shape_append_t<input,to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::tuple<std::pair<int,int>>;
    using to_append = unsigned int;
    using expected = std::tuple<std::pair<int,int>,unsigned int>;
    using result = shape_append_t<input,to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::tuple<std::pair<int,int>>;
    using to_append = unsigned int;
    using expected = std::pair<std::pair<int,int>,unsigned int>;
    using result = shape_append_t<input,to_append, std::pair>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::array<std::size_t, 1>;
    using to_append = std::size_t;
    using expected = std::array<std::size_t, 2>;
    using result = shape_append_t<input,to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::array<std::size_t, 1>;
    using to_append = std::size_t;
    using expected = std::pair<std::size_t, std::size_t>;
    using result = shape_append_t<input,to_append, std::pair>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::array<std::size_t, 1>;
    using to_append = std::size_t;
    using expected = std::tuple<std::size_t, std::size_t>;
    using result = shape_append_t<input,to_append, std::tuple>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::array<std::size_t, 1>;
    using to_append = std::size_t;
    using expected = std::array<std::size_t, 2>;
    using result = shape_append_t<input,to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::array<std::size_t, 2>;
    using to_append = std::size_t;
    using expected = std::tuple<std::size_t, std::size_t, std::size_t>;
    using result = shape_append_t<input,to_append,std::tuple>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }

  {
    using input = std::array<std::size_t, 2>;
    using to_append = std::size_t;
    using expected = std::array<std::size_t, 3>;
    using result = shape_append_t<input,to_append>;
    static_assert(std::is_same<expected, result>::value, "Error.");
  }
}

