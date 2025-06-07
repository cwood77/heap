#pragma once

namespace heaplib {

#define HEAPLIB_PROBE() foo

class probe {
public:
   probe();
   probe(const probe&);
   ~probe();

   probe& operator=(const probe&);
};

} // namespace heaplib
