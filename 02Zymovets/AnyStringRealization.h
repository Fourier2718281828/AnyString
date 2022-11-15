#ifndef _ANY_STRING_REALIZATION_
#define _ANY_STRING_REALIZATION_
#include "AnyString.h"
#include "AnyStringData.h"
#include "AnyStringProxy.h"
#include "Macros.h"

ANY_BEGIN

ANY_MEMBER AnyString() :
	_data(std::make_shared<string_data>("", 0u))
{
}

ANY_MEMBER AnyString(const char_type c) :
	_data(std::make_shared<string_data>(c))
{
}

ANY_MEMBER AnyString(const char_type* const chrs) :
	_data(std::make_shared<string_data>(chrs, strlen(chrs)))
{
}

ANY_MEMBER ~AnyString() = default;

ANY_METHOD operator[](const size_type i) -> CharProxy
{
	check_at(i);
	return CharProxy(*this, i);
}

ANY_METHOD operator[](const size_type i) const -> char_ñref
{
	check_at(i);
	return _data->chars()[i];
}

ANY_METHOD size() const noexcept -> size_type
{
	return _data->size();
}

ANY_METHOD empty() const noexcept -> bool
{
	return size() == 0u;
}

ANY_METHOD check_at(const size_type i) const -> void
{
	if (i >= size())
		throw 1; //TODO define Badstring and throw it!
}

ANY_METHOD read_at(const size_type i) const -> const char_type&
{
	return _data->chars()[i];
}

ANY_METHOD write_at(char_ñref c, const size_type i) -> void
{
	if(_data.use_count() != 1) 
		_data = _data->getOwnCopy();
	_data->chars()[i] = c;
}

ANY_END

#endif // !_ANY_STRING_REALIZATION_