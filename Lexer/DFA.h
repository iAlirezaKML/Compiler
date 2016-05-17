#ifndef __SwiftCompiler__DFA__
#define __SwiftCompiler__DFA__

#include <iostream>
#include <string>

using namespace std;

class DFA {
public:
	static const int dfa_table[58][28];
	
	int operator() (const int& x, const int& y) const;
	int trace(const string& buffer, int& first_pos, int& cur_pos);
private:
	bool isLegal(const int& input);
	bool isAccept(const int& state);
	int mapInput(const char& input);
};


#endif