#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*heaplib_inner_main_f)(int,const char*[]);
extern int heaplib_main(int argc, const char *argv[], heaplib_inner_main_f f);

#ifdef __cplusplus
}
#endif
