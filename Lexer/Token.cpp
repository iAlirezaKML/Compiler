#include "Token.h"
#include "Log.h"
#include <string>

SymbolTable Token::ST = *new SymbolTable;

const string Token::states_map[58] =
{ "reject", // 0
	"identifier", // 1 identifier
	"num", // 2 num
	"PANIC", // 3 PANIC .
	"reject", // 4
	"/", // 5 /
	"whitespace", // 6 whitespace
	"*", // 7 *
	"whitespace", // 8 whitespace
	"whitespace", // 9 whitespace
	"=", // 10 =
	"!", // 11 !
	"<", // 12 <
	">", // 13 >
	"+", // 14 +
	"-", // 15 -
	"&", // 16 &
	"|", // 17 |
	"%", // 18 %
	"{", // 19 {
	"}", // 20 }
	"[", // 21 [
	"]", // 22 ]
	"(", // 23 (
	")", // 24 )
	":", // 25 :
	",", // 26 ,
	";", // 27 ;
	"identifier", // 28 identifier
	"identifier", // 29 identifier
	"num", // 30 num
	"num", // 31 num
	"literal", // 32 literal
	"reject", // 33
	"reject", // 34
	"reject", // 35
	"/=", // 36 /=
	"*=", // 37 *=
	"==", // 38 ==
	"!=", // 39 !=
	"<=", // 40 <=
	">=", // 41 >=
	"+=", // 42 +=
	"++", // 43 ++
	"-=", // 44 -=
	"->", // 45 ->
	"--", // 46 --
	"&&", // 47 &&
	"||", // 49 ||
	"num", // 49 num
	"reject", // 50
	"comment", // 51 comment
	"reject", // 52
	"reject", // 53
	"comment", // 54 comment
	"reject",  // 55
	"PANIC", // 56 PANIC */
	"identifier" // 57 PANIC identifier
};

bool Token::isKeyword(const string &str) {
	if (str == "var"	||
		str == "let"	||
		str == "if"		||
		str == "else"	||
		str == "while"	||
		str == "func"	||
		str == "return") {
		return true;
	}
	return false;
}

Token::Token() {
	this->name = "";
	this->attrib = -1;
}

void Token::tokenize(const int& state, const string& content) {
	if (state < 0) {
		name = "PANIC";
		attrib = -1;
		return;
	}
	name = states_map[state];
	switch (state) {
		// identifier
		case 1:
		case 28:
		case 29:
		{
			if (isKeyword(content)) {
				name = content;
				attrib = -1;
				break;
			}
		}
		// num
		case 2:
		case 30:
		case 31:
		case 49:
		// literal
		case 32:
		{
			if (content.at(content.size()-1) == '\n') Log::line++;
			attrib = ST(content);
			break;
		}
		// PANIC Recovery
		case 57:
		{
			Log::log("PANIC-MODE: ", state);
			string tmp = "";
			for (int i=0; i<content.size(); i++)
				if ((content.at(i) <= 'z' && content.at(i) >= 'a') || (content.at(i) <= 'Z' && content.at(i) >= 'A'))
					tmp += content.at(i);
			if (isKeyword(tmp)) {
				name = content;
				attrib = -1;
			}
			else
				attrib = ST(tmp);
		}
			break;
		case 3:
		case 56:
			Log::log("PANIC-MODE: ", state);
			break;
		// line increament
		case 6:
		case 51:
			Log::line++;
		default:
			attrib = -1;
			break;
	}
}


string Token::print() {
	if (name == "comment" || name == "whitespace" || name == "PANIC")
		return "";
	else if (attrib == -1)
		return '<' + this->name + '>';
	return '<' + this->name + ',' + to_string(this->attrib) + '>';
}