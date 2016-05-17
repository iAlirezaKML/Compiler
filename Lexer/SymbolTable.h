#ifndef __SwiftCompiler__SymbolTable__
#define __SwiftCompiler__SymbolTable__

#include <iostream>
#include <string>
#include <map>

using namespace std;

class SymbolTable {
public:
	int size = 0;
	
	int operator()(const string& key = "");
	string display() const;
	
private:
	map<string, int> table;
};

#endif