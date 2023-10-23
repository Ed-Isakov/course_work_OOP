#include "traffic_light.h"
#include <iostream>
traffic_light::traffic_light(cl_base* p_head_object, std::string s_name):cl_base(p_head_object, s_name){}
void traffic_light::signal(std::string & message){

}
void traffic_light::signal2(std::string & message){
	message="\nTraffic light color is "+message;
}
void traffic_light::change(std::string color, int time){
	//std::cout << '\n' << curr_color << '\n';
	if (time==-1){
		if (curr_color=="green" && time_pass>=green_time){
			time_pass=0;
			curr_color="yellow";
			prev_color="green";
		}
		if (curr_color=="yellow" && time_pass>=yellow_time){
			time_pass=0;
			if (prev_color=="green") curr_color = "red";
			if (prev_color=="red") curr_color = "green";
		}
		if (curr_color=="red" && time_pass>=red_time){
			time_pass=0;
			curr_color="yellow";
			prev_color="red";
		}
		emit_signal(SIGNAL_D(traffic_light::signal), curr_color);
		time_pass++;
	}else{
		if (color=="yellow" || time<2) return;
		if (color=="green") green_time = time;
		if (color=="red") red_time = time;
	}
}

void traffic_light::handler(std::string message){
	if (message=="Display"){
		std::string col=curr_color;
		emit_signal(SIGNAL_D(traffic_light::signal2), col);
		return;
	}
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
	int time=stoi(vec[1]);
	//std::cout<< '\n'<<time << '\n';
	change(vec[0], time);
}
