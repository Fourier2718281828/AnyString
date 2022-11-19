#ifndef _ANY_STRING_REALIZATION_
#define _ANY_STRING_REALIZATION_
#include "AnyString.h"
#include "AnyStringData.h"
#include "AnyStringProxy.h"
#include "Macros.h"

ANY_BEGIN

ANY_MEMBER AnyString(data_ptr&& data) :
	_data(std::move(data))
{
}

ANY_MEMBER AnyString() :
	_data(std::make_shared<string_data>())
{
#ifndef NDEBUG
	PRINT("###AnyString()")
#endif // !NDEBUG
}

ANY_MEMBER AnyString(const char_type c) :
	_data(std::make_shared<string_data>(c))
{
#ifndef NDEBUG
	PRINT("###AnyString(const char_type c)")
#endif // !NDEBUG
}

ANY_MEMBER AnyString(const char_type* const chrs) :
	_data(std::make_shared<string_data>(chrs, char_traits::length(chrs)))
{
#ifndef NDEBUG
	PRINT("###AnyString(const char_type* const chrs)")
#endif // !NDEBUG
}

ANY_MEMBER AnyString(const AnyString& str) :
	_data
	(
		str._data->is_shareable()
		? str._data
		: str._data->clone()
	)
{
#ifndef NDEBUG
	PRINT("###AnyString(const AnyString& str)")
#endif // !NDEBUG
}

ANY_MEMBER AnyString(AnyString&& str) noexcept :
	_data(std::move(str._data))
{
#ifndef NDEBUG
	PRINT("###AnyString(AnyString&& str)")
#endif // !NDEBUG
}

ANY_MEMBER ~AnyString()
{
#ifndef NDEBUG
#ifndef NODESTRUCTORS
	PRINT("###~AnyString()")
#endif // !NODESTRUCTORS
#endif // !NDEBUG
}

template<typename CharType, typename CharTraits>
template<typename OtherTraits, typename Alloc, typename>
inline AnyString<CharType, CharTraits>::AnyString(const std::basic_string<char_type, OtherTraits, Alloc>& str) :
	AnyString(str.c_str())
{
}

ANY_METHOD operator=(const AnyString& str)& -> AnyString&
{
	if (this != &str)
	{
		_data = str._data->is_shareable()
			? str._data
			: str._data->clone();

#ifndef NDEBUG
		PRINT("###operator=(const AnyString& str)&")
#endif // !NDEBUG
	}

	return *this;
}

ANY_METHOD operator=(AnyString&& str) & noexcept -> AnyString&
{
	if (this != &str)
	{
		_data = std::move(str._data);
#ifndef NDEBUG
		PRINT("###operator=(AnyString&& str)&")
#endif // !NDEBUG
	}

	return *this;
}

ANY_METHOD operator+=(const AnyString& str)& -> AnyString&
{
	return *this = *this + str;
}

ANY_METHOD operator[](const size_type i)&& -> char_ñref
{
	check_at(i);
	return _data->chars()[i];
}

ANY_METHOD operator[](const size_type i)& -> CharProxy
{
	check_at(i);
	return CharProxy(*this, i);
}

ANY_METHOD operator[](const size_type i) const& -> char_ñref
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

ANY_METHOD clear() -> void
{
	*this = AnyString();
}


ANY_METHOD check_at(const size_type i) const -> void
{
	if (i >= size())
		throw BadAnyString(BadAnyString::Type::IndexOutOfBounds, "Index out of bounds.");
}

ANY_METHOD read_at(const size_type i) const -> const char_type&
{
	return _data->chars()[i];
}

ANY_METHOD write_at(char_ñref c, const size_type i) -> void
{
	if(_data.use_count() != 1) 
		_data = _data->clone();
	_data->chars()[i] = c;
}

ANY_METHOD is_shareable() const -> bool
{
	return _data->is_shareable();
}

ANY_METHOD ref_counter() const -> size_type
{
	return _data.use_count();
}

ANY_METHOD compare(const AnyString& str) const -> int
{
	char_type* first = _data->chars();
	char_type* second = str._data->chars();

	const size_type len1 = char_traits::length(first);
	const size_type len2 = char_traits::length(second);

	const int cmp = char_traits::compare(first, second, std::min(len1, len2));
	
	if (cmp)         return cmp;
	if (len1 < len2) return -1;
	if (len1 > len2) return 1;
	                 return 0;
}

template<typename CharType, typename CharTraits>
class AnyString<CharType, CharTraits>::BadAnyString
{
public:
	using char_type = CharType;
	using char_traits = CharTraits;
	using string_t = std::string;
public:
	enum class Type
	{
		IndexOutOfBounds,
		NonTerminatedStringInput,
	};
private:
	const string_t _message;
	const Type        _type;
public:
	BadAnyString(const Type type, const string_t& str = "") :
		_message(str), _type(type) {}

	~BadAnyString() = default;

	inline const string_t what() const noexcept
	{
		return _message;
	}

	inline Type type() const noexcept
	{
		return _type;
	}
};

ANY_END

#endif // !_ANY_STRING_REALIZATION_