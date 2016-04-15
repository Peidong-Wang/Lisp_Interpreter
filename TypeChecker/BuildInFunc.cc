#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "TypeChecker.h"
using namespace std;


struct linked_list_node{
	string val;
	linked_list_node* left_node;
	linked_list_node* right_node;
	linked_list_node* parent_node;
	string color;
	string type;
	int var_num;
	linked_list_node(){
		val = "";
		left_node = NULL;
		right_node = NULL;
		parent_node = NULL;
		color = "WHITE";
		type = "";
		var_num = 0;
	}
};

void lisp_operation(linked_list_node* root_node, linked_list_node** cur_node){
	while ((*cur_node)->left_node != NULL){
		if ((*cur_node)->left_node->val.compare("COND") == 0){
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
		else if (((*cur_node)->left_node->val.at(0) > '9' || (*cur_node)->left_node->val.at(0) < '0') && (*cur_node)->left_node->val != "NIL" && (*cur_node)->left_node->val != "F" && (*cur_node)->left_node->val != "T" && !((*cur_node)->left_node->val.at(0) == '-' && (*cur_node)->left_node->val.length() > 1 && (*cur_node)->left_node->val.at(1) >= '0' && (*cur_node)->left_node->val.at(1) <= '9')){
			lisp_build_in_func((*cur_node)->left_node->val, cur_node);
		}
		else if ((*cur_node) == root_node && (((*cur_node)->left_node->val.at(0) <= '9' && (*cur_node)->left_node->val.at(0) >= '0') || (*cur_node)->left_node->val == "F" || (*cur_node)->left_node->val == "NIL" || (*cur_node)->left_node->val == "T" || ((*cur_node)->left_node->val.at(0) == '-' && (*cur_node)->left_node->val.length() > 1 && (*cur_node)->left_node->val.at(1) >= '0' && (*cur_node)->left_node->val.at(1) <= '9'))){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "00";
				flag_typechecking_switch = 1;
			}
		}
	}
}

void lisp_build_in_func(string function_name, linked_list_node** operation_node){
	if (function_name.compare("CONS") == 0){
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
	else if (function_name.compare("LESS") == 0){
		lisp_less(operation_node);
	}
	else if (function_name.compare("COND") == 0){
		lisp_cond(operation_node);
	}
	else {
		if (flag_typechecking_switch == 0){
			flag_typechecking = "01";
			flag_typechecking_switch = 1;
		}
	}
}

void lisp_cons(linked_list_node** operation_node){
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	int second_parameter_var_num;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "10";
			flag_typechecking_switch = 1;
		}
	}
	else {
		if (temp_node->type.compare("NAT") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "11";
				flag_typechecking_switch = 1;
			}
		}
		else if (temp_node->right_node->type.compare("LIST") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "12";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "LIST";
				second_parameter_var_num = temp_node->right_node->var_num;
				(*operation_node)->parent_node->var_num = second_parameter_var_num + 1;
			}
		}
	}
}

void lisp_car(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "20";
			flag_typechecking_switch = 1;
		}
	}
	else {
		linked_list_node* temp_node;
		temp_node = (*operation_node)->right_node;
		if (temp_node->type.compare("LIST") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "21";
				flag_typechecking_switch = 1;
			}
		}
		else if (temp_node->var_num <= 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "22";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "NAT";
			}
		}
	}
}

void lisp_cdr(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "30";
			flag_typechecking_switch = 1;
		}
	}
	else {
		linked_list_node* temp_node;
		temp_node = (*operation_node)->right_node;
		if (temp_node->type.compare("LIST") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "31";
				flag_typechecking_switch = 1;
			}
		}
		else if (temp_node->var_num <= 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "32";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "LIST";
				(*operation_node)->parent_node->var_num = temp_node->var_num - 1;
			}
		}
	}
}

void lisp_atom(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "40";
			flag_typechecking_switch = 1;
		}
	}
	else {
		linked_list_node* temp_node;
		temp_node = (*operation_node)->right_node;
		if (temp_node->type.compare("NAT") != 0 && temp_node->type.compare("BOOL") != 0 && temp_node->type.compare("LIST") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "41";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "BOOL";
			}
		}
	}
}

void lisp_int(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "50";
			flag_typechecking_switch = 1;
		}
	}
	else {
		linked_list_node* temp_node;
		temp_node = (*operation_node)->right_node;
		if (temp_node->type.compare("NAT") != 0 && temp_node->type.compare("BOOL") != 0 && temp_node->type.compare("LIST") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "51";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "BOOL";
			}
		}
	}
}

void lisp_null(linked_list_node** operation_node){
	if ((*operation_node)->right_node->left_node == NULL || (*operation_node)->right_node->right_node->val != "NIL" || (*operation_node)->right_node->right_node->left_node != NULL || (*operation_node)->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "60";
			flag_typechecking_switch = 1;
		}
	}
	else {
		linked_list_node* temp_node;
		temp_node = (*operation_node)->right_node;
		if (temp_node->type.compare("LIST") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "61";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "BOOL";
			}
		}
	}
}

void lisp_eq(linked_list_node** operation_node){
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "70";
			flag_typechecking_switch = 1;
		}
	}
	else {
		if (temp_node->type.compare("NAT") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "71";
				flag_typechecking_switch = 1;
			}
		}
		else if (temp_node->right_node->type.compare("NAT") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "72";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "BOOL";
			}
		}
	}
}

void lisp_plus(linked_list_node** operation_node){
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "80";
			flag_typechecking_switch = 1;
		}
	}
	else {
		if (temp_node->type.compare("NAT") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "81";
				flag_typechecking_switch = 1;
			}
		}
		else if (temp_node->right_node->type.compare("NAT") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "82";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "NAT";
			}
		}
	}
}

void lisp_less(linked_list_node** operation_node){
	linked_list_node* temp_node;
	temp_node = (*operation_node)->right_node;
	if (temp_node->left_node == NULL || temp_node->right_node->left_node == NULL || temp_node->right_node->right_node->val != "NIL" || temp_node->right_node->right_node->left_node != NULL || temp_node->right_node->right_node->right_node != NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "90";
			flag_typechecking_switch = 1;
		}
	}
	else {
		if (temp_node->type.compare("NAT") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "91";
				flag_typechecking_switch = 1;
			}
		}
		else if (temp_node->right_node->type.compare("NAT") != 0){
			if (flag_typechecking_switch == 0){
				flag_typechecking = "92";
				flag_typechecking_switch = 1;
			}
		}
		else {
			if ((*operation_node)->parent_node != NULL){
				(*operation_node)->parent_node->type = "BOOL";
			}
		}
	}
}

void lisp_cond(linked_list_node** operation_node){
	string expression_type;
	int expression_var_num;
	if ((*operation_node)->right_node->left_node == NULL){
		if (flag_typechecking_switch == 0){
			flag_typechecking = "x0";
			flag_typechecking_switch = 1;
		}
	}
	else{
		linked_list_node* check_temp_node;
		linked_list_node* check_subroot_node;
		check_temp_node = (*operation_node)->right_node;
		linked_list_node* cond_bool_condition;
		linked_list_node* cond_expression;
		if (check_temp_node->val != "NIL" || check_temp_node->left_node != NULL || check_temp_node->right_node != NULL){
			check_subroot_node = check_temp_node->left_node;
			if (check_subroot_node->left_node == NULL || check_subroot_node->right_node == NULL){
				if (flag_typechecking_switch == 0){
					flag_typechecking = "x1";
					flag_typechecking_switch = 1;
				}
			}
			else if (check_subroot_node->right_node->left_node == NULL || check_subroot_node->right_node->right_node->val != "NIL" || check_subroot_node->right_node->right_node->left_node != NULL || check_subroot_node->right_node->right_node->right_node != NULL){
				if (flag_typechecking_switch == 0){
					flag_typechecking = "x2";
					flag_typechecking_switch = 1;
				}
			}
			else {
				cond_expression = check_temp_node->left_node->right_node;
				lisp_operation(cond_expression->left_node, &cond_expression->left_node);
				expression_type = check_temp_node->left_node->right_node->type;
				if (expression_type.compare("LIST") == 0){
					expression_var_num = check_temp_node->left_node->right_node->var_num;
				}
			}
		}
		while (check_temp_node->val != "NIL" || check_temp_node->left_node != NULL || check_temp_node->right_node != NULL){
			check_subroot_node = check_temp_node->left_node;
			if (check_subroot_node->left_node == NULL || check_subroot_node->right_node == NULL){
				if (flag_typechecking_switch == 0){
					flag_typechecking = "x1";
					flag_typechecking_switch = 1;
				}
			}
			else if (check_subroot_node->right_node->left_node == NULL || check_subroot_node->right_node->right_node->val != "NIL" || check_subroot_node->right_node->right_node->left_node != NULL || check_subroot_node->right_node->right_node->right_node != NULL){
				if (flag_typechecking_switch == 0){
					flag_typechecking = "x2";
					flag_typechecking_switch = 1;
				}
			}
			else {
				cond_bool_condition = check_temp_node->left_node;
				cond_expression = check_temp_node->left_node->right_node;
				lisp_operation(cond_bool_condition->left_node, &cond_bool_condition->left_node);
				lisp_operation(cond_expression->left_node, &cond_expression->left_node);
				if (cond_bool_condition->type.compare("BOOL") != 0){
					if (flag_typechecking_switch == 0){
						flag_typechecking = "x3";
						flag_typechecking_switch = 1;
					}
				}
				else if (cond_expression->type.compare(expression_type) != 0){
					if (flag_typechecking_switch == 0){
						flag_typechecking = "x4";
						flag_typechecking_switch = 1;
					}
				}
				else {
					if (expression_type.compare("LIST") == 0){
						if (cond_expression->var_num < expression_var_num){
							expression_var_num = cond_expression->var_num;
						}
					}
				}
			}
			check_temp_node = check_temp_node->right_node;
		}
	}
	if (flag_typechecking_switch == 0 || (flag_typechecking_switch == 1 && flag_typechecking.at(0) != 'x')){
		if ((*operation_node)->parent_node != NULL){
			(*operation_node)->parent_node->type = expression_type;
			(*operation_node)->parent_node->var_num = expression_var_num;
		}
	}
}
