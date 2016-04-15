#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "TypeChecker.h"
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

void type_checking_error_print (string error_type){
	if (error_type.at(0) == '0'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined (Invalid Function Name (F, T, NIL or Integers)) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined (Invalid Function or Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '1'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CONS (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CONS (Non-Numeric First Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '2'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CONS (Non-List Second Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '2'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CAR (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CAR (Non-List Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '2'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CAR (Empty List) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '3'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CDR (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CDR (Non-List Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '2'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for CDR (Empty List) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '4'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for ATOM (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for ATOM (Non-Nat, Non-Bool and Non-List Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '5'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for INT (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for INT (Non-Nat, Non-Bool and Non-List Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '6'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for NULL (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for NULL (Non-List Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '7'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for EQ (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for EQ (Non-Nat First Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '2'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for EQ (Non-Nat Second Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '8'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for PLUS (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for PLUS (Non-Nat First Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '2'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for PLUS (Non-Nat Second Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == '9'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for LESS (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for LESS (Non-Nat First Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '2'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for LESS (Non-Nat Second Parameter) (From TypeChecker)" << endl;
		}
	}
	else if (error_type.at(0) == 'x'){
		if (error_type.at(1) == '0'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for COND (Parameter Number Mismatch) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '1'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for COND (Atom Parameter in a Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '2'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for COND (Parameter Number Mismatch in a Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '3'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for COND (Non-Bool First Parameter in a Parameter) (From TypeChecker)" << endl;
		}
		else if (error_type.at(1) == '4'){
			cout << "ERROR: [FIRST ERROR] Typechecking undefined for COND (Inconsistent Expression Types among Parameters) (From TypeChecker)" << endl;
		}
	}
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
			if (cur_node->val != "NIL" && cur_node->val != "F" && cur_node->val != "T" && (cur_node->val.at(0) > '9' || cur_node->val.at(0) < '0')){
				cout << "ERROR: [FIRST ERROR] Typechecking undefined (Invalid Input) (From TypeChecker)" << endl;
			}
			else{
				cout << (*cur_node).val << endl;
			}
		}
		else{
			flag_typechecking = "0";
			flag_typechecking_switch = 0;
			lisp_operation(root_node, &cur_node); // 1 means reverse search can be continued after the lisp_operation, 0 means reverse search should be terminated after the lisp_operation
			while (cur_node->right_node != NULL){
				cur_node = cur_node->right_node;
			}
			tail_node = cur_node;
			cur_node = root_node;
			if (flag_typechecking.compare("0") != 0){
				type_checking_error_print(flag_typechecking);
			}
			else{
				if (((*cur_node).left_node == NULL) && ((*cur_node).right_node == NULL)){
					cout << cur_node->val << endl;
				}
				else{
					lisp_list_notation_print(root_node, cur_node, tail_node, &flag_indent);			
				}
			}
		}
		my_scanner.GetCurrent(&token_type, &returning_string);
	} while (token_type != 5);
	return 0;
}
