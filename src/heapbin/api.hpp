#pragma once
#include <cstddef>

namespace heapbin {

#define callsiteHere() ::heapbin::callsite(__FUNCTION__,__FILE__,__LINE__)
class callsite {
public:
   callsite(const char *u, const char *f, int l) : func(u), file(f), line(l) {}

   const char *func;
   const char *file;
   int line;
};

typedef int (*inner_main_f)(int,const char*[]);

class iHeapIntf {
public:
   virtual void *new_thunk(size_t z, const callsite& cs) const = 0;
   virtual void delete_thunk(void *ptr, const callsite& cs) const = 0;
   virtual int main_thunk(int argc, const char *argv[], inner_main_f inner) const = 0;
};

} // namespace heapbin

extern "C" heapbin::iHeapIntf *getHeapIntf();
