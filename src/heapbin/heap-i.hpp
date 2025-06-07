#pragma once
#include <map>
#include <string>
#include "api.hpp"

namespace heapbin {
namespace impl {

class allocFlags {
public:
   static allocFlags opNew() { return allocFlags("new",false); }

   allocFlags(const char *f, bool c) : stdlibFunc(f), clearMem(c) {}

   const char *stdlibFunc;
   bool clearMem;
};

class iHeap {
public:
   static iHeap& get();

   // guard size
   // breakpoints
   virtual void configure(
      std::map<std::string,int>& settings,
      const callsite& cs) = 0;

   virtual void *alloc(
      size_t n, size_t z,
      const allocFlags& f,
      const callsite& cs) = 0;

   // realloc

   virtual void free(
      void *ptr,
      const callsite& cs) = 0;

   virtual void checkConsistency(const callsite& cs) = 0;
   virtual void dumpStats(const callsite& cs) = 0;
   virtual void dumpOutstanding(const callsite& cs) = 0;
};

} // namespace impl
} // namespace heapbin
