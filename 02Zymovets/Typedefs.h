#ifndef _TYPEDEFS_ZYMOVETS_
#define _TYPEDEFS_ZYMOVETS_
#include "Macros.h"
#include "AnyString.h"
#include "CharTraits.h"

ANY_BEGIN

using String = AnyString<char, CharTraits<char> >;
using WString = AnyString<wchar_t, CharTraits<wchar_t> >;


ANY_END
#endif // !_TYPEDEFS_ZYMOVETS_