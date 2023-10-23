#ifndef __CAR__H
#define __CAR__H
#include "cl_base.h"
class car:public cl_base{
public:
	car(cl_base* p_head_object, std::string s_object_name);
	void signal(std::string&);
	void handler(std::string);
};



#endif
