#include "Log.h"

unsigned int Log::line = 0;

ofstream Log::log_file("log.txt");

Log::~Log() {
	log_file.close();
}

void Log::operator()(const string& str) {
	log_file << "Line: " << line << " \t" << str << endl;
}

void Log::log(string str, const int& state) {
	switch (state) {
		case -2:
			str += "Illegal Input. Skipped!";
			break;
		case 3:
			str += "Unexpected \'.\'";
			break;
		case 56:
			str += "Unexpected \"*/\" Comment is not opened!";
			break;
		case 57:
			str += "Unexpected identifier, first letter considered as identifier!";
			break;
	default:
			str += "Fatal Error!";
			break;
	}
	log_file << "Line: " << line+1 << " \t" << str << endl;
}