#ifndef __SwiftCompiler__Token__
#define __SwiftCompiler__Token__

#include <iostream>
#include <string>
#include "SymbolTable.h"

using namespace std;

class Token {
public:
	static const string states_map[58];
	static SymbolTable ST;
	
	Token();
	
	void tokenize(const int& state, const string& content);
	
	string print();
	
private:
	string name;
	int attrib;
	
	bool isKeyword(const string& str);
};

#endif