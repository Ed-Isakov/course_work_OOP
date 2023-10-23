#include "road.h"
#include "car.h"
#include <iostream>
#include <algorithm>
road::road(cl_base* p_head_object, std::string s_object_name):cl_base(p_head_object, s_object_name){}


void road::signal(std::string & message){
	message="\n"+message;
}
void road::handler(std::string message){
	//std::cout << message << '\n';
	if (message=="End of cars") return;
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
	if (vec.size()==1){
		int n = stoi(vec[0]);
		//std::cout << n;
		left.resize(2*n, nullptr);
		right.resize(2*n, nullptr);
		up.resize(2*n, nullptr);
		down.resize(2*n, nullptr);

	}
	if (vec.size()==3){
		std::string name = vec[0];
		int x = stoi(vec[1]);
		int y = stoi(vec[2]);
		if (y==1){
			int ind = left.size()/2-x;
			if (ind>left.size()/2) ind--;
			left[ind] = new car(this, name);
		}else if (x==-1){
			int ind = down.size()/2-y;
			if (ind>down.size()/2) ind--;
			down[ind] = new car(this, name);
		}else if (y==-1){
			int ind = right.size()/2+x;
			if (ind>right.size()/2) ind--;
			right[ind] = new car(this, name);
		}else{
			int ind = up.size()/2+y;
			//std::cout <<up.size()/2+y;
			if (ind>up.size()/2) ind--;
			up[ind] = new car(this, name);
		}
	}
}
std::string road::find_car(std::string name){
	cl_base* sub = get_subordinate_object(name);
	if (sub){
		for (int i=0; i<left.size(); i++){
			if (left[i]==sub){
				std::string mes="";
				mes+=sub->get_name();
				int ind = left.size()/2-i;
				if (ind<1) ind--;
				mes+=" ( " +std::to_string(ind)+", 1 )";
				return mes;
			}
		}
		for (int i=0; i<down.size(); i++){
			if (down[i]==sub){
				std::string mes="";
				mes+=sub->get_name();
				int ind = down.size()/2-i;
				if (ind<1) ind--;
				mes+=" ( -1, "+std::to_string(ind)+" )";
				return mes;
			}
		}
		for (int i=0; i<right.size(); i++){
			if (right[i]==sub){
				std::string mes="";
				mes+=sub->get_name();
				int ind = -right.size()/2+i;
				if (ind>-1) ind++;
				mes+=" ( " +std::to_string(ind)+", -1 )";
				return mes;
			}
		}
		for (int i=0; i<up.size(); i++){
			if (up[i]==sub){
				std::string mes="";
				mes+=sub->get_name();
				int ind = -up.size()/2+i;
				//std::cout << '\n' << i << '\n';
				if (ind>-1) ind++;
				mes+=" ( 1, "+std::to_string(ind)+" )";
				return mes;
			}
		}
	}
	return "";
}
bool cmp(cl_base* obj1, cl_base* obj2){
	return obj1->get_name()<obj2->get_name();
}
void road::handler_2(std::string message){
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
	if (vec.size()==0 || vec[0]=="Switching") return;
	if (vec[0]=="Car"){
		std::string place = find_car(vec[1]);
		if (place==""){
			std::string mes = vec[1]+" the car left the road section";
			emit_signal(SIGNAL_D(road::signal), mes);
		} else{
			std::string mes = "Car "+place;
			emit_signal(SIGNAL_D(road::signal), mes);
		}
	}else if(message=="Display the system status"){
		std::vector <cl_base*> subs = get_subs();
		sort(subs.begin(), subs.end(), cmp);
		for (auto e:subs){
			std::string mes = find_car(e->get_name());
			emit_signal(SIGNAL_D(road::signal), mes);
			//std::cout << "Car "+e->get_name();
		}
	}
}
void road::handler_3(std::string message){
	if (message=="green"){
		if (left[left.size()-1]){
			cl_base* ptr = left[left.size()-1];
			left[left.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=left.size()-2; i>=0; i--){
			left[i+1]=left[i];
			left[i]=nullptr;
		}
		if (down[down.size()-1]){
			cl_base* ptr = down[down.size()-1];
			down[down.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=down.size()-2; i>down.size()/2-2; i--){
			down[i+1]=down[i];
			down[i]=nullptr;
		}
		for (int i=down.size()/2-3; i>=0; i--){
			if (down[i+1]==nullptr){
				down[i+1]=down[i];
				down[i]=nullptr;
			}
		}
		if (right[right.size()-1]){
			cl_base* ptr = right[right.size()-1];
			right[right.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=right.size()-2; i>=0; i--){
			right[i+1]=right[i];
			right[i]=nullptr;
		}
		if (up[up.size()-1]){
			cl_base* ptr = up[up.size()-1];
			up[up.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=up.size()-2; i>up.size()/2-2; i--){
			up[i+1]=up[i];
			up[i]=nullptr;
		}
		for (int i=up.size()/2-3; i>=0; i--){
			if (up[i+1]==nullptr){
				up[i+1]=up[i];
				up[i]=nullptr;
			}
		}
	}else if (message=="red"){
		if (down[down.size()-1]){
			cl_base* ptr = down[down.size()-1];
			down[down.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=down.size()-2; i>=0; i--){
			down[i+1]=down[i];
			down[i]=nullptr;
		}
		if (left[left.size()-1]){
			cl_base* ptr = left[left.size()-1];
			left[left.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=left.size()-2; i>left.size()/2-2; i--){
			left[i+1]=left[i];
			left[i]=nullptr;
		}
		for (int i=left.size()/2-3; i>=0; i--){
			if (left[i+1]==nullptr){
				left[i+1]=left[i];
				left[i]=nullptr;
			}
		}
		if (up[up.size()-1]){
			cl_base* ptr = up[up.size()-1];
			up[up.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=up.size()-2; i>=0; i--){
			up[i+1]=up[i];
			up[i]=nullptr;
		}
		if (right[right.size()-1]){
			cl_base* ptr = right[right.size()-1];
			right[right.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=right.size()-2; i>right.size()/2-2; i--){
			right[i+1]=right[i];
			right[i]=nullptr;
		}
		for (int i=right.size()/2-3; i>=0; i--){
			if (right[i+1]==nullptr){
				right[i+1]=right[i];
				right[i]=nullptr;
			}
		}
	} else{
		if (left[left.size()-1]){
			cl_base* ptr = left[left.size()-1];
			left[left.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=left.size()-2; i>left.size()/2-2; i--){
			left[i+1]=left[i];
			left[i]=nullptr;
		}
		for (int i=left.size()/2-3; i>=0; i--){
			if (left[i+1]==nullptr){
				left[i+1]=left[i];
				left[i]=nullptr;
			}
		}
		if (down[down.size()-1]){
			cl_base* ptr = down[down.size()-1];
			down[down.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=down.size()-2; i>down.size()/2-2; i--){
			down[i+1]=down[i];
			down[i]=nullptr;
		}
		for (int i=down.size()/2-3; i>=0; i--){
			if (down[i+1]==nullptr){
				down[i+1]=down[i];
				down[i]=nullptr;
			}
		}
		if (right[right.size()-1]){
			cl_base* ptr = right[right.size()-1];
			right[right.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=right.size()-2; i>right.size()/2-2; i--){
			right[i+1]=right[i];
			right[i]=nullptr;
		}
		for (int i=right.size()/2-3; i>=0; i--){
			if (right[i+1]==nullptr){
				right[i+1]=right[i];
				right[i]=nullptr;
			}
		}
		if (up[up.size()-1]){
			cl_base* ptr = up[up.size()-1];
			up[up.size()-1] = nullptr;
			delete_sub(ptr->get_name());
		}
		for (int i=up.size()-2; i>up.size()/2-2; i--){
			up[i+1]=up[i];
			up[i]=nullptr;
		}
		for (int i=up.size()/2-3; i>=0; i--){
			if (up[i+1]==nullptr){
				up[i+1]=up[i];
				up[i]=nullptr;
			}
		}
	}
}
