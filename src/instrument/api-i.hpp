#pragma once

#include <set>
#include <string>

namespace instrument {
namespace impl {

extern bool startsWithOrIs(const std::string& line, const std::string& prefix);
extern bool endsWith(const std::string& line, const std::string& suffix);

class iTemplate {
public:
   virtual bool shouldInject(const std::string& line) = 0;
   virtual void inject(const std::string& line, std::ostream& o) = 0;
};

class templateRegistry {
public:
   static templateRegistry& get();

   void publish(iTemplate& t) { m_set.insert(&t); }

   std::set<iTemplate*> all() { return m_set; }

private:
   templateRegistry() {}
   templateRegistry(const templateRegistry&);
   templateRegistry& operator=(const templateRegistry&);

   std::set<iTemplate*> m_set;
};

template<class T>
class autoTemplate : private T {
public:
   autoTemplate() { templateRegistry::get().publish(*this); }
};

class saver {
public:
   void overwriteFile(const std::string& path, const std::string& contents);
};

class instrumentor {
public:
   explicit instrumentor(saver& s) : m_s(s) {}

   void instrumentFile(const std::string& path);

private:
   saver& m_s;
};

class finder {
public:
   explicit finder(instrumentor& i) : m_i(i) {}

   void recurse(const std::string& path);

private:
   static bool isCSource(const std::string& filename);

   instrumentor& m_i;
};

} // namespace impl
} // namespace instrument
