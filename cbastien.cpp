#include "src/generators.hpp"
#include "iostream"
using namespace std;

int main() {
	Go* go = GenForest();
	printForest(go);

	delete go;
	return 1;
}
