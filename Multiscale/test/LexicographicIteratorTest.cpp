#include "multiscale/util/iterator/LexicographicNumberIterator.hpp"

#include <iostream>

using namespace std;
using namespace multiscale;

int main() {
	LexicographicNumberIterator it(1023);

	while (it.hasNext()) {
		cout << it.number() << endl;
	}
}
