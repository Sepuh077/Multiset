#include <iostream>
#include "MultiSet.h"

using namespace std;

int main() {
	MultiSet a, b;
	cin >> a;
	b = a;
	b.add_member(89);
	cout << b << endl;
	b -= a;
	cout << b << endl;
	return 0;
}