#define WIN32_LEAN_AND_MEAN
#include "api.hpp"
#include "heap-i.hpp"
#include "probes-i.hpp"
#include <iostream>
#include <windows.h>

namespace heapbin {
namespace {
using namespace impl;

class intf : public iLibIntf {
public:
   virtual iTracker& allTrackers()
   {
      return impl::getProbes();
   }

   virtual iHeap& heap()
   {
      throw 3.14;
   }

   virtual iProbes& probes()
   {
      return impl::getProbes();
   }

   virtual int main_thunk(int argc, const char *argv[], inner_main_f inner)
   {
      std::cout << "heap{{" << std::endl;
      allTrackers().dumpStats(callsiteHere());

      std::cout << "program-main{{" << std::endl;
      auto rval = inner(argc,argv);
      std::cout << "}}program-main" << std::endl;

      allTrackers().dumpOutstanding(callsiteHere());
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
      // configure default settings
   }
   return &gIntf;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
   return TRUE;
}
