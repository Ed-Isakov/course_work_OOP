#include "cl_base.h"
#include <iostream>
cl_base::cl_base(cl_base* p_head_object, std::string s_object_name){
	this -> p_head_object = p_head_object;
	this -> s_object_name = s_object_name;
	if ( p_head_object ){
		p_head_object -> subordinate_objects.push_back ( this ); // добавление в состав подчиненных головного объекта
	}
}
bool cl_base::edit_name(std::string new_name){
	if (this->p_head_object && this->p_head_object->get_subordinate_object(new_name)){
		return false;
	}
	this->s_object_name=new_name;
	return true;
}
std::string cl_base::get_name(){
	return this->s_object_name;
}
cl_base* cl_base::get_head_object(){
	return this->p_head_object;
}
void cl_base::print_tree(int level){
	std::cout << '\n';
	for (int i=0; i<level; i++){
		std::cout << "    ";
	}
	std::cout << this->get_name();
	for (auto elem:this->subordinate_objects){
		elem->print_tree(level+1);
	}
}
cl_base* cl_base::get_subordinate_object(std::string name){
	for (auto elem: this->subordinate_objects){
		if (elem->s_object_name==name){
			return elem;
		}
	}
	return nullptr;
}
cl_base::~cl_base(){
	for (int i=0; i<subordinate_objects.size(); i++){
		delete_sub(subordinate_objects[i]->get_name());
		i--;
	}
	cl_base* curr_obj=find_on_path("/");
	std::vector <cl_base*> queue;
	queue.push_back(curr_obj);
	for (int i=0; i<queue.size(); i++){
		for (auto e:queue[i]->subordinate_objects){
			queue.push_back(e);
		}
	}

	for (auto e:queue){
		for (int i=0; i<e->connects.size(); i++){
			if (e->connects[i]->p_cl_base==this){
				o_sh* ptr = e->connects[i];
				e->connects.erase(e->connects.begin()+i);
				delete ptr;
				break;
			}
		}
	}
}
cl_base* cl_base::find_on_branch(std::string name){
	std::vector <cl_base*> subs;
	std::vector <cl_base*> queue;
	for (auto e:subordinate_objects){
		subs.push_back(e);
		queue.push_back(e);
	}
	for (int i=0; i<queue.size(); i++){
		for (auto e:queue[i]->subordinate_objects){
			subs.push_back(e);
			queue.push_back(e);
		}
	}
	int cnt=0;
	cl_base* ans=nullptr;
	for (auto e:subs){
		if (e->get_name()==name){
			cnt++;
			ans=e;
		}
	}
	if (cnt>1) ans=nullptr;
	return ans;
}
cl_base* cl_base::find_on_tree(std::string name){
	cl_base* curr_obj = this;
	while (curr_obj->get_head_object()){
		curr_obj = curr_obj->get_head_object();
	}
	return curr_obj->find_on_branch(name);
}

void cl_base::set_is_ready(int x){
	if (x==0){
		this->is_ready=0;
		for (auto elem:this->subordinate_objects){
			elem->set_is_ready(0);
		}
	} else {
		if (this->get_head_object()==nullptr || this->get_head_object()->is_ready){
			this->is_ready=1;
		}
	}
}
void cl_base::print_tree_ready(int level){
	std::cout << '\n';
	for (int i=0; i<level; i++){
		std::cout << "    ";
	}
	std::cout << this->get_name();
	if (this->is_ready)
		std::cout << " is ready";
	else
		std::cout << " is not ready";
	for (auto elem:this->subordinate_objects){
		elem->print_tree_ready(level+1);
	}
}
bool cl_base::edit_head_object(cl_base* new_head_object){
	bool flag=0;
	cl_base* curr_obj=new_head_object;
	while (curr_obj->p_head_object){
		curr_obj=curr_obj->p_head_object;
		if (curr_obj==this) flag=1;
	}
	if (this->get_head_object()==nullptr || new_head_object==nullptr ||
		new_head_object->get_subordinate_object(s_object_name) || flag){
		return false;
	} else{
		for (int i=0; i<(p_head_object->subordinate_objects.size()); i++){
			if (p_head_object->subordinate_objects[i]==this){
				p_head_object->subordinate_objects.erase(p_head_object->subordinate_objects.begin()+i);
				break;
			}
		}
		this->p_head_object = new_head_object;
		new_head_object-> subordinate_objects.push_back ( this );
		return true;
	}
}
void cl_base::delete_sub(std::string sub_name){
	if (this->get_subordinate_object(sub_name)){
		cl_base* del_obj=this->get_subordinate_object(sub_name);
		for (int i=0; i<this->subordinate_objects.size(); i++){
			if (subordinate_objects[i]==del_obj){
				delete del_obj;
				subordinate_objects.erase(subordinate_objects.begin()+i);
				return;
			}
		}
	}
}
cl_base* cl_base::find_on_path(std::string path){
	if (path=="/"){
		cl_base* curr_obj = this;
		while (curr_obj->get_head_object()){
			curr_obj = curr_obj->get_head_object();
		}
		return curr_obj;
	}
	if (path[0]=='/' && path[1]=='/'){
		return (this->find_on_path("/"))->find_on_branch(path.substr(2, path.size()-2));
	}
	if (path=="."){
		return this;
	}
	if (path[0]=='.'){
		return this->find_on_branch(path.substr(1, path.size()-1));
	}
	if (path[0]=='/'){
		cl_base* curr_obj = this;
		while (curr_obj->get_head_object()){
			curr_obj = curr_obj->get_head_object();
		}
		return curr_obj->find_on_path(path.substr(1, path.size()-1));
	}
	std::string sub;
	int i=0;
	while(i<path.size() && path[i]!='/'){
		sub.push_back(path[i]);
		i++;
	}
	cl_base* curr_obj = this->get_subordinate_object(sub);
	if (i==path.size() || curr_obj==nullptr){
		return curr_obj;
	}else{
		return curr_obj->find_on_path(path.substr(i+1, path.size()-i-1));
	}
}
void cl_base :: set_connect ( TYPE_SIGNAL    p_signal, cl_base      * p_object, TYPE_HANDLER   p_ob_handler ){
	o_sh  * p_value;
	for ( unsigned int i = 0; i < connects.size ( ); i ++ )
	{
		if ( connects [ i ] -> p_signal  == p_signal     &&
			connects [ i ] -> p_cl_base == p_object     &&
			connects [ i ] -> p_handler == p_ob_handler    )
		{
			return;
		}
	}
	p_value =  new o_sh ( );
	p_value -> p_signal  = p_signal;
	p_value -> p_cl_base = p_object;
	p_value -> p_handler = p_ob_handler;
	connects.push_back ( p_value );
}
void cl_base :: destroy_connect ( TYPE_SIGNAL    p_signal, cl_base      * p_object, TYPE_HANDLER   p_ob_handler ){
	for ( unsigned int i = 0; i < connects.size ( ); i ++ )
	{
		if ( connects [ i ] -> p_signal  == p_signal     &&
			connects [ i ] -> p_cl_base == p_object     &&
			connects [ i ] -> p_handler == p_ob_handler    )
		{
			o_sh* ptr = connects [ i ];
			connects.erase(connects.begin()+i);
			delete ptr;
			return;
		}
	}
}
void cl_base :: emit_signal ( TYPE_SIGNAL p_signal, std::string & s_command )
{
	if (!is_ready) return;
	TYPE_HANDLER   p_handler;
	cl_base      * p_object;
	( this ->* p_signal ) ( s_command );
	for ( unsigned int i = 0; i < connects.size ( ); i ++ ) // цикл по всем обработчикам
	{
		if ( connects [ i ] -> p_signal == p_signal && connects[i]->p_cl_base->is_ready )      // определение допустимого обработчика
		{
			p_handler = connects [ i ] -> p_handler;
			p_object  = connects [ i ] -> p_cl_base;
			( p_object ->* p_handler ) ( s_command );      // вызов метода обработчика
		}
	}
}
std::string cl_base::get_abs_path(){
	cl_base* ptr = this;
	std::string abs_path;
	while (ptr->get_head_object()){
		abs_path = "/"+ptr->get_name()+abs_path;
		ptr=ptr->get_head_object();
	}
	if (abs_path=="") return "/";
	return abs_path;
}
void cl_base::set_class_number(int class_number){
	this->class_number=class_number;
}
int cl_base::get_class_number(){
	return class_number;
}
std::vector <cl_base*> cl_base::get_subs(){
	return subordinate_objects;
}
