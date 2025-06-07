#include "api.hpp"
#include <iostream>
#include <stdexcept>

namespace heapbin {
namespace {

class heap : public iHeap {
public:
   heap()
   : m_nAllocs(0)
   , m_nFrees(0)
   , m_i(0)
   {
   }

   virtual void configure(
      std::map<std::string,int>& settings,
      const callsite& cs);

   virtual void *alloc(
      size_t n, size_t z,
      const allocFlags& f,
      const callsite& cs);

   virtual void free(
      void *ptr,
      const callsite& cs);

   virtual void checkConsistency(const callsite& cs);
   virtual void dumpStats(const callsite& cs);
   virtual void dumpOutstanding(const callsite& cs);

private:
   unsigned long m_nAllocs;
   unsigned long m_nFrees;
   unsigned long m_i;
} gHeap;

void heap::configure(std::map<std::string,int>& settings, const callsite& cs)
{
   if(settings.size() != 0)
      throw std::runtime_error("primordial heap doesn't understand settings");
}

void *heap::alloc(size_t n, size_t z, const allocFlags& f, const callsite& cs)
{
   m_nAllocs++;
   return ::operator new(n*z);
}

void heap::free(void *ptr, const callsite& cs)
{
   m_nFrees++;
   ::operator delete(ptr);
}

void heap::checkConsistency(const callsite& cs)
{
}

void heap::dumpStats(const callsite& cs)
{
   std::cout << "[primordial] " << m_nAllocs << " allocation(s)" << std::endl;
   std::cout << "[primordial] " << m_nFrees << " frees(s)" << std::endl;
}

void heap::dumpOutstanding(const callsite& cs)
{
   dumpStats(cs);
}

} // anonymous namespace
namespace impl {

iHeap& getHeap() { return gHeap; }

} // namespace impl
} // namespace heapbin
