#include "controller.h"

controller::controller(cl_base* p_head_object, std::string s_name):cl_base(p_head_object, s_name){}
void controller::signal(std::string & message){
}
void controller::handler(std::string message){
	if (message=="Turn off the system") return;
	std::vector<std::string> vec;
	std::string buf;
	for (char c: message){
		if(c!=' '){
			buf.push_back(c);
		}else{
			if (buf.size()!=0){
				vec.push_back(buf);
				buf.clear();
			}
		}
	}
	if (buf.size()!=0){
		vec.push_back(buf);
		buf.clear();
	}
	if (vec.size()==0 || vec[0]=="Car") return;
	if (vec[0]=="Switching"){
		cl_base* traffic = get_subordinate_object("traffic_light");
		std::string mes = vec[3]+" "+vec[4];
		emit_signal(SIGNAL_D(controller::signal), mes);
	}else if (vec[0]=="Display"){
		emit_signal(SIGNAL_D(controller::signal), vec[0]);
	}
}
