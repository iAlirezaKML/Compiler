#ifndef __SwiftCompiler__Log__
#define __SwiftCompiler__Log__

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Log {
public:
	static unsigned int line;
	
	static void log(string str="", const int& state=0);
	
	~Log();
	
	void operator() (const string& str="");
private:
	static ofstream log_file;
};

#endif