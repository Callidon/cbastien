#include "serializer.hpp"

using namespace std;


/*
convention pour sérializer un node
conc : c(_,_)
union : u(_,_)
star : s(_)
un : un(_)
atom : a(_,_,_)
*/

void serialize_forest(Go & go, std::string filename) {

}

void serialize_node(Node * node, std::fstream * file) {

}

void deserialize_forest(Go & go, std::string filename) {

}

Node * deserializer_node(std::string token) {

}

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
	char current = "";
	while(! file.eof()) {
		current = file.get();
		while((current != " ") && (current != "\n")) {
			token += current;
			current = file.get();
		}
		stack.add(int(token));
		token = "";
	}
}
