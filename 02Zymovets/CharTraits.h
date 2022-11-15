#ifndef _CHAR_TRAITS_
#define _CHAR_TRAITS_
#include "Macros.h"

ANY_BEGIN

template<typename _CharType>
class CharTraits
{
public:
	using char_type = _CharType;
};

ANY_END

#endif // !_CHAR_TRAITS_