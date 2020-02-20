// COORD_CONCAT is a macro concatenator

#if !defined(COORD_CONCAT)

#  define COORD_CONCAT_IMPL(x, y) x##y
#  define COORD_CONCAT(x, y) COORD_CONCAT_IMPL(x, y)
#  define COORD_CONCAT_NEEDS_UNDEF

#elif defined(COORD_CONCAT_NEEDS_UNDEF)

#undef COORD_CONCAT_IMPL
#undef COORD_CONCAT
#undef COORD_CONCAT_NEEDS_UNDEF

#endif

