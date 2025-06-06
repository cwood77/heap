#pragma once
#include <map>
#include <string>

namespace heapbin {
namespace impl {

#define callsiteHere() ::heapbin::impl::callsite(__FUNCTION__,__FILE__,__LINE__)
class callsite {
public:
   callsite(const char *u, const char *f, int l) : func(u), file(f), line(l) {}

   const char *func;
   const char *file;
   int line;
};

class allocFlags {
public:
   static allocFlags opNew() { return allocFlags("new",false); }

   allocFlags(const char *f, bool c) : stdlibFunc(f), clearMem(c) {}

   const char *stdlibFunc;
   bool clearMem;
};

class iHeap {
public:
   virtual void push() = 0;
   virtual void pop() = 0;

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

   virtual void checkConsistency(
      const callsite& cs) = 0;
   virtual void checkEnd(
      const callsite& cs) = 0;
};

extern iHeap *gHeadHeap;
extern iHeap& primordialHeap();
extern iHeap& guardedHeap();

} // namespace impl
} // namespace heapbin
