#define WIN32_LEAN_AND_MEAN
#include "../heapbin/api.hpp"
#include "api.h"
#include <stdexcept>
#include <windows.h>

static heapbin::iHeapIntf& loadbin()
{
   static heapbin::iHeapIntf *pHeap = NULL;
   if(pHeap)
      return *pHeap;

   static HMODULE hLib = NULL;
   hLib = ::LoadLibraryA("heapbin.dll");
   ::LoadLibraryA("heapbin.dll"); // once more for good measure
   if(!hLib)
      throw std::runtime_error("cannot load heapbin.dll");

   typedef heapbin::iHeapIntf *(*func_t)();
   auto f = (func_t)::GetProcAddress(hLib,"getHeapIntf");
   if(!f)
      throw std::runtime_error("cannot link heapbin.dll");

   pHeap = f();
   return *pHeap;
}

extern "C" void *heaplib_new(size_t z)
{
   return loadbin().new_thunk(z,callsiteHere());
}

extern "C" void heaplib_delete(void *ptr)
{
   loadbin().delete_thunk(ptr,callsiteHere());
}

extern "C" int heaplib_main(int argc, const char *argv[], heaplib_inner_main_f f)
{
   return loadbin().main_thunk(argc,argv,(heapbin::inner_main_f)f);
}

void *operator new(std::size_t z)
{
   return heaplib_new(z);
}

void operator delete(void* p) _GLIBCXX_USE_NOEXCEPT
{
   heaplib_delete(p);
}
