#include <iostream>
#include <fstream>
#include <string>

#include "DFA.h"
#include "Token.h"
#include "Log.h"

using namespace std;

void preProcess(string& str) {
	auto found = str.find("#define");
	if (found != string::npos) {
		auto i=found+8, begin=found, end=found;
		string macro="", value="";
		
		while (str.at(i) != '\n' && i < str.size()-1) {
			if ((str.at(i) <= 'z' && str.at(i) >= 'a') || (str.at(i) <= 'Z' && str.at(i) >= 'A')) {
				macro += str.at(i);
				i++;
			}
			else if (str.at(i) == ' ') {
				while (str.at(i) != '\n' && i < str.size()-1) {
					value += str.at(i);
					i++;
				}
			}
			else
				break;
		}
		end = i;
		
		str.erase(begin, end-begin);
		
		for (i=end; i<str.size(); i++) {
			if (str.at(i) == '"') {
				while (i < str.size()) {
					i++;
					if (str.at(i) == '"' || str.at(i) == '\n') break;
				}
			}
			else if (str.at(i) == '/') {
				i++;
				if (str.at(i) == '/') {
					while (i < str.size()) {
						i++;
						if (str.at(i) == '\n') break;
					}
				}
				else if (str.at(i) == '*') {
					while (i < str.size()) {
						i++;
						if (str.at(i) == '*') {
							i++;
							if (str.at(i) == '/') break;
						}
					}
				}
			}
			else if (str.at(i) == macro.at(0)) {
				begin = i;
				for (int j=1; j<macro.size(); j++) {
					i++;
					if (str.at(i) != macro.at(j)) break;
					else if (j+1 == macro.size()) {
						if ((str.at(i+1) <= 'z' && str.at(i+1) >= 'a') || (str.at(i+1) <= 'Z' && str.at(i+1) >= 'A'))
							break;
						else {
							str.erase(begin, macro.size());
							str.insert(begin, value);
							break;
						}
					}
				}
				
			}
		}
	}
}

int main(int argc, const char * argv[]) {
	
	DFA dfa;
	
	int first_pos = 0, cur_pos = 0, state = -1;
	Token token;
	string buffer = "", temp_str;
	
	ifstream source_file;
	ofstream token_file, st_file;
	
	Log log;
	
	source_file.open(argv[1]);
	if (!source_file.is_open()) {
		log("INVALID ARG, TRYING: \"source.swift\"");
		source_file.open("source.swift");
		if (!source_file.is_open()) {
			log("\"source.swift\" NOT FOUND!");
			return 1;
		}
		else
			log("------FILE\t\"source.swift\" IS OPEN.");
	}
	else
		log("------FILE\t\"" + string(argv[1]) + "\" IS OPEN.");
	
	token_file.open("token.txt");
	
	st_file.open("symbol_table.txt");
	
	log();
	
	while (!source_file.eof()) {
		getline(source_file, temp_str);
		buffer = buffer + temp_str + "\n";
	}
	preProcess(buffer);
	
	cout << buffer << endl;
	
	while (true) {
		cur_pos = 0;
		first_pos = cur_pos;
		while (cur_pos < buffer.size()-1) {
			state = dfa.trace(buffer, first_pos, cur_pos);
			temp_str = "";
			for (int i = first_pos; i<cur_pos; i++)
				temp_str += buffer.at(i);
			token.tokenize(state, temp_str);
			token_file << token.print();
			first_pos = cur_pos;
		}
		if (first_pos == buffer.size() - 1) break;
	}
	
	st_file << token.ST.display() << endl;
	
	source_file.close();
	
	token_file.close();
	
	st_file.close();
	
	return 0;
}
