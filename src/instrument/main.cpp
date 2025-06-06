#include "api-i.hpp"
#include <iostream>
#include <stdexcept>

namespace instrument {
namespace impl {

templateRegistry& templateRegistry::get()
{
   static templateRegistry self;
   return self;
}

} // namespace impl
} // namespace instrument

namespace {

void usage()
{
   std::cerr << "instrument.exe - modify source to use the heap" << std::endl;
   std::cerr << "usage: instrument <command> <path>" << std::endl;
   std::cerr << std::endl;
   std::cerr << "commands include" << std::endl;
   std::cerr << "   -1 instrument a single file described in <path>" << std::endl;
   std::cerr << "   -r instrument a whole tree described in <path>" << std::endl;
   std::cerr << std::endl;
   std::cerr << "note that un-instrumenting isn't supported, so save a copy" << std::endl;
   std::cerr << "of the source before running!!" << std::endl;
}

} // anonymous namespace

int main(int argc, const char *argv[])
{
   if(argc!=3)
   {
      usage();
      return -1;
   }

   using namespace instrument;
   using namespace instrument::impl;

   try
   {
      std::cout << "starting" << std::endl;

      saver s;
      instrumentor i(s);

      const std::string opt = argv[1];
      if(opt == "-1")
         i.instrumentFile(argv[2]);
      else if(opt == "-r")
         finder(i).recurse(argv[2]);
      else
         throw std::runtime_error("option not supported");

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
