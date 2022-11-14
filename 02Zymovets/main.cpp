#include "AnyString.h"
#include <iostream>
using std::cout;
using std::endl;

AnyString<char> f()
{
	return "abd";
}

int main()
{
	AnyString<char> s = "abcd", d = "vbnm";
	s[0] = '$';
	cout << s[0];
	cout << s.size() << endl;
	return 0;
}