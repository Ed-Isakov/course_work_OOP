#include "cl_application.h"
#include "cl_base.h"
#include "input.h"
#include "controller.h"
#include "road.h"
#include "output.h"
#include "traffic_light.h"
#include <iostream>
cl_application::cl_application(cl_base* p_head_object):cl_base(p_head_object){}
void cl_application::signal(std::string& message){
		message+=" (class: 1)";
		std::cout << "\nSignal from " << get_abs_path();
}
void cl_application::handler(std::string message){
	std::cout <<"\nSignal to " << get_abs_path() << " Text: " << message;
}
void cl_application::build_tree_objects(){
	cl_base* inp = new input(this, "input");
	cl_base* control = new controller(this, "controller");
	cl_base* road_to_the_dream = new road(this, "road");
	cl_base* outp = new output(this, "output");
	cl_base* traf = new traffic_light(control, "traffic_light");
	inp->set_connect(SIGNAL_D(input::signal), road_to_the_dream, HANDLER_D(road::handler));
	std::string s_command;
	while (s_command!="End of cars"){
		inp->emit_signal(SIGNAL_D(input::signal), s_command);
	}
	inp->destroy_connect(SIGNAL_D(input::signal), road_to_the_dream, HANDLER_D(road::handler));

}
int cl_application::exec_app(){
	std::cout << "Ready to work";
	std::string s_command;
	cl_base* inp = get_subordinate_object("input");
	cl_base* control = get_subordinate_object("controller");
	cl_base* road_to_the_dream = get_subordinate_object("road");
	cl_base* outp = get_subordinate_object("output");
	cl_base* traffic = control->get_subordinate_object("traffic_light");
	inp->set_connect(SIGNAL_D(input::signal), control, HANDLER_D(controller::handler));
	inp->set_connect(SIGNAL_D(input::signal), road_to_the_dream, HANDLER_D(road::handler_2));
	road_to_the_dream->set_connect(SIGNAL_D(road::signal), outp, HANDLER_D(output::handler));
	control->set_connect(SIGNAL_D(controller::signal), traffic, HANDLER_D(traffic_light::handler));
	traffic->set_connect(SIGNAL_D(traffic_light::signal), road_to_the_dream, HANDLER_D(road::handler_3));
	traffic->set_connect(SIGNAL_D(traffic_light::signal2), outp, HANDLER_D(output::handler));
	std::string p_command = "color -1";
	inp->emit_signal(SIGNAL_D(input::signal), s_command);
	//std::cout <<0;
	while (s_command!="Turn off the system"){
		//std::cout << s_command << '\n';
		control->emit_signal(SIGNAL_D(controller::signal), p_command);
		inp->emit_signal(SIGNAL_D(input::signal), s_command);

	}
	std::cout << "\nTurn off the system";
	return 0;
}
