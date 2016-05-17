#include "SymbolTable.h"
#include <string>

int SymbolTable::operator()(const string& key) {
	if (table.count(key) == 1)
		return table[key];
	table[key] = size++;
	return size - 1;
}

string SymbolTable::display() const {
	string st_content = "";
	for (auto i = table.begin(); i != table.end(); i++) {
		st_content += i->first + ',' + to_string(i->second) + '\n';
	}
	return st_content;
}