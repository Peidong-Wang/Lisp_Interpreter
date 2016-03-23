#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "LispFunc.h"
using namespace std;

struct linked_list_node{
	string val;
	linked_list_node* left_node;
	linked_list_node* right_node;
	linked_list_node* parent_node;
	string color;
	linked_list_node(){
		val = "";
		left_node = NULL;
		right_node = NULL;
		parent_node = NULL;
		color = "WHITE";
	}
};

linked_list_node* a_list = NULL;

linked_list_node* d_list = NULL;

void lisp_operation(linked_list_node* root_node, linked_list_node** cur_node){
	linked_list_node* function_address;
	linked_list_node* temp_node_a_val_address;
	int flag_root_val = 1;
	if (root_node->left_node == NULL && root_node->right_node == NULL){
		if ((temp_node_a_val_address = lisp_a_list_search(root_node->val)) != NULL){
			flag_root_val = 1;
			lisp_deep_copy(temp_node_a_val_address, root_node, 0, &flag_root_val);
			return;
		}
	}
	while ((*cur_node)->left_node != NULL){
		if ((*cur_node)->left_node->val.compare("QUOTE") == 0){
			lisp_func("QUOTE", cur_node);
			break;
		}
		else if ((*cur_node)->left_node->val.compare("COND") == 0){
			lisp_func("COND", cur_node);
			break;
		}
		else if ((*cur_node)->left_node->val.compare("DEFUN") == 0){
			lisp_func("DEFUN", cur_node);
			break;
		}
		else if ((function_address = lisp_d_list_search((*cur_node)->left_node->val)) != NULL && ((*cur_node)->parent_node == NULL || (*cur_node)->parent_node->left_node == (*cur_node))){
			lisp_apply(function_address, cur_node);
			break;
		}
		(*cur_node) = (*cur_node)->right_node;
	}
	while ((*cur_node) != root_node){
		(*cur_node) = (*cur_node)->parent_node;
		if ((*cur_node)->left_node->left_node != NULL){
			(*cur_node) = (*cur_node)->left_node;
			lisp_operation((*cur_node), cur_node);
			(*cur_node) = (*cur_node)->parent_node;
		}
		else if (((*cur_node)->left_node->val.at(0) > '9' || (*cur_node)->left_node->val.at(0) < '0') && (*cur_node)->left_node->val != "NIL" && (*cur_node)->left_node->val != "T" && !((*cur_node)->left_node->val.at(0) == '-' && (*cur_node)->left_node->val.length() > 1 && (*cur_node)->left_node->val.at(1) >= '0' && (*cur_node)->left_node->val.at(1) <= '9')){
			lisp_func((*cur_node)->left_node->val, cur_node);
		}
		else if ((*cur_node) == root_node && (((*cur_node)->left_node->val.at(0) <= '9' && (*cur_node)->left_node->val.at(0) >= '0') || (*cur_node)->left_node->val == "NIL" || (*cur_node)->left_node->val == "T" || ((*cur_node)->left_node->val.at(0) == '-' && (*cur_node)->left_node->val.length() > 1 && (*cur_node)->left_node->val.at(1) >= '0' && (*cur_node)->left_node->val.at(1) <= '9'))){
			cout << "ERROR: Invalid function name (NIL, T or Integers) (From Interpreter)" << endl;
			exit(0);
		}
	}
}

void lisp_func(string function_name, linked_list_node** operation_node){
	linked_list_node* function_address;
	linked_list_node* temp_node_a_val_address;
	int flag_root_val = 1;
	if (function_name.compare("QUOTE") == 0){
		lisp_quote(operation_node);
	}
	else if (function_name.compare("CONS") == 0){
		lisp_cons(operation_node);
	}
	else if (function_name.compare("CAR") == 0){
		lisp_car(operation_node);
	}
	else if (function_name.compare("CDR") == 0){
		lisp_cdr(operation_node);
	}
	else if (function_name.compare("ATOM") == 0){
		lisp_atom(operation_node);
	}
	else if (function_name.compare("INT") == 0){
		lisp_int(operation_node);
	}
	else if (function_name.compare("NULL") == 0){
		lisp_null(operation_node);
	}
	else if (function_name.compare("EQ") == 0){
		lisp_eq(operation_node);
	}
	else if (function_name.compare("PLUS") == 0){
		lisp_plus(operation_node);
	}
	else if (function_name.compare("MINUS") == 0){
		lisp_minus(operation_node);
	}
	else if (function_name.compare("TIMES") == 0){
		lisp_times(operation_node);
	}
	else if (function_name.compare("LESS") == 0){
		lisp_less(operation_node);
	}
	else if (function_name.compare("GREATER") == 0){
		lisp_greater(operation_node);
	}
	else if (function_name.compare("COND") == 0){
		lisp_cond(operation_node);
	}
	else if (function_name.compare("DEFUN") == 0){
		lisp_defun(operation_node);
	}
	else if ((function_address = lisp_d_list_search(function_name)) != NULL && ((*operation_node)->parent_node == NULL || (*operation_node)->parent_node->left_node == (*operation_node))){
		lisp_apply(function_address, operation_node);
	}
	else if ((*operation_node)->parent_node != NULL && (*operation_node)->parent_node->left_node != (*operation_node) && (temp_node_a_val_address = lisp_a_list_search(function_name)) != NULL){
		flag_root_val = 1;
		lisp_deep_copy(temp_node_a_val_address, (*operation_node)->left_node, 0, &flag_root_val);
	}
	else {
		cout << "ERROR: Invalid function or parameter \"" << function_name << "\" (From Interpreter)" << endl;
		exit(0);
	}
}

void lisp_quote(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for QUOTE (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node->left_node;
	(*operation_node)->left_node = temp_node->left_node;
	if (temp_node->left_node != NULL){
		temp_node->left_node->parent_node = (*operation_node);
	}
	(*operation_node)->right_node = temp_node->right_node;
	if (temp_node->left_node != NULL){
		temp_node->right_node->parent_node = (*operation_node);
	}
	(*operation_node)->val = temp_node->val;
}

void lisp_cons(linked_list_node** operation_node){
	linked_list_node* left_sub_tree;
	linked_list_node* right_sub_tree;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for CONS (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	temp_node = (*operation_node)->right_node;
	left_sub_tree = temp_node->left_node;
	right_sub_tree = temp_node->right_node->left_node;
	(*operation_node)->left_node = left_sub_tree;
	left_sub_tree->parent_node = (*operation_node);
	(*operation_node)->right_node = right_sub_tree;
	right_sub_tree->parent_node = (*operation_node);
}

void lisp_car(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for CAR (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* left_sub_tree;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node->left_node;
	if (temp_node->left_node == NULL && temp_node->right_node == NULL){
		cout << "ERROR: Evaluation undefined for CAR (Splitting Atom) (From Interpreter)" << endl;
		exit(0);
	}
	left_sub_tree = temp_node->left_node;
	(*operation_node)->left_node = left_sub_tree->left_node;
	if (left_sub_tree->left_node != NULL){
		left_sub_tree->left_node->parent_node = (*operation_node);
	}
	(*operation_node)->right_node = left_sub_tree->right_node;
	if (left_sub_tree->left_node != NULL){
		left_sub_tree->right_node->parent_node = (*operation_node);
	}
	(*operation_node)->val = left_sub_tree->val;
	// delete left_sub_tree;
}

void lisp_cdr(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for CDR (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* right_sub_tree;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node->left_node;
	if (temp_node->left_node == NULL && temp_node->right_node == NULL){
		cout << "ERROR: Evaluation undefined for CDR (Splitting Atom) (From Interpreter)" << endl;
		exit(0);
	}
	right_sub_tree = temp_node->right_node;
	(*operation_node)->left_node = right_sub_tree->left_node;
	if (right_sub_tree->left_node != NULL){
		right_sub_tree->left_node->parent_node = (*operation_node);
	}
	(*operation_node)->right_node = right_sub_tree->right_node;
	if (right_sub_tree->left_node != NULL){
		right_sub_tree->right_node->parent_node = (*operation_node);
	}
	(*operation_node)->val = right_sub_tree->val;
}

void lisp_atom(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for ATOM (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node->left_node;
	if (temp_node->left_node == NULL && temp_node->right_node == NULL){
		(*operation_node)->val = "T";
	}
	else{
		(*operation_node)->val = "NIL";
	}
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_int(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for INT (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node->left_node;
	if (temp_node->left_node == NULL && temp_node->right_node == NULL && temp_node->val.at(0) <= '9' && temp_node->val.at(0) >= '0'){
		(*operation_node)->val = "T";
	}
	else if (temp_node->left_node == NULL && temp_node->right_node == NULL && temp_node->val.at(0) == '-' && temp_node->val.length() > 1 && temp_node->val.at(1) >= '0' && temp_node->val.at(1) <= '9'){
		(*operation_node)->val = "T";
	}
	else{
		(*operation_node)->val = "NIL";
	}
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_null(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for NULL (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node->left_node;
	if (temp_node->left_node == NULL && temp_node->right_node == NULL && temp_node->val.compare("NIL") == 0){
		(*operation_node)->val = "T";
	}
	else{
		(*operation_node)->val = "NIL";
	}
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_eq(linked_list_node** operation_node){
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for EQ (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	if ((temp_node->left_node->left_node != NULL || temp_node->left_node->right_node != NULL) || (temp_node->right_node->left_node->left_node != NULL || temp_node->right_node->left_node->right_node != NULL)){
		cout << "ERROR: Evaluation undefined for EQ (Parameter Type Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* left_parameter;
	linked_list_node* right_parameter;
	left_parameter = temp_node->left_node;
	right_parameter = temp_node->right_node->left_node;
	if (left_parameter->val.compare(right_parameter->val) == 0){
		(*operation_node)->val = "T";
	}
	else {
		(*operation_node)->val = "NIL";
	}
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_plus(linked_list_node** operation_node){
	int result_plus = 0;
	int result_temp = 0;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for PLUS (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	if ((temp_node->left_node->val.at(0) > '9' || temp_node->left_node->val.at(0) < '0' || temp_node->left_node->left_node != NULL || temp_node->left_node->right_node != NULL) || (temp_node->right_node->left_node->val.at(0) > '9' || temp_node->right_node->left_node->val.at(0) < '0' || temp_node->right_node->left_node->left_node != NULL || temp_node->right_node->left_node->right_node != NULL)){
		if (temp_node->left_node->val.at(0) != '-'){
			if (temp_node->left_node->val.length() == 1){
				cout << "ERROR: Evaluation undefined for PLUS (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
			else if (temp_node->left_node->val.at(1) < '0' || temp_node->left_node->val.at(1) > '9'){
				cout << "ERROR: Evaluation undefined for PLUS (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
		}
	}
	linked_list_node* left_parameter;
	linked_list_node* right_parameter;
	left_parameter = temp_node->left_node;
	right_parameter = temp_node->right_node->left_node;
	istringstream istr_l(left_parameter->val);
	istr_l >> result_temp;
	result_plus = result_temp;
	istringstream istr_r(right_parameter->val);
	istr_r >> result_temp;
	result_plus = result_plus + result_temp;
	ostringstream ostr;
	ostr << result_plus;
	(*operation_node)->val = ostr.str();
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_minus(linked_list_node** operation_node){
	int result_minus = 0;
	int result_temp = 0;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for MINUS (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	if ((temp_node->left_node->val.at(0) > '9' || temp_node->left_node->val.at(0) < '0' || temp_node->left_node->left_node != NULL || temp_node->left_node->right_node != NULL) || (temp_node->right_node->left_node->val.at(0) > '9' || temp_node->right_node->left_node->val.at(0) < '0' || temp_node->right_node->left_node->left_node != NULL || temp_node->right_node->left_node->right_node != NULL)){
		if (temp_node->left_node->val.at(0) != '-'){
			if (temp_node->left_node->val.length() == 1){
				cout << "ERROR: Evaluation undefined for MINUS (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
			else if (temp_node->left_node->val.at(1) < '0' || temp_node->left_node->val.at(1) > '9'){
				cout << "ERROR: Evaluation undefined for MINUS (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
		}
	}
	linked_list_node* left_parameter;
	linked_list_node* right_parameter;
	left_parameter = temp_node->left_node;
	right_parameter = temp_node->right_node->left_node;
	istringstream istr_l(left_parameter->val);
	istr_l >> result_temp;
	result_minus = result_temp;
	istringstream istr_r(right_parameter->val);
	istr_r >> result_temp;
	result_minus = result_minus - result_temp;
	ostringstream ostr;
	ostr << result_minus;
	(*operation_node)->val = ostr.str();
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_times(linked_list_node** operation_node){
	int result_times = 0;
	int result_temp = 0;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for TIMES (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	if ((temp_node->left_node->val.at(0) > '9' || temp_node->left_node->val.at(0) < '0' || temp_node->left_node->left_node != NULL || temp_node->left_node->right_node != NULL) || (temp_node->right_node->left_node->val.at(0) > '9' || temp_node->right_node->left_node->val.at(0) < '0' || temp_node->right_node->left_node->left_node != NULL || temp_node->right_node->left_node->right_node != NULL)){
		if (temp_node->left_node->val.at(0) != '-'){
			if (temp_node->left_node->val.length() == 1){
				cout << "ERROR: Evaluation undefined for TIMES (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
			else if (temp_node->left_node->val.at(1) < '0' || temp_node->left_node->val.at(1) > '9'){
				cout << "ERROR: Evaluation undefined for TIMES (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
		}
	}
	linked_list_node* left_parameter;
	linked_list_node* right_parameter;
	left_parameter = temp_node->left_node;
	right_parameter = temp_node->right_node->left_node;
	istringstream istr_l(left_parameter->val);
	istr_l >> result_temp;
	result_times = result_temp;
	istringstream istr_r(right_parameter->val);
	istr_r >> result_temp;
	result_times = result_times * result_temp;
	ostringstream ostr;
	ostr << result_times;
	(*operation_node)->val = ostr.str();
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_less(linked_list_node** operation_node){
	int result_less = 0;
	int result_temp = 0;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for LESS (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	if ((temp_node->left_node->val.at(0) > '9' || temp_node->left_node->val.at(0) < '0' || temp_node->left_node->left_node != NULL || temp_node->left_node->right_node != NULL) || (temp_node->right_node->left_node->val.at(0) > '9' || temp_node->right_node->left_node->val.at(0) < '0' || temp_node->right_node->left_node->left_node != NULL || temp_node->right_node->left_node->right_node != NULL)){
		if (temp_node->left_node->val.at(0) != '-'){
			if (temp_node->left_node->val.length() == 1){
				cout << "ERROR: Evaluation undefined for LESS (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
			else if (temp_node->left_node->val.at(1) < '0' || temp_node->left_node->val.at(1) > '9'){
				cout << "ERROR: Evaluation undefined for LESS (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
		}
	}
	linked_list_node* left_parameter;
	linked_list_node* right_parameter;
	left_parameter = temp_node->left_node;
	right_parameter = temp_node->right_node->left_node;
	istringstream istr_l(left_parameter->val);
	istr_l >> result_temp;
	result_less = result_temp;
	istringstream istr_r(right_parameter->val);
	istr_r >> result_temp;
	if (result_less < result_temp){
		(*operation_node)->val = "T";
	}
	else{
		(*operation_node)->val = "NIL";
	}
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_greater(linked_list_node** operation_node){
	int result_greater = 0;
	int result_temp = 0;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for GREATER (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	if ((temp_node->left_node->val.at(0) > '9' || temp_node->left_node->val.at(0) < '0' || temp_node->left_node->left_node != NULL || temp_node->left_node->right_node != NULL) || (temp_node->right_node->left_node->val.at(0) > '9' || temp_node->right_node->left_node->val.at(0) < '0' || temp_node->right_node->left_node->left_node != NULL || temp_node->right_node->left_node->right_node != NULL)){
		if (temp_node->left_node->val.at(0) != '-'){
			if (temp_node->left_node->val.length() == 1){
				cout << "ERROR: Evaluation undefined for GREATER (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
			else if (temp_node->left_node->val.at(1) < '0' || temp_node->left_node->val.at(1) > '9'){
				cout << "ERROR: Evaluation undefined for GREATER (Parameter Type Mismatch) (From Interpreter)" << endl;
				exit(0);
			}
		}
	}
	linked_list_node* left_parameter;
	linked_list_node* right_parameter;
	left_parameter = temp_node->left_node;
	right_parameter = temp_node->right_node->left_node;
	istringstream istr_l(left_parameter->val);
	istr_l >> result_temp;
	result_greater = result_temp;
	istringstream istr_r(right_parameter->val);
	istr_r >> result_temp;
	if (result_greater > result_temp){
		(*operation_node)->val = "T";
	}
	else{
		(*operation_node)->val = "NIL";
	}
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
}

void lisp_cond(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL){
		cout << "ERROR: Evaluation undefined for COND (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* check_temp_node;
	linked_list_node* check_subroot_node;
	check_temp_node = (*operation_node)->right_node;
	while (check_temp_node->val != "NIL" || check_temp_node->left_node != NULL || check_temp_node->right_node != NULL){
		check_subroot_node = check_temp_node->left_node;
		if (check_subroot_node->left_node == NULL || check_subroot_node->right_node == NULL){
			cout << "ERROR: Evaluation undefined for COND (Atom Parameter) (From Interpreter)" << endl;
			exit(0);
		}
		if (check_subroot_node->right_node->left_node == NULL || check_subroot_node->right_node->right_node->val != "NIL" || check_subroot_node->right_node->right_node->left_node != NULL || check_subroot_node->right_node->right_node->right_node != NULL){
			cout << "ERROR: Evaluation undefined for COND (Parameter Number Mismatch in a Parameter) (From Interpreter)" << endl;
			exit(0);
		}
		check_temp_node = check_temp_node->right_node;
	}
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	linked_list_node* cond_bool_condition;
	linked_list_node* cond_bool_condition_backup;
	linked_list_node* cond_expression;
	linked_list_node* cond_expression_backup;
	while(temp_node->left_node != NULL && temp_node->right_node != NULL){
		cond_bool_condition = temp_node->left_node->left_node;
		cond_expression = temp_node->left_node->right_node->left_node;
		cond_bool_condition_backup = cond_bool_condition;
		lisp_operation(cond_bool_condition, &cond_bool_condition);
		cond_bool_condition = cond_bool_condition_backup;
		if (cond_bool_condition->val.compare("NIL") == 0 && cond_bool_condition->left_node == NULL && cond_bool_condition->right_node == NULL){
			temp_node = temp_node->right_node;
			if (temp_node->val == "NIL" && temp_node->left_node == NULL && temp_node->right_node == NULL){
				cout << "ERROR: Evaluation undefined for COND (No Valid Condition) (From Interpreter)" << endl;
				exit(0);
			}
			else{
				continue;
			}
		}
		else {
			cond_expression_backup = cond_expression;
			lisp_operation(cond_expression, &cond_expression);
			cond_expression = cond_expression_backup;
			(*operation_node)->left_node = cond_expression->left_node;
			if (cond_expression->left_node != NULL){
				cond_expression->left_node->parent_node = (*operation_node);
			}
			(*operation_node)->right_node = cond_expression->right_node;
			if (cond_expression->left_node != NULL){
				cond_expression->right_node->parent_node = (*operation_node);
			}
			(*operation_node)->val = cond_expression->val;
			return;
		}
	}
}

void lisp_defun(linked_list_node** operation_node){
	if ((*operation_node)->right_node == NULL || (*operation_node)->right_node->right_node == NULL || (*operation_node)->right_node->right_node->right_node == NULL || (*operation_node)->right_node->right_node->right_node->right_node == NULL || (*operation_node)->right_node->right_node->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node->right_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for DEFUN (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	if ((*operation_node)->right_node->left_node->left_node != NULL || (*operation_node)->right_node->left_node->right_node != NULL){
		cout << "ERROR: Evaluation undefined for DEFUN (Invalid Function Name) (From Interpreter)" << endl;
		exit(0);
	}
	if (((*operation_node)->right_node->left_node->val.at(0) >= '0' && (*operation_node)->right_node->left_node->val.at(0) <= '9') || (*operation_node)->right_node->left_node->val.compare("T") == 0 || (*operation_node)->right_node->left_node->val.compare("NIL") == 0 || (*operation_node)->right_node->left_node->val.compare("CAR") == 0 || (*operation_node)->right_node->left_node->val.compare("CDR") == 0 || (*operation_node)->right_node->left_node->val.compare("CONS") == 0 || (*operation_node)->right_node->left_node->val.compare("ATOM") == 0 || (*operation_node)->right_node->left_node->val.compare("EQ") == 0 || (*operation_node)->right_node->left_node->val.compare("NULL") == 0 || (*operation_node)->right_node->left_node->val.compare("INT") == 0 || (*operation_node)->right_node->left_node->val.compare("PLUS") == 0 || (*operation_node)->right_node->left_node->val.compare("MINUS") == 0 || (*operation_node)->right_node->left_node->val.compare("TIMES") == 0 || (*operation_node)->right_node->left_node->val.compare("LESS") == 0 || (*operation_node)->right_node->left_node->val.compare("GREATER") == 0 || (*operation_node)->right_node->left_node->val.compare("COND") == 0 || (*operation_node)->right_node->left_node->val.compare("QUOTE") == 0 || (*operation_node)->right_node->left_node->val.compare("DEFUN") == 0){
		cout << "ERROR: Evaluation undefined for DEFUN (Numeric Function Name or Function Name In Conflict With T, NIL or BuildIn Functions) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node->right_node->left_node;
	if (temp_node->val.compare("NIL") != 0 && temp_node->left_node == NULL && temp_node->right_node == NULL){
		cout << "ERROR: Evaluation undefined for DEFUN (Atom Formal Parameter List) (From Interpreter)" << endl;
		exit(0);
	}
	while (temp_node->left_node != NULL){
		if (temp_node->left_node->left_node != NULL || temp_node->left_node->right_node != NULL){
			cout << "ERROR: Evaluation undefined for DEFUN (Invalid Formal Parameter Name) (From Interpreter)" << endl;
			exit(0); 
		}
		if ((temp_node->left_node->val.at(0) >= '0' && temp_node->left_node->val.at(0) <= '9') || temp_node->left_node->val.compare("T") == 0 || temp_node->left_node->val.compare("NIL") == 0 || temp_node->left_node->val.compare("CAR") == 0 || temp_node->left_node->val.compare("CDR") == 0 || temp_node->left_node->val.compare("CONS") == 0 || temp_node->left_node->val.compare("ATOM") == 0 || temp_node->left_node->val.compare("EQ") == 0 || temp_node->left_node->val.compare("NULL") == 0 || temp_node->left_node->val.compare("INT") == 0 || temp_node->left_node->val.compare("PLUS") == 0 || temp_node->left_node->val.compare("MINUS") == 0 || temp_node->left_node->val.compare("TIMES") == 0 || temp_node->left_node->val.compare("LESS") == 0 || temp_node->left_node->val.compare("GREATER") == 0 || temp_node->left_node->val.compare("COND") == 0 || temp_node->left_node->val.compare("QUOTE") == 0 || temp_node->left_node->val.compare("DEFUN") == 0){
			cout << "ERROR: Evaluation undefined for DEFUN (Numeric Formal Parameter Name or Formal Parameter Name In Conflict With T, NIL or BuildIn Functions) (From Interpreter)" << endl;
			exit(0);
		}
		temp_node = temp_node->right_node;
	}
	temp_node = (*operation_node)->right_node->right_node->left_node;
	linked_list_node* temp_node_front;
	string cur_val;
	while (temp_node->left_node != NULL){
		cur_val = temp_node->left_node->val;
		temp_node_front = temp_node->right_node;
		while (temp_node_front->left_node != NULL){
			if (temp_node_front->left_node->val.compare(cur_val) == 0){
				cout << "ERROR: Evaluation undefined for DEFUN (Same Formal Parameter Names) (From Interpreter)" << endl;
				exit(0);
			}
			temp_node_front = temp_node_front->right_node;
		}
		temp_node = temp_node->right_node;
	}
	linked_list_node* temp_node_d;
	linked_list_node* root_node_d;
	root_node_d = new linked_list_node;
	temp_node_d = (*operation_node)->right_node;
	root_node_d->left_node = temp_node_d;
	temp_node_d->parent_node = root_node_d;
	if (d_list == NULL){
		linked_list_node* new_defun_node_d;
		new_defun_node_d = new linked_list_node;
		new_defun_node_d->val = "NIL";
		d_list = new_defun_node_d;
	}
	root_node_d->right_node = d_list;
	d_list->parent_node = root_node_d;
	d_list = root_node_d;
	(*operation_node)->left_node = NULL;
	(*operation_node)->right_node = NULL;
	(*operation_node)->val = temp_node_d->left_node->val;
}

void lisp_apply(linked_list_node* function_address, linked_list_node** operation_node){
	int formal_num = 0;
	int para_num = 0;
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	int flag_root_val = 1;
	while (temp_node->left_node != NULL){
		para_num = para_num + 1;
		temp_node = temp_node->right_node;
	}
	linked_list_node* temp_node_func;
	temp_node_func = function_address->right_node->left_node;
	while (temp_node_func->left_node != NULL){
		formal_num = formal_num + 1;
		temp_node_func = temp_node_func->right_node;
	}
	if (para_num != formal_num){
		cout << "ERROR: Illegal use of user defined function \"" << function_address->left_node->val << "\" (Parameter Number Mismatch) (From Interpreter)" << endl;
		exit(0);
	}
	linked_list_node* temp_node_para;
	temp_node_para = (*operation_node)->right_node;
	linked_list_node* temp_node_para_left_backup;
	while(temp_node_para->left_node != NULL){
		temp_node_para_left_backup = temp_node_para->left_node;
		lisp_operation(temp_node_para->left_node, &(temp_node_para->left_node));
		temp_node_para->left_node = temp_node_para_left_backup;
		temp_node_para = temp_node_para->right_node;
	}
	temp_node_para = (*operation_node)->right_node;
	linked_list_node* temp_node_formal;
	linked_list_node* root_node_a;
	root_node_a = new linked_list_node;
	temp_node_formal = function_address->right_node->left_node;
	if (a_list == NULL){
		linked_list_node* new_apply_node_a;
		new_apply_node_a = new linked_list_node;
		new_apply_node_a->val = "NIL";
		a_list = new_apply_node_a;
	}
	while(temp_node_formal->left_node != NULL){
		root_node_a = new linked_list_node;
		linked_list_node* pair_root;
		pair_root = new linked_list_node;
		linked_list_node* pair_var_name;
		pair_var_name = new linked_list_node;
		linked_list_node* pair_val;
		pair_val = new linked_list_node;
		a_list->parent_node = root_node_a;
		root_node_a->right_node = a_list;
		pair_root->parent_node = root_node_a;
		root_node_a->left_node = pair_root;
		pair_var_name->parent_node = pair_root;
		pair_root->left_node = pair_var_name;
		pair_val->parent_node = pair_root;
		pair_root->right_node = pair_val;
		pair_var_name->val = temp_node_formal->left_node->val;
		flag_root_val = 1;
		lisp_deep_copy(temp_node_para->left_node, pair_val, 0, &flag_root_val);
		temp_node_formal = temp_node_formal->right_node;
		temp_node_para = temp_node_para->right_node;
		a_list = root_node_a;
	}
	flag_root_val = 1;
	lisp_deep_copy(function_address->right_node->right_node->left_node, (*operation_node), 0, &flag_root_val);
	linked_list_node** operation_node_backup = operation_node;
	lisp_operation((*operation_node), operation_node);
	operation_node = operation_node_backup;
	linked_list_node* a_list_delete;
	a_list_delete = a_list;
	for (int i = 0; i < formal_num; i++){
		a_list_delete = a_list_delete->right_node;
	}
	a_list_delete->parent_node = NULL;
	a_list = a_list_delete;
}

void lisp_deep_copy(linked_list_node* original_node, linked_list_node* target_node, int flag_left_right, int* flag_root){
	linked_list_node* temp_node;
	temp_node = original_node;
	linked_list_node* temp_node_target;
	temp_node_target = target_node;
	if ((*flag_root) == 1){
		if (temp_node->left_node != NULL && temp_node->right_node != NULL){
			linked_list_node* new_node;
			new_node = new linked_list_node;
			new_node->val = temp_node->val;
			temp_node_target->val = new_node->val;
			temp_node_target->left_node = new_node->left_node;
			temp_node_target->right_node = new_node->right_node;
			(*flag_root) = 0;
			lisp_deep_copy(temp_node->left_node, temp_node_target, 0, flag_root);
			lisp_deep_copy(temp_node->right_node, temp_node_target, 1, flag_root);
		}
		else{
			linked_list_node* new_node;
			new_node = new linked_list_node;
			new_node->val = temp_node->val;
			temp_node_target->val = new_node->val;
			temp_node_target->left_node = new_node->left_node;
			temp_node_target->right_node = new_node->right_node;
		}
	}
	else if ((*flag_root) == 0){ // In this case, temp_node_target is viewed as the parent node.
		if (temp_node->left_node != NULL && temp_node->right_node != NULL){
			linked_list_node* new_node;
			new_node = new linked_list_node;
			new_node->val = temp_node->val;
			new_node->parent_node = temp_node_target;
			if (flag_left_right == 0){
				temp_node_target->left_node = new_node;
			}
			else if (flag_left_right == 1){
				temp_node_target->right_node = new_node;
			}
			lisp_deep_copy(temp_node->left_node, new_node, 0, flag_root);
			lisp_deep_copy(temp_node->right_node, new_node, 1, flag_root);
		}
		else{
			linked_list_node* new_node;
			new_node = new linked_list_node;
			new_node->val = temp_node->val;
			new_node->parent_node = temp_node_target;
			if (flag_left_right == 0){
				temp_node_target->left_node = new_node;
			}
			else if (flag_left_right == 1){
				temp_node_target->right_node = new_node;
			}
		}
	}
}

linked_list_node* lisp_a_list_search(string variable_name){
	linked_list_node* result_node = NULL;
	linked_list_node* temp_node;
	temp_node = a_list;
	if (a_list == NULL){
		return result_node;
	}
	while (temp_node->left_node != NULL){
		if (temp_node->left_node->left_node->val.compare(variable_name) == 0){
			result_node = temp_node->left_node->right_node;
			break;
		}
		temp_node = temp_node->right_node;
	}
	return result_node;
}

linked_list_node* lisp_d_list_search(string function_name){
	linked_list_node* result_node = NULL;
	linked_list_node* temp_node;
	temp_node = d_list;
	if (temp_node == NULL){
		return result_node;
	}
	while(temp_node->left_node != NULL){
		if (temp_node->left_node->left_node->val.compare(function_name) == 0){
			result_node = temp_node->left_node;
			break;
		}
		temp_node = temp_node->right_node;
	}
	return result_node;
}
