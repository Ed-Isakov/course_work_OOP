#include "output.h"
#include <iostream>
output::output(cl_base* p_head_object, std::string s_object_name):cl_base(p_head_object,s_object_name){}

void output::handler(std::string message){
	std::cout << message;
}
