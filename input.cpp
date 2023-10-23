#include "input.h"
#include <iostream>
input::input(cl_base* p_head_object, std::string s_object_name):cl_base(p_head_object,s_object_name){}
void input::signal(std::string & message){
	getline(std::cin, message);
}
void input::handler(std::string message){

}
