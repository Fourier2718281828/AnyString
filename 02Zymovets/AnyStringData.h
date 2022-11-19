#ifndef _STRING_DATA_
#define _STRING_DATA_
#include "AnyString.h"
#include "Macros.h"

ANY_BEGIN

template<typename CharType, typename CharTraits>
class AnyString<CharType, CharTraits>::string_data
{
public:
	using char_type = AnyString::char_type;
	using char_ñref = AnyString::char_ñref;
	using char_traits = AnyString::char_traits;
	using size_type = AnyString::size_type;
	using data_ptr = std::shared_ptr<string_data>;
public:
	struct AllocateOnly_tag {};
public:
	string_data();
	explicit string_data(const size_type, AllocateOnly_tag);
	string_data(const char_type* const, const size_type);
	explicit string_data(const char_type);
	string_data(const string_data&) = delete;
	~string_data();
public:
	data_ptr clone() const;
	void set_shareable(bool) noexcept;
	bool is_shareable() const noexcept;
	size_type size() const noexcept;
	char_type* chars() noexcept;
	char_type* construct_char(char_type* const, const char_type&) const;
	void construct_range(char_type*, const char_type*, size_type) const;
public:
	string_data& operator= (const string_data&) = delete;
private:
	char_type* _chrs;
	size_type _size;
	bool _shareable;
};

DATA_MEMBER string_data::string_data() :
	string_data(0u, AllocateOnly_tag{})
{
}

DATA_MEMBER string_data::string_data(const size_type n, AllocateOnly_tag) :
	_chrs(reinterpret_cast<char_type*>(::operator new((n + 1) * sizeof(char_type)))),
	_size(n),
	_shareable(true)
{
	construct_char(&_chrs[n], char_type());
}

DATA_MEMBER string_data(const char_type* const str, const size_type size) :
	string_data(size, AllocateOnly_tag{})
{
	construct_range(_chrs, str, size);
}

DATA_MEMBER string_data(const char_type c) :
	string_data(1u, AllocateOnly_tag{})
{
	construct_char(&_chrs[0], c);
}

DATA_MEMBER ~string_data()
{
#ifndef NDEBUG
	PRINT("###String Data deleted")
#endif // !NDEBUG

	for (size_type i = 0; i < size(); ++i)
	{
		_chrs[i].~char_type();
	}
	::operator delete(_chrs);
	_chrs = nullptr;
	_size = 0u;
	_shareable = false;
}

DATA_METHOD string_data::clone() const -> data_ptr
{
	return std::make_shared<string_data>(_chrs, size());
}

DATA_METHOD set_shareable(bool shareable) noexcept -> void
{
	_shareable = shareable;
}

DATA_METHOD is_shareable() const noexcept -> bool
{
	return _shareable;
}

DATA_METHOD size() const noexcept -> size_type
{
	return _size;
}

DATA_METHOD chars() noexcept -> char_type*
{
	return _chrs;
}

DATA_METHOD construct_char(char_type* const ptr, const char_type& ch) const -> char_type*
{
	return new (ptr) char_type(ch);
}

DATA_METHOD construct_range(char_type* dst, const char_type* src, size_type cnt) const -> void
{
	for (; cnt; dst++, src++, --cnt)
	{
		construct_char(dst, *src);
	}
}

ANY_END

#endif // !_STRING_DATA_
