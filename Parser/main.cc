#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "Scanner.cc"
using namespace std;

//token types: 1 denotes OpenParenthesis, 2 denotes ClosingParenthesis, 3 denotes numeric atom, 4 denotes literal atom, 5 denotes EOF, 6 denotes ERROR

void Expr(Scanner * my_scanner, int * token_type, string * returning_string, int * parenthesis_pairing, int * inner_parenthesis_pairing, string * input_string, int * input_index){ // Flag is used to distinguish atom from list, 0 means atom, 1 means list
	int num_atom = 0;
	int pairing_check = 1;
	int input_index_backup = 0;
	(* my_scanner).GetCurrent(token_type, returning_string);
	if (* token_type == 3 || * token_type == 4){
		if (* parenthesis_pairing == 0){
			cout << * returning_string << endl;
		}
		else if (* parenthesis_pairing > 0){
			cout << "(" << * returning_string << " . ";
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
		if (* parenthesis_pairing > 1){
			cout << "(";
		}
		(* my_scanner).MoveToNext(input_string, input_index);
		(* my_scanner).GetCurrent(token_type, returning_string);
		while(* token_type != 2 && * token_type != 5 && * token_type != 6){
			Expr(my_scanner, token_type, returning_string, parenthesis_pairing, inner_parenthesis_pairing, input_string, input_index);
			num_atom ++;
			(* my_scanner).GetCurrent(token_type, returning_string);
		}
		cout << "NIL";
		for (int i = 0; i < num_atom; i++){
			cout << ")";
		}
		if (* inner_parenthesis_pairing > 1){
			cout << " . ";
		}
		else if (* inner_parenthesis_pairing == 1){
			cout << endl;
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
	my_scanner.Init(&input_string, &input_index);
	my_scanner.GetCurrent(&token_type, &returning_string);
	if (token_type == 5){
		cout << "ERROR: Empty input (From Parser)" << endl;
		exit(0);
	}
	do {
		Expr(&my_scanner, &token_type, &returning_string, &parenthesis_pairing, &inner_parenthesis_pairing, &input_string, &input_index);
		my_scanner.GetCurrent(&token_type, &returning_string);
	} while (token_type != 5);
	return 0;
}