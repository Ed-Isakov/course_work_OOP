#ifndef __TRAFFIC_LIGHT__H
#define __TRAFFIC_LIGHT__H
#include "cl_base.h"
class traffic_light:public cl_base{
public:
	traffic_light(cl_base* p_head_object, std::string s_object_name);
	void signal(std::string&);
	void signal2(std::string&);
	void handler(std::string);
	void change(std::string color, int time=-1);
private:
	std::string curr_color = "green";
	std::string prev_color = "yellow";
	int time_pass=0;
	int green_time=5;
	int red_time=5;
	int yellow_time=2;
};


#endif
