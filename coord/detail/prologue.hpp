// note that this header file is special and does not use #pragma once

#ifndef COORD_INCLUDE_LEVEL

// the first time this header is #included, this branch is processed

// this definition communicates that the stack is empty
// and that these macros should be undefined by epilogue.hpp
#define COORD_INCLUDE_LEVEL 0

// include configuration headers
#include "config.hpp"

#else

// any other time this header is #included, this branch is processed

// this push to the stack communicates with epilogue.hpp
// that these macros are not ready to be undefined.
#pragma push_macro("COORD_INCLUDE_LEVEL")
#define COORD_INCLUDE_LEVEL 1

#endif

