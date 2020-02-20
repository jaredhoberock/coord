#ifndef COORD_INCLUDE_LEVEL

// the first time this header is #included, this branch is processed

// this definition communicates that the stack is empty
// and that these macros should be undefined by epilogue.hpp
#define COORD_INCLUDE_LEVEL 0

// include configuration headers

#include "config/annotation.hpp"
#include "config/concat.hpp"
#include "config/exec_check_disable.hpp"
#include "config/namespace.hpp"
#include "config/requires.hpp"

#else

// any other time this header is #included, this branch is processed

// this push to the stack communicates with epilogue.hpp
// that these macros are not ready to be undefined.
#pragma push_macro("COORD_INCLUDE_LEVEL")
#define COORD_INCLUDE_LEVEL 1

#endif

