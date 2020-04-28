// note that this header file is special and does not use #pragma once

// The COORD_REQUIRES() macro may be used in a function template's parameter list
// to simulate Concepts.
//
// For example, to selectively enable a function template only for integer types,
// we could do something like this:
//
//     template<class Integer,
//              COORD_REQUIRES(std::is_integral<Integer>::value)
//             >
//     Integer plus_one(Integer x)
//     {
//       return x + 1;
//     }
//

#ifndef COORD_REQUIRES

#  define COORD_CONCATENATE_IMPL(x, y) x##y

#  define COORD_CONCATENATE(x, y) COORD_CONCATENATE_IMPL(x, y)

#  define COORD_MAKE_UNIQUE(x) COORD_CONCATENATE(x, __COUNTER__)

#  define COORD_REQUIRES_IMPL(unique_name, ...) bool unique_name = true, typename std::enable_if<(unique_name and __VA_ARGS__)>::type* = nullptr

#  define COORD_REQUIRES(...) COORD_REQUIRES_IMPL(COORD_MAKE_UNIQUE(__deduced_true), __VA_ARGS__)

#  define COORD_REQUIRES_DEF_IMPL(unique_name, ...) bool unique_name, typename std::enable_if<(unique_name and __VA_ARGS__)>::type*

#  define COORD_REQUIRES_DEF(...) COORD_REQUIRES_DEF_IMPL(COORD_MAKE_UNIQUE(__deduced_true), __VA_ARGS__)

#elif defined(COORD_REQUIRES)

#  ifdef COORD_CONCATENATE_IMPL
#    undef COORD_CONCATENATE_IMPL
#  endif

#  ifdef COORD_CONCATENATE
#    undef COORD_CONCATENATE
#  endif

#  ifdef COORD_MAKE_UNIQUE
#    undef COORD_MAKE_UNIQUE
#  endif

#  ifdef COORD_REQUIRES_IMPL
#    undef COORD_REQUIRES_IMPL
#  endif

#  ifdef COORD_REQUIRES
#    undef COORD_REQUIRES
#  endif

#  ifdef COORD_REQUIRES_DEF_IMPL
#    undef COORD_REQUIRES_DEF_IMPL
#  endif

#  ifdef COORD_REQUIRES_DEF
#    undef COORD_REQUIRES_DEF
#  endif

#endif

