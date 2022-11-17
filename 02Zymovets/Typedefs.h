#ifndef _TYPEDEFS_ZYMOVETS_
#define _TYPEDEFS_ZYMOVETS_
#include "Macros.h"
#include "AnyString.h"
#include "CharTraits.h"

ANY_BEGIN

using String = AnyString<char, CharTraits<char> >;
using WString = AnyString<wchar_t, CharTraits<wchar_t> >;

//using Ostream = std::basic_ostream<char, CharTraits<char, int> >;
//using Wostream = std::basic_ostream<wchar_t, CharTraits<wchar_t, int> >;

//Ostream Cout (new std::basic_streambuf<char, CharTraits<char, int>>);
//Wostream Wcout;

ANY_END
#endif // !_TYPEDEFS_ZYMOVETS_