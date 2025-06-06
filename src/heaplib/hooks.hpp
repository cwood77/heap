#pragma once

#define HEAPLIB_MAIN \
   static int _programMain(int argc, const char *argv[]); \
   int main(int argc, const char *argv[]) \
   { \
      return _programMain(argc,argv); \
   } \
   static int _programMain
