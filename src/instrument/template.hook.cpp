#include "api-i.hpp"
#include <iostream>

namespace instrument {
namespace {

class Template : public impl::iTemplate {
public:
   virtual bool shouldInject(const std::string& line)
   {
#if 0
      if(line.empty())
         return false;

      if(impl::startsWithOrIs(line,"//") || impl::startsWithOrIs(line,"/*"))
         return false;

      if(impl::startsWithOrIs(line,"#"))
         return false;
#endif

      return true;
   }

   virtual void inject(const std::string& line, std::ostream& o)
   {
      std::cout << "  injecting hook template" << std::endl;
      o << "// wrap/hook memory routines" << std::endl;
      o << "// (injected by instrument.exe)" << std::endl;
      o << "#include \"../heaplib/hooks.h\"" << std::endl;
      o << std::endl;
      o << line << std::endl;
   }
};

impl::autoTemplate<Template> gTemplate;

} // anonymous namespace
} // namespace instrument
