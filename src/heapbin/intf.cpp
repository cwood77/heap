#define WIN32_LEAN_AND_MEAN
#include "api.hpp"
#include "heap-i.hpp"
#include <iostream>
#include <windows.h>

namespace heapbin {
namespace {
using namespace impl;

class heapIntf : public iHeapIntf {
public:
   virtual void *new_thunk(size_t z, const callsite& cs) const
   {
      return iHeap::get().alloc(1,z,allocFlags::opNew(),cs);
   }

   virtual void delete_thunk(void *ptr, const callsite& cs) const
   {
      iHeap::get().free(ptr,cs);
   }

   virtual int main_thunk(int argc, const char *argv[], inner_main_f inner) const
   {
      std::cout << "heap{{" << std::endl;
      iHeap::get().dumpStats(callsiteHere());

      std::cout << "program-main{{" << std::endl;
      auto rval = inner(argc,argv);
      std::cout << "}}program-main" << std::endl;

      iHeap::get().dumpOutstanding(callsiteHere());
      std::cout << "}}heap" << std::endl;
      return rval;
   }
};

} // anonymous namespace
} // namespace heapbin

extern "C" heapbin::iHeapIntf *getHeapIntf()
{
   static heapbin::heapIntf gIntf;
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
