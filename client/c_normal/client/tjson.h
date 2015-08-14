#include <fstream>
#include <cassert>
#include "jsonPP/include/json/json.h"
using namespace std;


void TestJson(){
	ifstream ifs;
	ifs.open("test.json");
	assert(ifs.is_open());
	
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
				   return ;
			   }	              	
	           std::string name = root["name"].asString();
	           int age = root["age"].asInt();
	
		            std::cout << name << std::endl;
	          cout << age << std::endl;

			  getchar();
			  getchar();
}