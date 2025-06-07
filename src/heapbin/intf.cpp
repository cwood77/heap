#define WIN32_LEAN_AND_MEAN
#include "api.hpp"
#include "heap-i.hpp"
#include <iostream>
#include <windows.h>

namespace heapbin {
namespace {
using namespace impl;

class intf : public iLibIntf {
public:
   virtual iHeap& heap()
   {
      throw 3.14;
   }

   virtual int main_thunk(int argc, const char *argv[], inner_main_f inner) const
   {
      std::cout << "heap{{" << std::endl;

      std::cout << "program-main{{" << std::endl;
      auto rval = inner(argc,argv);
      std::cout << "}}program-main" << std::endl;

      std::cout << "}}heap" << std::endl;
      return rval;
   }
};

} // anonymous namespace
} // namespace heapbin

extern "C" heapbin::iLibIntf *getIntf()
{
   static heapbin::intf gIntf;
   static bool setup = false;
   if(!setup)
   {
      setup = true;
      // configure heap default settings
   }
   return &gIntf;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
   return TRUE;
}
