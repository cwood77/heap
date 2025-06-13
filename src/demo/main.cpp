// wrap/hook memory routines
// (injected by instrument.exe)
#include "../heaplib/hooks.h"
#include "../heaplib/probe.hpp"

#include "cmd-i.hpp"
#include <iostream>
#include <stdexcept>

namespace demo {
namespace impl {

typeRegistry& typeRegistry::get()
{
   static typeRegistry self;
   return self;
}

void typeRegistry::publish(const std::string& name, iType& c)
{
   m_map[name] = &c;
}

iType& typeRegistry::demand(const std::string& name)
{
   auto it = m_map.find(name);
   if(it == m_map.end())
      throw std::runtime_error("type not supported");
   return *it->second;
}

} // namespace impl
} // namespace demo

namespace {

void usage()
{
   std::cerr << "demo.exe - exercise the heap" << std::endl;
   std::cerr << "usage: demo <command> <type>" << std::endl;
   std::cerr << std::endl;
   std::cerr << "commands include" << std::endl;
   std::cerr << "   normal       - do some safe memory operations" << std::endl;
if(false) { // coming soon
   std::cerr << "   underflow    - write off the low end of the buffer" << std::endl;
   std::cerr << "   overflow     - write off the high end of the buffer" << std::endl;
   std::cerr << "   doubledelete - free the buffer twice" << std::endl;
}
   std::cerr << "   leak         - leak the buffer" << std::endl;
   std::cerr << std::endl;
   std::cerr << "types include" << std::endl;
   std::cerr << "   scalarnew" << std::endl;
if(false) { // coming soon
   std::cerr << "   arraynew" << std::endl;
   std::cerr << "   malloc" << std::endl;
   std::cerr << "   calloc" << std::endl;
   std::cerr << "   strdup" << std::endl;
}
}

} // anonymous namespace

// wrap/hook main
// (injected by instrument.exe)
// [gaudi:type-hint]exe
HEAPLIB_MAIN(int argc, const char *argv[])
{
   if(argc!=3)
   {
      usage();
      return -1;
   }

   using namespace demo;

   try
   {
      std::cout << "starting" << std::endl;

      auto& t = impl::typeRegistry::get().demand(argv[2]);
      const std::string command = argv[1];
      if(command == "normal")
         t.normal();
      else if(command == "leak")
         t.leak();
      else
         throw std::runtime_error("command not supported");

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
