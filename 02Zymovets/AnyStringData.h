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
	string_data();
	string_data(const size_type);
	string_data(const char_type* const, const size_type);
	string_data(const char_type);
	string_data(const string_data&) = delete;
	~string_data();
public:
	data_ptr clone() const;
	void assign(const char_type* const, const size_type);
	void set_shareable(bool sharable) noexcept;
	bool is_shareable() const noexcept;
	size_type size() const noexcept;
	char_type* chars() noexcept;
	void copy_elems_from(const char_type* const, const size_type);
public:
	string_data& operator= (const string_data&) = delete;
private:
	char_type* _chrs;
	size_type _size;
	bool _shareable;
};

DATA_MEMBER string_data::string_data() :
	_chrs(new char_type[1] { char_type() }),
	_size(0u),
	_shareable(true)
{
}

DATA_MEMBER string_data::string_data(const size_type n) :
	_chrs(new char_type[n + 1]),
	_size(n),
	_shareable(true)
{
	_chrs[n] = char_type();
}

DATA_MEMBER string_data(const char_type* const str, const size_type size) :
	_chrs(new char_type[size + 1]),
	_size(size),
	_shareable(true)
{
	copy_elems_from(str, size + 1);
}

DATA_MEMBER string_data(const char_type c) :
	_chrs(new char_type[2] {c, 0}), //Bad practice - solved by allocators
	_size(1u),
	_shareable(true)
{
}

DATA_MEMBER ~string_data()
{
#ifndef NDEBUG
	PRINT("###String Data deleted")
#endif // !NDEBUG

	delete[] _chrs;
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

DATA_METHOD copy_elems_from(const char_type* const str, const size_type size) -> void
{
	char_traits::copy(_chrs, str, size);
}

ANY_END

#endif // !_STRING_DATA_