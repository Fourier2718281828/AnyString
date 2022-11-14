#ifndef _ANY_STRING_REALIZATION_
#define _ANY_STRING_REALIZATION_
#include "AnyString.h"
#include "AnyStringData.h"
#include "AnyStringProxy.h"

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::AnyString()
	: _data(std::make_shared<string_data>("", 0u))
{
}


template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::~AnyString() = default;

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::CharProxy AnyString<CharType, CharTraits>::operator[](const size_type i)
{
	return CharProxy(*this, i);
}

#endif // !_ANY_STRING_REALIZATION_