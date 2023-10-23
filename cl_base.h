#ifndef CL_BASE_H_INCLUDED
#define CL_BASE_H_INCLUDED
#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HANDLER_D( handler_f ) ( TYPE_HANDLER ) ( & handler_f )
#include <vector>
#include <string>

class cl_base{

public:
typedef void ( cl_base :: * TYPE_SIGNAL ) ( std::string & );
typedef void ( cl_base :: * TYPE_HANDLER ) ( std::string );
struct o_sh{
	TYPE_SIGNAL  p_signal;    // ”казатель на метод сигнала
	cl_base    * p_cl_base;   // ”казатель на целевой объект
	TYPE_HANDLER p_handler;   // ”казатель на метод обработчика
};
	cl_base ( cl_base * p_head_object,std::string s_object_name = "Base_object");
	bool edit_name(std::string new_name);
	std::string get_name();
	cl_base* get_head_object();
	void print_tree(int level=0);
	cl_base* get_subordinate_object(std::string name);
	~cl_base();
	cl_base* find_on_branch(std::string);
	cl_base* find_on_tree(std::string);
	void set_is_ready(int);
	void print_tree_ready(int level = 0);
	bool edit_head_object(cl_base*);
	void delete_sub(std::string);
	cl_base* find_on_path(std::string);
	void set_connect ( TYPE_SIGNAL    p_signal,     cl_base      * p_object,     TYPE_HANDLER   p_ob_hendler );
	void destroy_connect( TYPE_SIGNAL    p_signal,     cl_base      * p_object,     TYPE_HANDLER   p_ob_hendler );
	void emit_signal ( TYPE_SIGNAL p_signal, std::string & s_command );
	std::string get_abs_path();
	void set_class_number(int);
	int get_class_number();
	std::vector <cl_base* > get_subs();
private:
	std::vector < o_sh * > connects;
	cl_base * p_head_object;
	std::vector < cl_base * > subordinate_objects;
	std::string s_object_name;
	int is_ready=1;
	int class_number;
};



#endif // CL_BASE_H_INCLUDED
