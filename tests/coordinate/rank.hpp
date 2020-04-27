#include <utility>
#include <tuple>
#include <coord/coordinate/rank.hpp>

struct has_rank_member_function
{
  constexpr std::size_t rank()
  {
    return 1;
  }
};

struct has_rank_free_function {};

constexpr std::size_t rank(const has_rank_free_function&)
{
  return 1;
}


void test_rank()
{
  static_assert(1 == coord::rank_v<has_rank_member_function>, "Error.");
  static_assert(1 == coord::rank_v<has_rank_free_function>, "Error.");

  static_assert(0 == coord::rank_v<int>, "Error.");
  static_assert(0 == coord::rank_v<unsigned int>, "Error.");
  static_assert(0 == coord::rank_v<std::size_t>, "Error.");
  static_assert(1 == coord::rank_v<std::tuple<char>>, "Error.");

  static_assert(0 == coord::rank_v<float>, "Error.");
  static_assert(0 == coord::rank_v<double>, "Error.");
  static_assert(1 == coord::rank_v<std::tuple<float>>, "Error.");
  static_assert(1 == coord::rank_v<std::tuple<double>>, "Error.");

  static_assert(2 == coord::rank_v<std::pair<int,int>>, "Error.");
  static_assert(2 == coord::rank_v<std::tuple<int,unsigned int>>, "Error.");
  static_assert(3 == coord::rank_v<std::tuple<int,unsigned int,std::size_t>>, "Error.");

  using int2 = std::pair<int,int>;
  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;

  static_assert(2 == coord::rank_v<std::pair<int2,uint3>>, "Error.");
  static_assert(3 == coord::rank_v<std::tuple<int2,uint3,std::size_t>>, "Error.");

  using uint2x3 = std::pair<uint3,uint3>;
  static_assert(2 == coord::rank_v<uint2x3>, "Error.");
}

