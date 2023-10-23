#ifndef __OUTPUT__H
#define __OUTPUT__H
#include "cl_base.h"
class output:public cl_base{
public:
	output(cl_base* p_head_object, std::string s_object_name);
	void signal(std::string&);
	void handler(std::string);
};


#endif
