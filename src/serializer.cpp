#include "serializer.hpp"

using namespace std;

void serialize_stack(PcodeStack & stack, std::string filename) {
	fstream file (filename, fstream::out);
	for(auto &it : stack) {
		file << to_string(it);
		file << ' ';
	}
}

void deserialize_stack(PcodeStack & stack, std::string filename) {
	fstream file (filename, fstream::in);
	string token;
	string current = "";
	while(! file.eof()) {
		current = file.get();
		while ((current != " ") && (current != "\n") && (! file.eof())) {
			token += current;
			current = file.get();
		}
		if(token != "") {
			stack.push_back(atoi(token.c_str()));
			token = "";
		}
	}
}
