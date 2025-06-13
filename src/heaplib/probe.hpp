#pragma once

namespace heaplib {

class probeBase {
protected:
   static void onCtor(void *p, const char *file, unsigned long line);
   static void onDtor(void *p);
};

#define HEAPLIB_PROBE() \
   struct _info { \
      static const char *getFile() { return __FILE__; } \
      static unsigned long getLine() { return __LINE__; } \
   }; \
   ::heaplib::probe<_info> _p;

template<class T>
class probe : private probeBase {
public:
   probe() { onCtor(this,T::getFile(),T::getLine()); }
   ~probe() { onDtor(this); }

   probe(const probe<T>&) {}
   probe<T>& operator=(const probe<T>&) { return *this; }
};

} // namespace heaplib
