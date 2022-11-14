#ifndef _ANY_STRING_REALIZATION_
#define _ANY_STRING_REALIZATION_
#include "AnyString.h"
#include "AnyStringData.h"
#include "AnyStringProxy.h"

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::AnyString() : 
	_data(std::make_shared<string_data>("", 0u))
{
}

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::AnyString(const char_type c) :
	_data(std::make_shared<string_data>(c))
{
}

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::AnyString(const char_type* const chrs) :
	_data(std::make_shared<string_data>(chrs, strlen(chrs)))
{
}

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::~AnyString() = default;

template<typename CharType, typename CharTraits>
inline auto AnyString<CharType, CharTraits>::operator[](const size_type i) -> CharProxy
{
	check_at(i);
	return CharProxy(*this, i);
}

template<typename CharType, typename CharTraits>
inline auto AnyString<CharType, CharTraits>::operator[](const size_type i) const -> char_ñref
{
	check_at(i);
	return _data->chars()[i];
}

template<typename CharType, typename CharTraits>
inline auto AnyString<CharType, CharTraits>::size() const noexcept -> size_type
{
	return _data->size();
}

template<typename CharType, typename CharTraits>
inline bool AnyString<CharType, CharTraits>::empty() const noexcept
{
	return size() == 0u;
}

template<typename CharType, typename CharTraits>
inline void AnyString<CharType, CharTraits>::check_at(const size_type i) const
{
	if (i >= size())
		throw 1; //TODO define Badstring and throw it!
}
template<typename CharType, typename CharTraits>
inline auto AnyString<CharType, CharTraits>::read_at(const size_type i) const -> const char_type&
{
	return _data->chars()[i];
}
template<typename CharType, typename CharTraits>
inline void AnyString<CharType, CharTraits>::write_at(char_ñref c, const size_type i)
{
	if(_data.use_count() != 1) _data = _data->getOwnCopy();
	_data->chars()[i] = c;
}
#endif // !_ANY_STRING_REALIZATION_