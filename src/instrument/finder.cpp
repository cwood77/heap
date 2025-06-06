#define WIN32_LEAN_AND_MEAN
#include "api-i.hpp"
#include <stdexcept>
#include <windows.h>

namespace instrument {
namespace impl {

void finder::recurse(const std::string& path)
{
   WIN32_FIND_DATA fData;
   HANDLE hFind = ::FindFirstFileA((path + "\\*").c_str(),&fData);
   if(hFind == INVALID_HANDLE_VALUE)
      throw std::runtime_error("can't recurse on path");
   do
   {
      if(std::string(".") == fData.cFileName)
         continue;
      if(std::string("..") == fData.cFileName)
         continue;

      std::string fullPath = path + "\\" + fData.cFileName;

      if(fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         recurse(fullPath);
      else if(isCSource(fData.cFileName))
         m_i.instrumentFile(fullPath);
   }
   while(::FindNextFile(hFind,&fData));
   ::FindClose(hFind);
}

bool finder::isCSource(const std::string& filename)
{
   return endsWith(filename,".c") || endsWith(filename,".cpp");
}

} // namespace impl
} // namespace instrument
