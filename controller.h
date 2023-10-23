#ifndef __CONTOROLLER__H
#define __CONTOROLLER__H

#include "cl_base.h"
class controller:public cl_base{
public:
	controller(cl_base* p_head_object, std::string s_object_name);
	void signal(std::string&);
	void handler(std::string);
	void handler_2(std::string);
};

#endif
