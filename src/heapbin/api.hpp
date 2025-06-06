#pragma once
#include <cstddef>

namespace heapbin {

typedef int (*inner_main_f)(int,const char*[]);

class iHeapIntf {
public:
   virtual void *new_thunk(size_t z) const = 0;
   virtual void delete_thunk(void *ptr) const = 0;
   virtual int main_thunk(int argc, const char *argv[], inner_main_f inner) const = 0;
};

} // namespace heapbin

extern "C" heapbin::iHeapIntf *getHeapIntf();
