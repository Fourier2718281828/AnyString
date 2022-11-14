#ifndef _STRING_DATA_
#define _STRING_DATA_
#include "AnyString.h"

template<typename CharType, typename CharTraits>
class AnyString<CharType, CharTraits>::string_data
{
public:
	using char_type = AnyString::char_type;
	using char_ñref = AnyString::char_ñref;
	using char_traits = AnyString::char_traits;
	using size_type = AnyString::size_type;
public:
	string_data(const char_type* const, const size_type);
	string_data(const string_data&) = delete;
	~string_data();
public:
	string_data* getOwnCopy();
	void assign(const char_type* const, const size_type);
	void setShareable(bool sharable) noexcept;
	bool isShareable() const noexcept;
public:
	string_data& operator= (const string_data&) = delete;
private:
	void copy_elems_from(const char_type* const, const size_type);
private:
	char_type* _chrs;
	size_type _size;
	bool _shareable;
};

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::string_data::string_data(const char_type* const str, const size_type size) :
	_chrs(new char_type[size + 1]),
	_size(size),
	_shareable(true)
{
	copy_elems_from(str, size + 1);
}

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::string_data::~string_data()
{
	delete _chrs;
	_chrs = nullptr;
}

template<typename CharType, typename CharTraits>
inline void AnyString<CharType, CharTraits>::string_data::setShareable(bool shareable) noexcept
{
	_shareable = shareable;
}

template<typename CharType, typename CharTraits>
inline bool AnyString<CharType, CharTraits>::string_data::isShareable() const noexcept
{
	return _shareable;
}

template<typename CharType, typename CharTraits>
inline void AnyString<CharType, CharTraits>::string_data::copy_elems_from(const char_type* const str, const size_type size)
{
	strcpy_s(_chrs, size, str);
}

#endif // !_STRING_DATA_