#pragma once
#include "api.h"

#ifdef __cplusplus
#include <new>
#include <exception>
#endif

#ifdef __cplusplus
void *operator new(std::size_t z);
void operator delete(void* p) _GLIBCXX_USE_NOEXCEPT;
#endif

#define HEAPLIB_MAIN \
   static int _programMain(int argc, const char *argv[]); \
   int main(int argc, const char *argv[]) \
   { \
      return heaplib_main(argc,argv,&_programMain); \
   } \
   static int _programMain
