#include <iostream>

using namespace std;

class A {
private:
	const int i;

public:
	A():i(0) { }
	A(int a):i(a) {}
	int print() { return cout << "non-const object, i: " << i << endl; }
	int print() const { return cout << "    const object, i: " << i << endl; }
};

int main()
{
	A a, b(8);
	a.print();
	b.print();

	const A c(3);
	c.print();

	cout << "i1o0Oo1liLl1" << endl;

	return 0;
}
