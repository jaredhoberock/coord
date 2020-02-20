// COORD_EXEC_CHECK_DISABLE expands to a pragma which tells a CUDA-capable
// compiler not to enforce that a function must call another function with
// a compatible execution space

#ifndef COORD_EXEC_CHECK_DISABLE
#  ifdef __CUDACC__
#    define COORD_EXEC_CHECK_DISABLE #pragma nv_exec_check_disable
#  else
#    define COORD_EXEC_CHECK_DISABLE
#  endif
#elif defined(COORD_EXEC_CHECK_DISABLE)
#  undef COORD_EXEC_CHECK_DISABLE
#endif

