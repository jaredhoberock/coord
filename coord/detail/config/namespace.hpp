// note that this header file is special and does not use #pragma once

#if !defined(COORD_NAMESPACE)

// this branch is taken the first time this header is included

#  if defined(COORD_NAMESPACE_OPEN_BRACE) or defined(COORD_NAMESPACE_CLOSE_BRACE)
#    error "Either all of COORD_NAMESPACE, COORD_NAMESPACE_OPEN_BRACE, and COORD_NAMESPACE_CLOSE_BRACE must be defined, or none of them."
#  endif

#  define COORD_NAMESPACE coord
#  define COORD_NAMESPACE_OPEN_BRACE namespace coord {
#  define COORD_NAMESPACE_CLOSE_BRACE }
#  define COORD_NAMESPACE_NEEDS_UNDEF

#elif defined(COORD_NAMESPACE_NEEDS_UNDEF)

// this branch is taken the second time this header is included

#  undef COORD_NAMESPACE
#  undef COORD_NAMESPACE_OPEN_BRACE
#  undef COORD_NAMESPACE_CLOSE_BRACE
#  undef COORD_NAMESPACE_NEEDS_UNDEF

#elif defined(COORD_NAMESPACE) or defined(COORD_NAMESPACE_OPEN_BRACE) or defined(COORD_CLOSE_BRACE)

// this branch is taken the first time this header is included, and the user has misconfigured these namespace-related symbols

#  if !defined(COORD_NAMESPACE) or !defined(COORD_NAMESPACE_OPEN_BRACE) or !defined(COORD_NAMESPACE_CLOSE_BRACE)
#    error "Either all of COORD_NAMESPACE, COORD_NAMESPACE_OPEN_BRACE, and COORD_NAMESPACE_CLOSE_BRACE must be defined, or none of them."
#  endif

#endif

