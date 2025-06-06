#include "api-i.hpp"
#include <iostream>
#include <stdexcept>

namespace heapbin {
namespace impl {
namespace {

class heap : public iHeap {
public:
   heap()
   : m_nAllocs(0)
   , m_nFrees(0)
   {
   }

   virtual void push()
   {
      throw std::runtime_error("can't push the primordial heap");
   }

   virtual void pop()
   {
      throw std::runtime_error("can't pop the primordial heap");
   }

   virtual void configure(
      std::map<std::string,int>& settings,
      const callsite& cs)
   {
      if(settings.size() != 0)
         throw std::runtime_error("primordial heap doesn't understand settings");
   }

   virtual void *alloc(
      size_t n, size_t z,
      const allocFlags& f,
      const callsite& cs)
   {
      m_nAllocs++;
      return ::operator new(n*z);
   }

   virtual void free(
      void *ptr,
      const callsite& cs)
   {
      m_nFrees++;
      ::operator delete(ptr);
   }

   virtual void checkConsistency(
      const callsite& cs)
   {
   }

   virtual void checkEnd(
      const callsite& cs)
   {
      std::cout << "[primordial] " << m_nAllocs << " allocation(s)" << std::endl;
      std::cout << "[primordial] " << m_nFrees << " frees(s)" << std::endl;
   }

private:
   unsigned long m_nAllocs;
   unsigned long m_nFrees;
} gHeap;

} // anonymous namespace

iHeap& primordialHeap() { return gHeap; }

} // namespace impl
} // namespace heapbin
