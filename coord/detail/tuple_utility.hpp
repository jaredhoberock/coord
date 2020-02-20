#pragma once

#include "prologue.hpp"

// define various macros for tuple_utility_impl.hpp before #include
#define TUPLE_UTILITY_ANNOTATION COORD_ANNOTATION
#define TUPLE_UTILITY_NAMESPACE COORD_NAMESPACE::detail::tu
#define TUPLE_UTILITY_NAMESPACE_OPEN_BRACE COORD_NAMESPACE_OPEN_BRACE namespace detail { namespace tu {
#define TUPLE_UTILITY_NAMESPACE_CLOSE_BRACE } } COORD_NAMESPACE_CLOSE_BRACE

#include "tuple_utility_impl.hpp"

// undefine the macros for tuple_utility_impl.hpp before #include
#undef TUPLE_UTILITY_ANNOTATION
#undef TUPLE_UTILITY_NAMESPACE
#undef TUPLE_UTILITY_NAMESPACE_OPEN_BRACE
#undef TUPLE_UTILITY_NAMESPACE_CLOSE_BRACE

#include "epilogue.hpp"

