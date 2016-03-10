#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//token types: 1 denotes OpenParenthesis, 2 denotes ClosingParenthesis, 3 denotes numeric atom, 4 denotes literal atom, 5 denotes EOF, 6 denotes ERROR

void getNextToken(int * token_type, string * returning_string, string * input_string, int * input_index, bool token_mute){
	char cur_character = '\0';
	string temp_string = "";
	while (1){
		* input_index = * input_index + 1;
		if ((unsigned int)(* input_index) == (* input_string).length()){
			* token_type = 5;
			* returning_string = "";
			return;
		}
		cur_character = (* input_string).at(* input_index);
		if (cur_character != ' ' && cur_character != '\r' && cur_character != '\n') {
			break;
		}
	}
	if (cur_character == '('){
		* token_type = 1;
		* returning_string = "";
		return;
	}
	else if (cur_character == ')'){
		* token_type = 2;
		* returning_string = "";
		return;
	}
	else if ((cur_character >= '0') && (cur_character <= '9')){
		* token_type = 3;
		while ((cur_character != ' ') && (cur_character != '\r') && (cur_character != '\n') && (cur_character != '(') && (cur_character != ')')) {
			if ((cur_character >= '0') && (cur_character <= '9')) {
				temp_string = temp_string + cur_character;
			}
			else {
				* token_type = 6;
				temp_string = temp_string + cur_character;
			}
			* input_index = * input_index + 1;
			if ((unsigned int)(* input_index) == (*input_string).length()){
				break;
			}
			cur_character = (* input_string).at(* input_index);
		}
		* input_index = * input_index - 1;
		* returning_string = temp_string;
		if (* token_type == 6 && token_mute == false){
			cout << "ERROR: Invalid token " << * returning_string << endl;
			exit (0);
		}
		return;
	}
	else {
		* token_type = 4;
		while ((cur_character != ' ') && (cur_character != '\r') && (cur_character != '\n') && (cur_character != '(') && (cur_character != ')')) {
			temp_string = temp_string + cur_character;
			* input_index = * input_index + 1;
			if ((unsigned int)(* input_index) == (*input_string).length()){
				break;
			} 
			cur_character = (* input_string).at(* input_index);
		}
		* input_index = * input_index - 1;
		* returning_string = temp_string;
		return;
	}
}