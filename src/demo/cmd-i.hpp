#pragma once

#include <map>
#include <string>

namespace demo {
namespace impl {

class iType {
public:
   virtual void normal() const = 0;
   virtual void leak() const = 0;
};

class typeRegistry {
public:
   static typeRegistry& get();

   void publish(const std::string& name, iType& c);

   iType& demand(const std::string& name);

private:
   typeRegistry() {}
   typeRegistry(const typeRegistry&);
   typeRegistry& operator=(const typeRegistry&);

   std::map<std::string,iType*> m_map;
};

template<class T>
class autoType : private T {
public:
   explicit autoType(const std::string& name)
   { typeRegistry::get().publish(name,*this); }
};

} // namespace impl
} // namespace demo
