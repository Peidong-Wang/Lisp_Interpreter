#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "LispInterpreter.h"
#include "Parser.cc"
using namespace std;

void lisp_list_notation_print(linked_list_node* root_node, linked_list_node* cur_node, linked_list_node* tail_node, int* flag_indent){//linked_list_node* origin_node, linked_list_node* con_tail_node, linked_list_node* root_node, linked_list_node* cur_node, linked_list_node* tail_node){
	cur_node->color = "GRAY";
	if (cur_node == root_node){
		cout << "(";
		*flag_indent = 0;
	}
	if (cur_node->left_node == NULL){
		if (cur_node->parent_node->right_node == cur_node) {
			if (cur_node->val == "NIL"){
				if (cur_node == tail_node){
					cout << ")" << endl;
				}
				else {
					cout << ")";
					*flag_indent = 1;
				}
			}
			else{
				if (cur_node == tail_node){
					cout << " . " << cur_node->val << ")" << endl;
				}
				else{
					cout << " . " << cur_node->val << ")";
					*flag_indent = 1;
				}
			}
		}
		else{
			if (*flag_indent == 0){
				cout << cur_node->val;
				*flag_indent = 1;
			}
			else if (*flag_indent == 1){
				cout << " " << cur_node->val;
				*flag_indent = 1;
			}
		}
	}
	else if (cur_node->left_node->left_node != NULL){
		if (*flag_indent == 0){
			cout << "(";
		}
		else if(*flag_indent == 1){
			cout << " (";
		}
		*flag_indent = 0;
	}
	if (cur_node->left_node != NULL && cur_node->left_node->color == "WHITE"){
		cur_node = cur_node->left_node;
		lisp_list_notation_print(root_node, cur_node, tail_node, flag_indent);
		cur_node = cur_node->parent_node;
	}
	if (cur_node->right_node != NULL && cur_node->right_node->color == "WHITE"){
		cur_node = cur_node->right_node;
		lisp_list_notation_print(root_node, cur_node, tail_node, flag_indent);
	}
	cur_node->color = "BLACK";
}

int main(){
	int token_type = 0;
	stringstream input_string_stream;
	string input_string;
	input_string_stream << cin.rdbuf();
	input_string = input_string_stream.str();
	int input_index = - 1;
	string returning_string;
	Scanner my_scanner;
	int parenthesis_pairing = 0; // parenthesis_pairing means the "layer" the Parser is at. If parenthesis_pairing is greater than 0, it means the number of open parenthesis is larger than the number of closing parenthesis, vice versa.
	int inner_parenthesis_pairing = 0; // inner_parenthesis_pairing is used to make sure that the parentheses in output is complete.
	int flag_indent = 0;
	my_scanner.Init(&input_string, &input_index);
	my_scanner.GetCurrent(&token_type, &returning_string);
	if (token_type == 5){
		cout << "ERROR: Empty input (From Parser)" << endl;
		exit(0);
	}
	do {
		linked_list_node* root_node;
		root_node = new linked_list_node;
		linked_list_node* cur_node;
		cur_node = root_node;
		linked_list_node* tail_node;
		Expr(&my_scanner, &token_type, &returning_string, &parenthesis_pairing, &inner_parenthesis_pairing, &input_string, &input_index, &cur_node);
		tail_node = cur_node;
		cur_node = root_node;
		if (((*cur_node).left_node == NULL) && ((*cur_node).right_node == NULL)){
			if (cur_node->val != "NIL" && cur_node->val != "T" && (cur_node->val.at(0) > '9' || cur_node->val.at(0) < '0')){
				cout << "ERROR: Invalid input (From Interpreter)" << endl;
				exit(0);
			}
			else{
				cout << (*cur_node).val << endl;
			}
		}
		else{
			lisp_operation(root_node, &cur_node); // 1 means reverse search can be continued after the lisp_operation, 0 means reverse search should be terminated after the lisp_operation
			while (cur_node->right_node != NULL){
				cur_node = cur_node->right_node;
			}
			tail_node = cur_node;
			cur_node = root_node;
			if (((*cur_node).left_node == NULL) && ((*cur_node).right_node == NULL)){
				cout << cur_node->val << endl;
			}
			else{
				lisp_list_notation_print(root_node, cur_node, tail_node, &flag_indent);			
			}
		}
		my_scanner.GetCurrent(&token_type, &returning_string);
	} while (token_type != 5);
	return 0;
}
