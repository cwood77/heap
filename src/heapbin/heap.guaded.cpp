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
   , m_pNext(NULL)
   {
   }

   virtual void push()
   {
      m_pNext = gHeadHeap;
      gHeadHeap = this;
   }

   virtual void pop()
   {
      gHeadHeap = m_pNext;
      m_pNext = NULL;
   }

   virtual void configure(
      std::map<std::string,int>& settings,
      const callsite& cs)
   {
      m_pNext->configure(settings,cs);
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
      m_pNext->checkConsistency(cs);
   }

   virtual void checkEnd(
      const callsite& cs)
   {
      std::cout << "[guarded] " << m_nAllocs << " allocation(s)" << std::endl;
      std::cout << "[guarded] " << m_nFrees << " frees(s)" << std::endl;
      m_pNext->checkEnd(cs);
   }

private:
   unsigned long m_nAllocs;
   unsigned long m_nFrees;
   iHeap *m_pNext;
} gHeap;

} // anonymous namespace

iHeap& guardedHeap() { return gHeap; }

} // namespace impl
} // namespace heapbin
