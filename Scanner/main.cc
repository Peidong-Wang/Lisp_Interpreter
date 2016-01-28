#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "getNextToken.cc"
using namespace std;

int main(){
	int i = 0;
	int num_numeric_atoms = 0;
	int num_literal_atoms = 0;
	int num_openparenthesis = 0;
	int num_closingparenthesis = 0;
	int token_type = 0; // 1 denotes OpenParenthesis, 2 denotes ClosingParenthesis, 3 denotes numeric atom, 4 denotes literal atom, 5 denotes EOF, 6 denotes ERROR
	string returning_string = "";
	vector<string> str_literal_atoms;
	vector<string> str_numeric_atoms;
	int sum_numeric_atoms = 0;
	int temp_numeric_atoms = 0;
	while (1){
		getNextToken(&token_type, &returning_string);
		if (token_type == 6){
			cout << "ERROR: Invalid token " << returning_string << endl;
			return 0;
		}
		else if (token_type == 1){
			num_openparenthesis = num_openparenthesis + 1;
		}
		else if (token_type == 2){
			num_closingparenthesis = num_closingparenthesis + 1;
		}
		else if (token_type == 3){
			num_numeric_atoms = num_numeric_atoms + 1;
			str_numeric_atoms.push_back(returning_string);
		}
		else if (token_type == 4){
			num_literal_atoms = num_literal_atoms + 1;
			str_literal_atoms.push_back(returning_string);
		}
		else if (token_type == 5){
			break;
		}
	}

	if (num_literal_atoms != 0){
		cout << "LITERAL ATOMS: " << num_literal_atoms << ", ";
		for (i = 0; i < num_literal_atoms - 1; i++){
			cout << str_literal_atoms[i] << ", ";
		}
		cout << str_literal_atoms[num_literal_atoms - 1] << endl;
	}
	else {
		cout << "LITERAL ATOMS: " << num_literal_atoms << endl;
	}
	if (num_numeric_atoms != 0){
		cout << "NUMERIC ATOMS: " << num_numeric_atoms << ", ";
		for (i = 0; i < num_numeric_atoms; i++){
			istringstream istr(str_numeric_atoms[i]);
			istr >> temp_numeric_atoms;
			sum_numeric_atoms = sum_numeric_atoms + temp_numeric_atoms;
		}
		ostringstream ostr;
		ostr << sum_numeric_atoms;
		cout << ostr.str() << endl;
	}
	else {
		cout << "NUMERIC ATOMS: " << num_numeric_atoms << endl;
	}
	cout << "OPEN PARENTHESIS: " << num_openparenthesis << endl;
	cout << "CLOSING PARENTHESIS: " << num_closingparenthesis << endl;
	return 0;
}