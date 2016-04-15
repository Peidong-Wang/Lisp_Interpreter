#include <iostream>
#include <stdlib.h>
#include "BuildInFunc.cc"
#include "Scanner.cc"
using namespace std;

//token types: 1 denotes OpenParenthesis, 2 denotes ClosingParenthesis, 3 denotes numeric atom, 4 denotes literal atom, 5 denotes EOF, 6 denotes ERROR

void Expr(Scanner * my_scanner, int * token_type, string * returning_string, int * parenthesis_pairing, int * inner_parenthesis_pairing, string * input_string, int * input_index, linked_list_node** cur_node){
	int num_atom = 0;
	int pairing_check = 1;
	int input_index_backup = 0;
	linked_list_node* ancestor_node;
	(* my_scanner).GetCurrent(token_type, returning_string);
	if (* token_type == 3 || * token_type == 4){
		if (* parenthesis_pairing == 0){
			(*(*cur_node)).val = *returning_string;
		}
		else if (* parenthesis_pairing > 0){
			linked_list_node* new_left_node;
			new_left_node = new linked_list_node;
			(*cur_node)->left_node = new_left_node;
			new_left_node->parent_node = (*cur_node);
			new_left_node->val = *returning_string;
			if ((*token_type) == 3){
				(*cur_node)->type = "NAT";
			}
			else if ((*token_type) == 4 && (((*returning_string).compare("T") == 0) || (*returning_string).compare("F") == 0)){
				(*cur_node)->type = "BOOL";
			}
			else if ((*token_type) == 4 && (*returning_string).compare("NIL") == 0){
				(*cur_node)->type = "LIST";
				(*cur_node)->var_num = 0;
			}
			linked_list_node* new_right_node;
			new_right_node = new linked_list_node;
			(*cur_node)->right_node = new_right_node;
			new_right_node->parent_node = (*cur_node);
			(*cur_node) = (*cur_node)->right_node;
		}
		(* my_scanner).MoveToNext(input_string, input_index);
		return;
	}
	else if (* token_type == 1){
		if (* parenthesis_pairing == 0){
			input_index_backup = * input_index;
			pairing_check = 1;
			while(* token_type != 5){
				(* my_scanner).MoveToNextMute(input_string, input_index);
				(* my_scanner).GetCurrent(token_type, returning_string);
				if (* token_type == 2){
					pairing_check = pairing_check - 1;
				}
				else if (* token_type == 1){
					pairing_check = pairing_check + 1;
				}
				if (pairing_check == 0){
					break;
				}
			}
			if (pairing_check > 0){
				cout << "ERROR: Non-pairing OpenParenthesis(es) (From Parser)" << endl;
				exit(0);
			}
			* input_index = input_index_backup;
			pairing_check = 1;
			do {
				(* my_scanner).MoveToNext(input_string, input_index);
				(* my_scanner).GetCurrent(token_type, returning_string);
				if (* token_type == 2){
					pairing_check = pairing_check - 1;
				}
				else if (* token_type == 1){
					pairing_check = pairing_check + 1;
				}
				if (pairing_check == 0){
					break;
				}
			} while (* token_type != 5);
			* input_index = input_index_backup;
		}
		* parenthesis_pairing = * parenthesis_pairing + 1;
		* inner_parenthesis_pairing = * inner_parenthesis_pairing + 1;
		if(* parenthesis_pairing > 1){
			linked_list_node* subroot_node;
			subroot_node = new linked_list_node;
			ancestor_node = (*cur_node);
			(*cur_node)->left_node = subroot_node;
			subroot_node->parent_node = (*cur_node);
			(*cur_node) = subroot_node;
		}
		(* my_scanner).MoveToNext(input_string, input_index);
		(* my_scanner).GetCurrent(token_type, returning_string);
		while(* token_type != 2 && * token_type != 5 && * token_type != 6){
			Expr(my_scanner, token_type, returning_string, parenthesis_pairing, inner_parenthesis_pairing, input_string, input_index, cur_node);
			num_atom ++;
			(* my_scanner).GetCurrent(token_type, returning_string);
		}
		if (* inner_parenthesis_pairing > 1){
			linked_list_node* new_right_node;
			new_right_node = new linked_list_node;
			(*cur_node)->val = "NIL";
			if (((*cur_node)->parent_node->left_node) == (*cur_node)){
				(*cur_node)->parent_node->type = "LIST";
				(*cur_node)->parent_node->var_num = 0;
			}
			(*cur_node) = ancestor_node;
			(*cur_node)->right_node = new_right_node;
			new_right_node->parent_node = (*cur_node);
			(*cur_node) = (*cur_node)->right_node;
		}
		else if (* inner_parenthesis_pairing == 1){
			(*cur_node)->val = "NIL";
		}
		if (* token_type == 2){
			* parenthesis_pairing = * parenthesis_pairing - 1;
		}
		* inner_parenthesis_pairing = * inner_parenthesis_pairing - 1;
		(* my_scanner).MoveToNext(input_string, input_index);
		return;
	}
	else if (* token_type == 2){
		cout << "ERROR: Non-pairing ClosingParenthesis(es) (From Parser)" << endl;
		exit (0);
	}
	else if (* token_type == 5){
		return;
	}
	else if (* token_type == 6){
		return;
	}
	else {
		cout << "ERROR: Unknown parsing error (From Parser)" << endl;
		return;
	}
}
