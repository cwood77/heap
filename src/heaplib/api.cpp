#define WIN32_LEAN_AND_MEAN
#include "../heapbin/api.hpp"
#include "api.h"
#include "probe.hpp"
#include <stdexcept>
#include <windows.h>

static heapbin::iLibIntf& loadbin()
{
   static heapbin::iLibIntf *pLib = NULL;
   if(pLib)
      return *pLib;

   static HMODULE hLib = NULL;
   hLib = ::LoadLibraryA("heapbin.dll");
   ::LoadLibraryA("heapbin.dll"); // once more for good measure
   if(!hLib)
      throw std::runtime_error("cannot load heapbin.dll");

   typedef heapbin::iLibIntf *(*func_t)();
   auto f = (func_t)::GetProcAddress(hLib,"getIntf");
   if(!f)
      throw std::runtime_error("cannot link heapbin.dll");

   pLib = f();
   return *pLib;
}

// C API
// =================================================================================

extern "C" int heaplib_main(int argc, const char *argv[], heaplib_inner_main_f f)
{
   return loadbin().main_thunk(argc,argv,(heapbin::inner_main_f)f);
}

// C++ API
// =================================================================================

namespace heaplib {

void probeBase::onCtor(void *p, const char *file, unsigned long line)
{
   loadbin().probes().add(p,heapbin::callsite("",file,line));
}

void probeBase::onDtor(void *p)
{
   loadbin().probes().remove(p);
}

} // namespace heaplib
