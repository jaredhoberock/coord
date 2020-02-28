#if COORD_INCLUDE_LEVEL == 1

// any time this header is #included in a nested fashion, this branch is processed

// pop from the stack
#pragma pop_macro("COORD_INCLUDE_LEVEL")

#else

// the final time this header is processed, this branch is taken

#undef COORD_INCLUDE_LEVEL

// include configuration headers

#include "config/annotation.hpp"
#include "config/concat.hpp"
#include "config/exec_check_disable.hpp"
#include "config/namespace.hpp"
#include "config/requires.hpp"

#endif

