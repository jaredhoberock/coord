// COORD_ANNOTATION expands to __host__ __device__ when encountered by a
// CUDA-capable compiler

#if !defined(COORD_ANNOTATION)

#  ifdef __CUDACC__
#    define COORD_ANNOTATION __host__ __device__
#  else
#    define COORD_ANNOTATION
#  endif
#  define COORD_ANNOTATION_NEEDS_UNDEF

#elif defined(COORD_ANNOTATION_NEEDS_UNDEF)

#undef COORD_ANNOTATION
#undef COORD_ANNOTATION_NEEDS_UNDEF

#endif

