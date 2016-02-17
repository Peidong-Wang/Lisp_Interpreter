#include <string>
using namespace std;

struct linked_list_node;

void lisp_operation(linked_list_node* root_node, linked_list_node** cur_node);

void lisp_build_in_func(string function_name, linked_list_node** operation_node);

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
