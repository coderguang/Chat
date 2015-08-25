#ifndef _COMMON_UTIL_FUNCPTR_H_
#define _COMMON_UTIL_FUNCPTR_H_

#include <string>

namespace GCommon{
  namespace GUtil{


using voFuncInt=void (*)(int);
using voFuncIntCharptr=void (*)(int,char*);
using voFuncIntInt=void (*)(int,int);
using voFuncIntStr=void (*)(int,std::string);
using voFuncStr=void (*)(std::string);

  }
}
#endif
