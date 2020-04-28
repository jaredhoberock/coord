#include <utility>
#include <tuple>
#include <array>
#include <coord/congruent.hpp>

void test_are_congruent()
{
  // test some congruent coordinates
  static_assert(coord::are_congruent_v<int,int>, "Error.h");
  static_assert(coord::are_congruent_v<int,unsigned int>, "Error.h");
  static_assert(coord::are_congruent_v<unsigned int,int>, "Error.h");
  static_assert(coord::are_congruent_v<float,int>, "Error.h");
  static_assert(coord::are_congruent_v<float,float>, "Error.h");
  static_assert(coord::are_congruent_v<double,double>, "Error.h");
  static_assert(coord::are_congruent_v<double,float>, "Error.h");
  static_assert(coord::are_congruent_v<float,double>, "Error.h");
  
  static_assert(coord::are_congruent_v<std::tuple<int>, std::tuple<int>>, "Error.");
  static_assert(coord::are_congruent_v<std::tuple<int,std::size_t>, std::pair<char, int>>, "Error.");
  static_assert(coord::are_congruent_v<std::array<std::size_t,3>, std::tuple<int,int,int>>, "Error.");

  using uint3 = std::tuple<unsigned int, unsigned int, unsigned int>;
  using uint2x3 = std::pair<uint3,uint3>;
  using int2x3 = std::tuple<std::array<int,3>,std::array<int,3>>;
  static_assert(coord::are_congruent_v<uint2x3, int2x3>, "Error.");


  // test some types that are not congruent
  using float2 = std::pair<float,float>;
  using double3 = std::tuple<double, double, double>;

  static_assert(!coord::are_congruent_v<int*,int>, "Error.");
  static_assert(!coord::are_congruent_v<int*,int*>, "Error.");
  static_assert(!coord::are_congruent_v<int,uint2x3>, "Error.");
  static_assert(!coord::are_congruent_v<float2,double3>, "Error.");
  static_assert(!coord::are_congruent_v<uint3, uint2x3>, "Error.");
  static_assert(!coord::are_congruent_v<std::array<int,1>, int>, "Error.");
}

