#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include <coord/shape/common_shape.hpp>
#include <coord/shape/shape_cast.hpp>

void test_common_shape()
{
  using namespace coord;

  {
    // two identical shapes' common shape is what we started with
    using shape1 = std::size_t;
    using shape2 = std::size_t;

    using common_shape = common_shape_t<shape1,shape2>;
    using reference = std::size_t;

    static_assert(std::is_same<reference, common_shape>::value, "Error.");
  }

  {
    // the common shape of size_t & array<size_t, 1> should be size_t

    using shape1 = std::size_t;
    using shape2 = std::array<size_t,1>;

    {
      using common_shape = common_shape_t<shape1,shape2>;

      static_assert(std::is_same<common_shape, std::size_t>::value, "common_shape should be size_t");
    }

    {
      // and vice versa
      using common_shape = common_shape_t<shape2,shape1>;

      static_assert(std::is_same<common_shape, std::size_t>::value, "common_shape should be size_t");
    }

    {
      // test that we can cast back and forth from an original shape to the common shape without losing information
      shape1 s1 = 13;
      shape2 s2 = {{7}};

      using common_shape = common_shape_t<shape1,shape2>;

      common_shape cs1 = shape_cast<common_shape>(s1);
      common_shape cs2 = shape_cast<common_shape>(s2);

      assert(s1 == shape_cast<shape1>(cs1));
      assert(s2 == shape_cast<shape2>(cs2));
    }
  }

  {
    // the common shape of size_t & array<size_t, 2> should have two size_t elements
    
    using shape1 = std::size_t;
    using shape2 = std::array<size_t, 2>;

    {
      using common_shape = common_shape_t<shape1,shape2>;

      static_assert(shape_size<common_shape>::value == 2, "common_shape should have two elements.");
      static_assert(std::is_same<shape_element_t<0,common_shape>, std::size_t>::value, "common_shape's first element should be size_t");
      static_assert(std::is_same<shape_element_t<1,common_shape>, std::size_t>::value, "common_shape's second element should be size_t");
    }

    {
      // and vice versa
      
      using common_shape = common_shape_t<shape2,shape1>;

      static_assert(shape_size<common_shape>::value == 2, "common_shape should have two elements.");
      static_assert(std::is_same<shape_element_t<0,common_shape>, std::size_t>::value, "common_shape's first element should be size_t");
      static_assert(std::is_same<shape_element_t<1,common_shape>, std::size_t>::value, "common_shape's second element should be size_t");
    }

    {
      // test that we can cast back and forth from an original shape to the common shape without losing information
      shape1 s1 = 13;
      shape2 s2 = {{13,7}};

      using common_shape = common_shape_t<shape1,shape2>;

      common_shape cs1 = shape_cast<common_shape>(s1);
      common_shape cs2 = shape_cast<common_shape>(s2);

      assert(s1 == shape_cast<shape1>(cs1));
      assert(s2 == shape_cast<shape2>(cs2));
    }
  }

  {
    using size2 = std::tuple<std::size_t, std::size_t>;
    using uint3 = std::array<unsigned int, 3>;

    // the common shape of size2 & uint3 should be {size, size, uint}
    using shape1 = size2;
    using shape2 = uint3;

    using common_shape = common_shape_t<shape1,shape2>;

    static_assert(shape_size<common_shape>::value == 3, "common_shape should have three elements.");
    static_assert(std::is_same<shape_element_t<0,common_shape>, std::size_t>::value, "common_shape's first element should be size_t");
    static_assert(std::is_same<shape_element_t<1,common_shape>, std::size_t>::value, "common_shape's first element should be size_t");
    static_assert(std::is_same<shape_element_t<2,common_shape>, unsigned int>::value, "common_shape's first element should be unsigned int");

    // test that we can cast back and forth from an original shape to the common shape without losing information
    shape1 s1 = {13, 7};
    shape2 s2 = {13, 7, 42};

    common_shape cs1 = shape_cast<common_shape>(s1);
    common_shape cs2 = shape_cast<common_shape>(s2);

    assert(s1 == shape_cast<shape1>(cs1));
    assert(s2 == shape_cast<shape2>(cs2));
  }

  {
    using size2 = std::pair<std::size_t, std::size_t>;
    using size3 = std::array<std::size_t, 3>;

    // try something complicated
    
    using shape1 = std::tuple<
      size2,                       // 0

      std::tuple<                  // 1
        size3,                     // 1.0
        int                        // 1.1
      >,

      std::tuple<                  // 2
        unsigned int               // 2.0
      >
    >;

    using shape2 = std::tuple<
      std::tuple<                  // 0
        int,                       // 0.0
        int,                       // 0.1
        size3                      // 0.2
      >,

      std::pair<                   // 1
        std::pair<                 // 1.0
          int,                     // 1.0.0
          unsigned int             // 1.0.1
        >,
        std::array<std::size_t, 4> // 1.1
      >
    >;

    using common_shape = common_shape_t<shape1,shape2>;

    using reference = std::tuple<
      std::tuple<                  // 0
        std::size_t,               // 0.0
        std::size_t,               // 0.1
        size3                      // 0.2
      >,

      std::tuple<                  // 1
        std::tuple<                // 1.0
          std::size_t,             // 1.0.0
          std::size_t,             // 1.0.1
          std::size_t              // 1.0.2
        >,
        std::tuple<                // 1.1
          std::size_t,             // 1.1.0
          std::size_t,             // 1.1.1
          std::size_t,             // 1.1.2
          std::size_t              // 1.1.2
        >
      >,

      std::tuple<                  // 2
        unsigned int               // 2.0
      >
    >;

    static_assert(std::is_same<reference, common_shape>::value, "common_shape does not match reference.");
  }

  std::cout << "OK" << std::endl;
}

