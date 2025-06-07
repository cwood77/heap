#include "api-i.hpp"
#include <iostream>

namespace instrument {
namespace {

class Template : public impl::iTemplate {
public:
   virtual bool shouldInject(const std::string& line)
   {
      return impl::startsWithOrIs(line,"int main(int argc, const char *argv[])");
   }

   virtual void inject(const std::string& line, std::ostream& o)
   {
      std::cout << "  injecting hook template" << std::endl;
      o << "// wrap/hook main" << std::endl;
      o << "// (injected by instrument.exe)" << std::endl;
      o << "// [gaudi:type-hint]exe" << std::endl;
      o << "HEAPLIB_MAIN" << (line.c_str()+8) << std::endl;
   }

   virtual bool done() { return true; }
};

impl::autoTemplate<Template> gTemplate;

} // anonymous namespace
} // namespace instrument
