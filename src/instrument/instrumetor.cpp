#include "api-i.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

namespace instrument {
namespace impl {

bool startsWithOrIs(const std::string& line, const std::string& prefix)
{
   if(line.length() < prefix.length())
      return false;
   return ::strncmp(line.c_str(),prefix.c_str(),prefix.length())==0;
}

bool endsWith(const std::string& line, const std::string& suffix)
{
   if(line.length() < suffix.length())
      return false;
   auto offset = line.length() - suffix.length();
   return ::strncmp(line.c_str()+offset,suffix.c_str(),suffix.length())==0;
}

} // namespace impl
namespace {

class rewriter {
public:
   static bool run(const std::string& path, std::ostream& out)
   { return rewriter(path,out).run(); }

private:
   rewriter(const std::string& path, std::ostream& out)
   : m_in(path)
   , m_o(out)
   , m_templates(impl::templateRegistry::get().all())
   , m_madeChanges(false)
   {
      if(!m_in.good())
         throw std::runtime_error("can't open path: " + path);
   }

   bool run()
   {
      while(m_in.good())
      {
         std::string line;
         std::getline(m_in,line);
         if(!m_in.good() && line.empty())
            break;

         handleLine(line);
      }

      return m_madeChanges;
   }

   void handleLine(const std::string& line)
   {
      std::set<impl::iTemplate*> copy = m_templates;
      for(auto *pTmpt : copy)
      {
         if(pTmpt->shouldInject(line))
         {
            pTmpt->inject(line,m_o);
            m_madeChanges = true;
            m_templates.erase(pTmpt);
            return;
         }
      }

      m_o << line << std::endl;
   }

   std::ifstream m_in;
   std::ostream& m_o;
   std::set<impl::iTemplate*> m_templates;
   bool m_madeChanges;
};


} // anonymous namespace

namespace impl {

void saver::overwriteFile(const std::string& path, const std::string& contents)
{
   std::cout << "  saving file" << std::endl;
   std::ofstream(path) << contents;
}

void instrumentor::instrumentFile(const std::string& path)
{
   std::stringstream buffer;

   std::cout << "processing file " << path << std::endl;
   bool changed = rewriter::run(path,buffer);
   if(changed)
      m_s.overwriteFile(path,buffer.str());
   else
      std::cout << "  no changes to file" << std::endl;
}

} // namespace impl
} // namespace instrument
