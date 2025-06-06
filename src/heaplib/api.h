#pragma once
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void *heaplib_new(size_t z);
extern void heaplib_delete(void *ptr);

typedef int (*heaplib_inner_main_f)(int,const char*[]);
extern int heaplib_main(int argc, const char *argv[], heaplib_inner_main_f f);

#ifdef __cplusplus
}
#endif
