#ifndef PCODE_HPP
#define PCODE_HPP

// Instructions de Pseudo Code
enum Pcode {
	LDA = 1,
	LDV = 2,
	LDC = 3,
	JMP = 4,
	JIF = 5,
	JSR = 6,
	RSR = 7,
	SUP = 8,
	SUPE = 9,
	INF = 10,
	INFE = 11,
	EQ = 12,
	DIFF = 13,
	RD = 14,
	RDLN = 15,
	WRT = 16,
	WRTLN = 17,
	ADD = 18,
	MOINS = 19,
	DIV = 20,
	MULT = 21,
	NEQ = 22,
	INC = 23,
	DEC = 24,
	AND = 25,
	OR = 26,
	NOT = 27,
	AFF = 28,
	STOP = 29,
	INDA = 30,
	INDV = 31
};

#endif
