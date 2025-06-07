#pragma once
#include "api.h"

#define HEAPLIB_MAIN \
   static int _programMain(int argc, const char *argv[]); \
   int main(int argc, const char *argv[]) \
   { \
      return heaplib_main(argc,argv,&_programMain); \
   } \
   static int _programMain
