#pragma once
#include <cstddef>
#include <map>
#include <string>

namespace heapbin {

#define callsiteHere() ::heapbin::callsite(__FUNCTION__,__FILE__,__LINE__)
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

class iTracker {
public:
   // guard size
   // breakpoints
   virtual void configure(
      std::map<std::string,int>& settings,
      const callsite& cs) = 0;

   virtual void checkConsistency(const callsite& cs) = 0;
   virtual void dumpStats(const callsite& cs) = 0;
   virtual void dumpOutstanding(const callsite& cs) = 0;
};

class iHeap : public iTracker {
public:
   virtual void *alloc(
      size_t n, size_t z,
      const allocFlags& f,
      const callsite& cs) = 0;

   // realloc

   virtual void free(
      void *ptr,
      const callsite& cs) = 0;
};

class iProbes : public iTracker {
public:
   virtual void add(
      void *p,
      const callsite& cs) = 0;

   virtual void remove(
      void *p) = 0;
};

typedef int (*inner_main_f)(int,const char*[]);

class iLibIntf {
public:
   virtual iTracker& allTrackers() = 0;
   virtual iHeap& heap() = 0;
   virtual iProbes& probes() = 0;
   virtual int main_thunk(int argc, const char *argv[], inner_main_f inner) = 0;
};

} // namespace heapbin

extern "C" heapbin::iLibIntf *getIntf();
