#if COORD_INCLUDE_LEVEL == 1

// any time this header is #included in a nested fashion, this branch is processed

// pop from the stack
#pragma pop_macro("COORD_INCLUDE_LEVEL")

#else

// the final time this header is processed, this branch is taken

#undef COORD_INCLUDE_LEVEL

// include configuration headers

#include "config.hpp"

#endif

