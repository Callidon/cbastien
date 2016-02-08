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
