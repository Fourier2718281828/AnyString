#include "AnyString.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using namespace Zymovets02_AnyString;

int main()
{
	using namespace Zymovets02_AnyString;
	AnyString<char> s = "abcd", d = "vbnm";
	s[0] = '$';
	cout << s[0];
	cout << s.size() << endl;
	cout << s;
	//cout << std::string("asd");
	//operator<< <char, CharTraits<char>> (cout, s);

	return 0;
}