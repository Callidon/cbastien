#include "interpreter.hpp"
#include <string>
#include <iostream>
#include <functional>
using namespace std;

/*
 * Méthode exécutant une série d'instructions en Pcode
 */
void execute(PcodeStack & pile_pcode) {
	int co = 0;
	int spx = 0;
	ExecStack pile_x;
	while(pile_pcode[co] != STOP) {
		interprete(pile_pcode, pile_x, co, spx);
	}
}

/*
 * Méthode interprétant la prochaine instruction en Pcode dans une pile d'instructions
 */
void interprete(PcodeStack & pile_pcode, ExecStack & pile_x, int co, int spx) {
	auto operateur = [&](function<int(int,int)> op) {
		pile_x[spx - 1] = op(pile_x[spx - 1], pile_x[spx]);
		spx--;
		co++;
	};
	switch(pile_pcode[co]) {
		// Instructions de chargement
		case LDA : {
			spx++;
			pile_x[spx] = pile_pcode[co + 1];
			co = co + 2;
		} break;
		case LDV : {
			spx++;
			pile_x[spx] = pile_x[pile_pcode[co + 1]];
			co = co + 2;
		} break;
		case LDC : {
			spx++;
			pile_x[spx] = pile_pcode[co + 1];
			co = co + 2;
		} break;

		// Instructions de saut
		case JMP : {
			co = pile_pcode[co + 1];
		} break;
		case JIF : {
			if(pile_x[spx] == 0) {
				co = pile_pcode[co + 1];
			} else {
				co = co + 2;
			}
			spx--;
		} break;
		case JSR : {
			// TODO
		} break;
		case RSR : {
			// TODO
		} break;

		// Opérateurs relationnels
		case SUP : {
			operateur([](int a, int b) -> int { a > b; });
		} break;
		case SUPE : {
			operateur([](int a, int b) -> int { a >= b; });
		} break;
		case INF : {
			operateur([](int a, int b) -> int { a < b; });
		} break;
		case INFE : {
			operateur([](int a, int b) -> int { a <= b; });
		} break;
		case EQ : {
			operateur([](int a, int b) -> int { a == b; });
		} break;
		case DIFF : {
			operateur([](int a, int b) -> int { a != b; });
		} break;

		// Instructions I/O
		case RD : {
			string input;
			spx++;
			cin >> input;
			pile_x[spx] = atoi(input.c_str());
			co++;
		} break;
		case RDLN : {
			string input;
			spx++;
			cin >> input;
			cout << endl;
			pile_x[spx] = atoi(input.c_str());
			co++;
		} break;
		case WRT : {
			cout << pile_x[spx];
			spx++;
			co++;
		} break;
		case WRTLN : {
			cout << pile_x[spx] << endl;
			spx++;
			co++;
		} break;

		// Opérateurs mathématiques
		case ADD : {
			operateur([](int a, int b) -> int { a + b; });
		} break;
		case MOINS : {
			operateur([](int a, int b) -> int { a - b; });
		} break;
		case DIV : {
			operateur([](int a, int b) -> int { a / b; });
		} break;
		case MULT : {
			operateur([](int a, int b) -> int { a * b; });
		} break;
		case NEQ : {
			pile_x[spx] = 0 - pile_x[spx];
			co++;
		} break;
		case INC : {
			pile_x[spx]++;
			co++;
		} break;
		case DEC : {
			pile_x[spx]--;
			co++;
		} break;

		// Opérateurs logiques
		case AND : {
			operateur([](int a, int b) -> int { a && b; });
		} break;
		case OR : {
			operateur([](int a, int b) -> int { a || b; });
		} break;
		case NOT : {
			pile_x[spx] = (! pile_x[spx]);
			co++;
		} break;

		// Instructions supplémentaires
		case AFF : {
			pile_x[pile_x[spx - 1]] = pile_x[spx];
			spx = spx - 2;
			co++;
		} break;
		case STOP : {
			// TODO
		} break;
		case INDA : {
			// TODO
		} break;
		case INDV : {
			// TODO
		} break;
	}
}
