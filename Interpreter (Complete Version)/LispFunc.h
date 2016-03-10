#ifndef LISP_INTERPRETER
#define LISP_INTERPRETER

struct linked_list_node;

extern linked_list_node* d_list;

extern linked_list_node* a_list;

void lisp_apply(linked_list_node* function_address, linked_list_node** operation_node);

void lisp_operation(linked_list_node* root_node, linked_list_node** cur_node);

void lisp_func(std::string function_name, linked_list_node** operation_node);

void lisp_quote(linked_list_node** operation_node);

void lisp_cons(linked_list_node** operation_node);

void lisp_car(linked_list_node** operation_node);

void lisp_cdr(linked_list_node** operation_node);

void lisp_atom(linked_list_node** operation_node);

void lisp_int(linked_list_node** operation_node);

void lisp_null(linked_list_node** operation_node);

void lisp_eq(linked_list_node** operation_node);

void lisp_plus(linked_list_node** operation_node);

void lisp_minus(linked_list_node** operation_node);

void lisp_times(linked_list_node** operation_node);

void lisp_less(linked_list_node** operation_node);

void lisp_greater(linked_list_node** operation_node);

void lisp_cond(linked_list_node** operation_node);

void lisp_defun(linked_list_node** operation_node);

linked_list_node* lisp_a_list_search(std::string variable_name);

linked_list_node* lisp_d_list_search(std::string variable_name);

void lisp_deep_copy(linked_list_node* original_node, linked_list_node* target_node, int flag_left_right, int* flag_root);

#endif
