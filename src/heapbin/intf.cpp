#define WIN32_LEAN_AND_MEAN
#include "api-i.hpp"
#include "api.hpp"
#include <iostream>
#include <windows.h>

namespace heapbin {
namespace impl {

iHeap *gHeadHeap = &primordialHeap();

} // namespace impl

namespace {
using namespace impl;

class heap : public iHeapIntf {
public:
   virtual void *new_thunk(size_t z) const
   {
      gHeadHeap->checkConsistency(callsiteHere());
      return gHeadHeap->alloc(1,z,allocFlags::opNew(),callsiteHere());
   }

   virtual void delete_thunk(void *ptr) const
   {
      gHeadHeap->checkConsistency(callsiteHere());
      gHeadHeap->free(ptr,callsiteHere());
   }

   virtual int main_thunk(int argc, const char *argv[], inner_main_f inner) const
   {
      std::cout << "heap{{" << std::endl;
      gHeadHeap->checkConsistency(callsiteHere());
      auto rval = inner(argc,argv);
      gHeadHeap->checkConsistency(callsiteHere());
      gHeadHeap->checkEnd(callsiteHere());
      std::cout << "}}heap" << std::endl;
      return rval;
   }
};

} // anonymous namespace
} // namespace heapbin

extern "C" heapbin::iHeapIntf *getHeapIntf()
{
   static heapbin::heap gHeap;
   static bool setup = false;
   if(!setup)
   {
      setup = true;

      heapbin::impl::gHeadHeap->checkConsistency(callsiteHere());
      heapbin::impl::guardedHeap().push();
      heapbin::impl::gHeadHeap->checkConsistency(callsiteHere());
   }
   return &gHeap;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
   return TRUE;
}
