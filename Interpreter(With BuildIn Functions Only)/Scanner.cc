#include "getNextToken.cc"
using namespace std;

class Scanner{
	int token_type;
	string returning_string;
public:
	void Init(string * input_string, int * input_index){
		getNextToken(&token_type, &returning_string, input_string, input_index, false);
		return;
	}
	void GetCurrent(int * cur_token_type, string * cur_returning_string){
		* cur_token_type = token_type;
		* cur_returning_string = returning_string;
		return;
	}
	void MoveToNext(string * input_string, int * input_index){
		getNextToken(&token_type, &returning_string, input_string, input_index, false);
		return;
	}
	void MoveToNextMute(string * input_string, int * input_index){
		getNextToken(&token_type, &returning_string, input_string, input_index, true);
		return;
	}
};