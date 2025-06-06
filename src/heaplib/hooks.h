#pragma once
#include "api.h"

#ifdef __cplusplus
#include <exception>
#endif

#ifdef __cplusplus
inline void *operator new(std::size_t z)
{
   return heaplib_new(z);
}
inline void operator delete(void *p)
{
   heaplib_delete(p);
}
#endif

#define HEAPLIB_MAIN \
   static int _programMain(int argc, const char *argv[]); \
   int main(int argc, const char *argv[]) \
   { \
      return heaplib_main(argc,argv,&_programMain); \
   } \
   static int _programMain
