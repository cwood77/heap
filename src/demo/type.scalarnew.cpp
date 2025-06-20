// wrap/hook memory routines
// (injected by instrument.exe)
#include "../heaplib/hooks.h"
#include "../heaplib/probe.hpp"

#include "cmd-i.hpp"
#include <iostream>

namespace demo {
namespace {

class type : public impl::iType {
public:
   virtual void normal() const
   {
      std::cout << "allocating stuff" << std::endl;
      auto *pPtr = new int;

      std::cout << "accessing stuff" << std::endl;
      *pPtr = 7;

      std::cout << "freeing stuff" << std::endl;
      delete pPtr;
   }

   virtual void leak() const
   {
      std::cout << "leaking stuff" << std::endl;
      new int;
   }

private:
   HEAPLIB_PROBE();
};

impl::autoType<type> gType("scalarnew");

} // anonymous namespace
} // namespace demo
