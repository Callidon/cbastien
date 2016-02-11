#include "table_symboles.hpp"

using namespace std;

const int NB_SYMBOLES = 18;

void table_symboles_init(table_symboles_t & table) {
	int i = 0;
	string symboles[NB_SYMBOLES] = {"S", "N", "E", "T", "F", ";", "->", "+", ".", ",", "(", ")", "[", "]", "(/", "/)","IDNTER", "ELTER"};
	for(i = 0; i < NB_SYMBOLES; i++) {
		table[i] = symboles[i];
	}
}

int table_get_code(table_symboles_t & table, string symbole) {
	int code = -1;
	for (map<int, string>::iterator it = table.begin(); it != table.end(); ++it) {
		if(it->second == symbole) {
			return it->first;
		}
	}
	return code;
}
