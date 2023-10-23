#ifndef __INPUT__H
#define __INPUT__H
#include "cl_base.h"
class input:public cl_base{
public:
	input(cl_base* p_head_object, std::string s_object_name);
	void signal(std::string&);
	void handler(std::string);
};


#endif
