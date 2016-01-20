#include "src/generators.hpp"
#include "iostream"
using namespace std;

int main() {
	Atom* a = GenAtom(1,0,Terminal);
	Atom* b = GenAtom(2,0,Terminal);
	cout << a->code << endl;

	delete a;
	delete b;
	return 1;
}
