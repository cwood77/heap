#include "cmd-i.hpp"
#include <iostream>

namespace {

void usage()
{
   std::cerr << "demo.exe - exercise the heap" << std::endl;
   std::cerr << "usage: demo <command> <type>" << std::endl;
   std::cerr << std::endl;
   std::cerr << "commands include" << std::endl;
   std::cerr << "   normal       - do some safe memory operations" << std::endl;
   std::cerr << "   underflow    - write off the low end of the buffer" << std::endl;
   std::cerr << "   overflow     - write off the high end of the buffer" << std::endl;
   std::cerr << "   doubledelete - free the buffer twice" << std::endl;
   std::cerr << "   leak         - leak the buffer" << std::endl;
   std::cerr << std::endl;
   std::cerr << "types include" << std::endl;
   std::cerr << "   scalarnew" << std::endl;
   std::cerr << "   arraynew" << std::endl;
   std::cerr << "   malloc" << std::endl;
   std::cerr << "   calloc" << std::endl;
   std::cerr << "   strdup" << std::endl;
}

} // anonymous namespace

int main(int argc, const char *argv[])
{
   if(argc!=3)
   {
      usage();
      return -1;
   }

   using namespace demo;
   using namespace demo::impl;

   try
   {
      std::cout << "starting" << std::endl;
      commandRegistry::get().demand(argv[1]).run(parseType(argv[2]));

      std::cout << "exiting main" << std::endl;
      return 0;
   }
   catch(std::exception& x)
   {
      std::cerr << "caught exception!" << std::endl;
      std::cerr << x.what() << std::endl;
      return -1;
   }
}
