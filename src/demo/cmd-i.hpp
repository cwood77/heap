#pragma once

#include <stdexcept>
#include <string>
#include <map>

namespace demo {
namespace impl {

namespace types {
enum t {
   kScalarNew
};
} // namespace types;

inline types::t parseType(const std::string& s)
{
   if(s == "new")
      return types::kScalarNew;
   else
      throw std::runtime_error("can't parse type argument");
}

class iCommand {
public:
   virtual void run(types::t t) const = 0;
};

class commandRegistry {
public:
   static commandRegistry& get();

   void publish(const std::string& name, iCommand& c);

   iCommand& demand(const std::string& name);

private:
   commandRegistry() {}
   commandRegistry(const commandRegistry&);
   commandRegistry& operator=(const commandRegistry&);

   std::map<std::string,iCommand*> m_map;
};

template<class T>
class autoCommand : private T {
public:
   explicit autoCommand(const std::string& name)
   { commandRegistry::get().publish(name,*this); }
};

} // namespace impl
} // namespace demo
