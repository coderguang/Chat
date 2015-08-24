#include "Log.h"
using namespace GCommon::GLog;

void CLog::Log(std::string msg,std::string type){
    std::cout<<"type="<<type<<",msg="<<msg<<std::endl;
}
