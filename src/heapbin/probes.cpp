#include "api.hpp"
#include <iostream>
#include <map>
#include <stdexcept>

namespace heapbin {
namespace {

class probe {
public:
   probe(unsigned long i, const callsite& cs) : i(i), creator(cs) {}

   unsigned long i;
   callsite creator;

   void dump(void *p);
};

class probes : public iProbes {
public:
   probes()
   : m_nAllocs(0)
   , m_nFrees(0)
   , m_i(0)
   {
   }

   virtual void configure(
      std::map<std::string,int>& settings,
      const callsite& cs);

   virtual void checkConsistency(const callsite& cs);
   virtual void dumpStats(const callsite& cs);
   virtual void dumpOutstanding(const callsite& cs);

   virtual void add(void *p, const callsite& cs);
   virtual void remove(void *p);

private:
   unsigned long m_nAllocs;
   unsigned long m_nFrees;
   unsigned long m_i;
   std::map<void*,probe*> m_probes;
} gProbes;

void probe::dump(void *p)
{
   std::cout << "probe" << std::endl;
   std::cout << "   " << creator.file << "; line " << creator.line << std::endl;
   std::cout << "   #" << i << std::endl;
}

void probes::configure(std::map<std::string,int>& settings, const callsite& cs)
{
}

void probes::add(void *p, const callsite& cs)
{
   m_nAllocs++;
   m_probes[p] = new probe(m_i++,cs);
}

void probes::remove(void *p)
{
   m_nFrees++;
   delete m_probes[p];
   m_probes.erase(p);
}

void probes::checkConsistency(const callsite& cs)
{
}

void probes::dumpStats(const callsite& cs)
{
   std::cout << "[probes] " << m_nAllocs << " allocation(s)" << std::endl;
   std::cout << "[probes] " << m_nFrees << " frees(s)" << std::endl;
}

void probes::dumpOutstanding(const callsite& cs)
{
   dumpStats(cs);
   for(auto it=m_probes.begin();it!=m_probes.end();++it)
      it->second->dump(it->first);
}

} // anonymous namespace
namespace impl {

iProbes& getProbes() { return gProbes; }

} // namespace impl
} // namespace heapbin
