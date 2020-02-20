This directory contains unit tests exercising functionality defined beneath the `<coord/shape.hpp>` header.

For example, To build and execute a single test program named `is_shape`:

    $ make test.is_shape

To build and execute all test programs:

    $ make test

# Details

Each `<name>.hpp` file in this directory is a C++ file containing a function named `test_<name>`.

A unit test program should define a `main` function which calls the function `test_<name>`. If `test_<name>` exits normally, the test program should print "OK" to stdout, and exit normally.

For example, a unit test named `bulk_execute.cpp` should look like:

    #include <iostream>
    #include "bulk_execute.hpp"

    int main()
    {
      test_bulk_execute();
      std::cout << "OK" << std::endl;
      return 0;
    }

The `Makefile` automates this. To create a new unit test for `foo`, create a header file named `foo.hpp` and define a function named `test_foo`. The `Makefile` will take care of the rest.

