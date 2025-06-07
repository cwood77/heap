#include "api-i.hpp"
#include <iostream>

namespace instrument {
namespace {

class Template : public impl::iTemplate {
public:
   Template() : m_discardNext(false) {}

   virtual bool shouldInject(const std::string& line)
   {
      if(impl::startsWithOrIs(line,"enum "))
         m_discardNext = true;

      else if(line == "};")
      {
         bool handle = !m_discardNext;
         m_discardNext = false;
         return handle;
      }

      return false;
   }

   virtual void inject(const std::string& line, std::ostream& o)
   {
      std::cout << "  injecting probe template" << std::endl;
      o << std::endl;
      o << "private:" << std::endl;
      o << "   HEAPLIB_PROBE();" << std::endl;
      o << line << std::endl;
   }

   virtual bool done() { return false; }

private:
   bool m_discardNext;
};

impl::autoTemplate<Template> gTemplate;

} // anonymous namespace
} // namespace instrument
