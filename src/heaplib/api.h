#pragma once
#include <stddef.h>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*heaplib_inner_main_f)(int,const char*[]);
extern int heaplib_main(int argc, const char *argv[], heaplib_inner_main_f f);

#ifdef __cplusplus
}
#endif

inline void *operator new(size_t x)
{
   std::cerr << "in new" << std::endl;
   return ::malloc(x);
}

inline void operator delete(void *p)
{
   std::cerr << "in del" << std::endl;
   ::free(p);
}

#define HEAPLIB_MAIN \
   static int _programMain(int argc, const char *argv[]); \
   int main(int argc, const char *argv[]) \
   { \
      return heaplib_main(argc,argv,&_programMain); \
   } \
   static int _programMain
