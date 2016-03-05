#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "LispInterpreter.h"
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

void lisp_operation(linked_list_node* root_node, linked_list_node** cur_node){
	while ((*cur_node)->left_node != NULL){
		if ((*cur_node)->left_node->val.compare("QUOTE") == 0){
			lisp_build_in_func("QUOTE", cur_node);
			break;
		}
		else if ((*cur_node)->left_node->val.compare("COND") == 0){
			lisp_build_in_func("COND", cur_node);
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
			lisp_build_in_func((*cur_node)->left_node->val, cur_node);
		}
		else if ((*cur_node) == root_node && (((*cur_node)->left_node->val.at(0) <= '9' && (*cur_node)->left_node->val.at(0) >= '0') || (*cur_node)->left_node->val == "NIL" || (*cur_node)->left_node->val == "T" || ((*cur_node)->left_node->val.at(0) == '-' && (*cur_node)->left_node->val.length() > 1 && (*cur_node)->left_node->val.at(1) >= '0' && (*cur_node)->left_node->val.at(1) <= '9'))){
			cout << "ERROR: Invalid function name (NIL, T or Integers) (From Interpreter)" << endl;
			exit(0);
		}
	}
}

void lisp_build_in_func(string function_name, linked_list_node** operation_node){
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
	else {
		cout << "ERROR: Invalid function or parameter (From Interpreter)" << endl;
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
	linked_list_node* cond_expression;
	while(temp_node->left_node != NULL && temp_node->right_node != NULL){
		cond_bool_condition = temp_node->left_node->left_node;
		cond_expression = temp_node->left_node->right_node->left_node;
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
			lisp_operation(cond_expression, &cond_expression);
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
