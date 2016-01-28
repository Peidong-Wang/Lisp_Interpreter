#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

//token types: 1 denotes OpenParenthesis, 2 denotes ClosingParenthesis, 3 denotes numeric atom, 4 denotes literal atom, 5 denotes EOF, 6 denotes ERROR

void getNextToken(int * token_type, string * returning_string){
	char cur_character = '\0';
	string temp_string = "";
	while (1){
		cur_character = cin.get();
		if (cur_character == EOF){
			* token_type = 5;
			* returning_string = "";
			return;
		}
		else if (cur_character != ' ' && cur_character != '\r' && cur_character != '\n') {
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
		while ((cur_character != ' ') && (cur_character != '\r') && (cur_character != '\n') && (cur_character != EOF) && (cur_character != '(') && (cur_character != ')')) {
			if ((cur_character >= '0') && (cur_character <= '9')) {
				temp_string = temp_string + cur_character;
			}
			else {
				* token_type = 6;
				temp_string = temp_string + cur_character;
			}
			cur_character = cin.get();
		}
		cin.putback(cur_character);
		* returning_string = temp_string;
		return;
	}
	else {
		* token_type = 4;
		while ((cur_character != ' ') && (cur_character != '\r') && (cur_character != '\n') && (cur_character != EOF) && (cur_character != '(') && (cur_character != ')')) {
			temp_string = temp_string + cur_character;
			cur_character = cin.get();
		}
		cin.putback(cur_character);
		* returning_string = temp_string;
		return;
	}
}