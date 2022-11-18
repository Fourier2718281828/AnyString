#define NODESTRUCTORS
#include "AnyString.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::wcout;
using std::endl;
using namespace Zymovets02_AnyString;

void prev_test()
{
	using namespace Zymovets02_AnyString;
	using String = AnyString<char>;
	//String b = "abcde";
	//const char* pb = static_cast<const char*>(b);
	//b = pb;
	//Constructors, assignment :
	{
		cout << "1. Constructors & assignment" << endl;
		cout << "Calling all the constructors :" << endl;
		String a = "asdasd";							cout << "Created : " << '\"' << a << '\"' << endl;
		String b = "String";				cout << "Created : " << '\"' << b << '\"' << endl;
		String c = 's';						cout << "Created : " << '\"' << c << '\"' << endl;
		String d(std::string("string"));	cout << "Created : " << '\"' << d << '\"' << endl;
		String e(b);						cout << "Created : " << '\"' << e << '\"' << endl;
		String f = _STD move(a);			cout << "Created : " << '\"' << f << '\"' << endl;

		cout << "Notice: String(nullptr) is forbidden by String(std::nullptr_t) = delete!" << endl;
		//String(nullptr);

		cout << endl;

		cout << "Copy-Assignment :" << endl;
		b = c;					cout << "Result : " << '\"' << b << '\"' << endl;
		cout << "Move-Assignment :" << endl;
		c = _STD move(e);		cout << "Result : " << '\"' << c << '\"' << endl;
	}
	
	//operator[] :
	{
		cout << endl;
		cout << "3. operator[]" << endl;
		cout << "Creating a String :" << endl;
		String str = "str";
		cout << "Created : " << str << endl;
		cout << "Iterating over it via operator[] : " << endl;
		for (size_t i = 0u; i < str.size(); ++i)
		{
			cout << str[i] << ' ';
		}
		cout << endl << "When exceeding the index limit : " << endl;

		

		str[0] = 'B';
		cout << "Assigning str[0] = 'B';  str = " << str << endl;
	}

	//Additional methods :
	{
		cout << endl;
		cout << "4. Methods size(), empty(), clear()" << endl;
		String str("some_str");
		cout << "String created : " << '\"' << str << '\"' << endl;
		cout << "str.size() = " << str.size() << endl;
		cout << _STD boolalpha << "str.empty() = " << str.empty() << endl;
		cout << "str.clear();" << endl;
		str.clear();
		cout << "str = " << '\"' << str << '\"' << ", str.empty() = " << str.empty() << endl;
	}
	//operator+ and operator+= :
	{
		cout << endl;
		cout << "5. operator+ and operator+= : " << endl;
		cout << "Operator+ calls moving constructor to move the local result :" << endl;
		cout << "String(\"abc\") + String(\"def\"): " << endl;
		cout << "Result = " << String("abc") + String("def") << endl;

		cout << endl;
		cout << "When trying to mix types : " << endl;
		cout << "String(\"abc\") + \"cde\" = " << endl << String("abc") + "cde" << endl;
		cout << "\"cde\" + String(\"abc\") = " << endl << "cde" + String("abc") << endl;
		cout << "String(\"abc\") + std::string(\"cde\") = " << endl << String("abc") + std::string("cde") << endl;
		cout << "std::string(\"cde\") + String(\"abc\") = " << endl << std::string("cde") + String("abc") << endl;
		cout << endl;
		cout << endl;
		String str1("abc"), str2("def");
		cout << "str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"." << endl;
		cout << "str1 += str2 :" << endl;
		str1 += str2;
		cout << "str2 += \"some\" :" << endl;
		str2 += "some";
		cout << "str1 += std::string(\"some\") :" << endl;
		str1 += std::string("some");
		cout << "str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"." << endl;
	}

	//Cmp operators :
	cout << endl;
	cout << "String(\"abc\") != String(\"cde\") = " << endl << (String("abc") != String("cde")) << endl;
	cout << "String(\"abc\") == \"abc\" = " << endl << (String("abc") == String("abc")) << endl;

	cout << endl << "Now create a vector of Strings (a tone of copies) :" << endl;
	std::vector<String> toSort
	{
		"bcd",
		"abcd",
		"ab",
		"abc",
		"abc",
		"defgas",
		"dabc"
	};
	auto pringToSort = [&toSort]()
	{
		cout << "toSort :" << endl;
		for (size_t i = 0u; i < toSort.size(); ++i)
		{
			cout << toSort[i] << endl;
		}
	};
	cout << endl;
	pringToSort();
	cout << endl;
	cout << "Now sort it using std::sort (some moves):" << endl;
	_STD sort(toSort.begin(), toSort.end(), std::less<String>());
	cout << endl;
	pringToSort();
}

template <typename ÑhaType, typename CharTraits>
void tester(const AnyString<ÑhaType, CharTraits>& str)
{
	cout << "AnyString : " << str << endl;
	cout << "Shareable : " << str.is_shareable() << endl;
	cout << "RefCounter: " << str.ref_counter() << endl;
}

template <typename CharTraits>
void tester(const AnyString<wchar_t, CharTraits>& str)
{
	wcout << L"AnyString : " << str << endl;
	wcout << L"Shareable : " << str.is_shareable() << endl;
	wcout << L"RefCounter: " << str.ref_counter() << endl;
}

void testString()
{
	{
		cout << "1. Constructors" << endl;
		cout << "Calling basic the constructors :" << endl;
		String a = "asdasd";							cout << "Created : " << '\"' << a << '\"' << endl;
		String b = "String";				cout << "Created : " << '\"' << b << '\"' << endl;
		String c = 's';						cout << "Created : " << '\"' << c << '\"' << endl;
		String d(std::string("string"));	cout << "Created : " << '\"' << d << '\"' << endl;
		//String e(b);						cout << "Created : " << '\"' << e << '\"' << endl;
		//String f = _STD move(a);			cout << "Created : " << '\"' << f << '\"' << endl;

		cout << "Notice: String(nullptr) is forbidden by String(std::nullptr_t) = delete!" << endl;
		//String(nullptr);
		cout << "Let's see the tester function result on this strings:" << endl;
		cout << "================================================" << endl;
		tester(a);
		tester(b);
		tester(c);
		tester(d);
		cout << "================================================" << endl;
		cout << endl;
	}

	{
		cout << "--------------------------------------------------------------------" << endl;
		cout << endl << "2. When we have to defer copying. Copy ctor & copy assignment" << endl;
		cout << "Create a String :" << endl;
		String a = "string";
		cout << "Its tester:" << endl;
		cout << "================================================" << endl;
		tester(a);
		cout << "================================================" << endl;
		cout << "Now create another one by \"copying\" it :" << endl;
		String b(a);
		cout << "testers of the strings:" << endl;
		cout << "================================================" << endl;
		tester(a);
		tester(b);
		cout << "================================================" << endl;
		cout << "Now create independent one:" << endl;
		String c("independent");
		cout << "tester of third one :" << endl;
		cout << "================================================" << endl;
		tester(c);
		cout << "================================================" << endl;
		cout << "Now assign second string to the third, independent one :" << endl;
		c = b;
		cout << "testers of all strings :" << endl;
		cout << "================================================" << endl;
		tester(a);
		tester(b);
		tester(c);
		cout << "================================================" << endl;
		cout << "Now no matter how we assign those strings to each other, testers stay stable :" << endl;
		a = b;
		a = c;
		b = a;
		b = c;
		c = a;
		c = b;
		cout << "testers of all strings :" << endl;
		cout << "================================================" << endl;
		tester(a);
		tester(b);
		tester(c);
		cout << "================================================" << endl;
		cout << "Now let's separate strings from the membership one by one by assigning something different to them :" << endl;
		a = "new val for first";
		cout << "================================================" << endl;
		tester(a);
		tester(b);
		tester(c);
		cout << "================================================" << endl;
		b = "new val for second";
		cout << "================================================" << endl;
		tester(a);
		tester(b);
		tester(c);
		cout << "================================================" << endl;
		cout << "Now we've got 3 independent strings." << endl;
	}

	{
		cout << "--------------------------------------------------------------------" << endl;
		cout << endl << "3. Move ctor & assignment :" << endl;
		cout << "Create two independent strings and one dependent (on first):" << endl;
		String a("first"), b("second"), c(a);

		cout << "================================================" << endl;
		tester(a);
		tester(b);
		tester(c);
		cout << "================================================" << endl;
		cout << "Let's create one more via move-ctor on a:" << endl;
		String d(std::move(a));
		cout << "================================================" << endl;
		cout << "FIRST ONE IS NOW MOVED FROM" << endl;
		tester(b); 
		tester(c);
		tester(d);
		cout << "================================================" << endl;
		cout << "Now move d to c via assignment :" << endl;
		c = std::move(d);
		cout << "================================================" << endl;
		cout << "FIRST ONE IS NOW MOVED FROM" << endl;
		tester(b);
		tester(c);
		cout << "LAST ONE IS NOW MOVED FROM" << endl;
		cout << "================================================" << endl;
		cout << "Everything works just as if we were working with ordinary strings" << endl;
	}

	{
		cout << "--------------------------------------------------------------------" << endl;
		cout << endl << "3. Move ctor & assignment :" << endl;
	}
}

#include <vector>
int main()
{
	cout << "ATTENTION! If you want to see all the destructor calls" << endl;
	cout << "comment the line 1 : #define NODESTRUCTORS" << endl;
	cout << "------------------------------------------------------" << endl;
	testString();
	return 0;
}