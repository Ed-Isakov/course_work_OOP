#ifndef __ROAD__H
#define __ROAD__H
#include "cl_base.h"

class road: public cl_base{
public:
	road(cl_base* p_head_object, std::string s_object_name);
	void signal(std::string&);
	void handler(std::string);
	void handler_2(std::string);
	void handler_3(std::string);
	std::string find_car(std::string name);
private:
	std::vector <cl_base*> left;
	std::vector <cl_base*> down;
	std::vector <cl_base*> right;
	std::vector <cl_base*> up;
};


#endif
