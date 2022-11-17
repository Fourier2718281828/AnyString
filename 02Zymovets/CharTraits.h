#ifndef _CHAR_TRAITS_
#define _CHAR_TRAITS_
#include "Macros.h"

#include <string>
#include <string_view>
#include <iostream>
#include <cctype>

ANY_BEGIN

template<typename _CharType, typename _IntType>
class BasicCharTraits
{
public:
	using char_type = _CharType;
	using int_type = _IntType;
	using pos_type = std::streampos;
	using off_type = std::streamoff;
	using state_type = _Mbstatet;
	using comparison_category = std::strong_ordering;

public:


	static void assign(char_type& left, const char_type& right) noexcept
	{
		left = right;
	}


	static char_type* assign(char_type* first, size_t count, char_type ch)
	{
		for (char_type* next = first; count > 0; --count, ++next) 
		{
			*next = ch;
		}

		return first;
	}


	static bool eq(const char_type& a, const char_type& b) noexcept
	{
		return a == b;
	}
	

	static bool lt(char_type a, char_type b) noexcept
	{
		return a < b;
	}


	static char_type* move(char_type* dest, const char_type* src, size_t count)
	{
		memmove(dest, src, count * sizeof(char_type));
		return dest;
	}


	static char_type* copy(char_type* dest, const char_type* src, size_t count)
	{
		memcpy(dest, src, count * sizeof(char_type));
		return dest;
	}


	static int compare(const char_type* s1, const char_type* s2, size_t count)
	{
		for (; count > 0; --count, ++s1, ++s2)
		{
			if (*s1 != *s2) 
			{
				return *s1 < *s2 ? -1 : 1;
			}
		}

		return 0;
	}


	static size_t length(const char_type* first)
	{
		size_t count = 0;
		while (*first != char_type()) //requires no-parameter constructor
		{
			++count;
			++first;
		}

		return count;
	}


	static const char_type* find(const char_type* first, size_t count, const char_type& ch)
	{
		for (; count > 0; --count, ++first)
		{
			if (*first == ch)
			{
				return first;
			}
		}

		return nullptr;
	}


	static char_type to_char_type(int_type v) noexcept
	{
		return static_cast<char_type>(v);
	}


	static int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(c);
	}


	static bool eq_int_type(int_type c1, int_type c2) noexcept
	{
		return c1 == c2;
	}


	static int_type eof() noexcept
	{
		return static_cast<int_type>(EOF);
	}


	static int_type not_eof(int_type e) noexcept
	{
		return e != eof() ? e : static_cast<int_type>(!eof());
	}

};

template<typename _CharType, typename _IntType>
class BasicWCharTraits
{
public:
	using char_type = _CharType;
	using int_type = _IntType;
	using pos_type = std::streampos;
	using off_type = std::streamoff;
	using state_type = _Mbstatet;
	using comparison_category = std::strong_ordering;

public:


	static void assign(char_type& left, const char_type& right) noexcept
	{
		left = right;
	}


	static char_type* assign(char_type* first, size_t count, char_type ch)
	{
		for (char_type* next = first; count > 0; --count, ++next)
		{
			*next = ch;
		}

		return first;
	}


	static bool eq(const char_type& a, const char_type& b) noexcept
	{
		return a == b;
	}


	static bool lt(char_type a, char_type b) noexcept
	{
		return a < b;
	}


	static char_type* move(char_type* dest, const char_type* src, size_t count)
	{
		memmove(dest, src, count * sizeof(char_type)); //TODO fix
		return dest;
	}


	static char_type* copy(char_type* dest, const char_type* src, size_t count)
	{
		memcpy(dest, src, count * sizeof(char_type)); //TODO fix
		return dest;
	}


	static int compare(const char_type* s1, const char_type* s2, size_t count)
	{
		for (; count > 0; --count, ++s1, ++s2)
		{
			if (*s1 != *s2)
			{
				return *s1 < *s2 ? -1 : 1;
			}
		}

		return 0;
	}


	static size_t length(const char_type* first)
	{
		size_t count = 0;
		while (*first != char_type()) //requires no-parameter constructor
		{
			++count;
			++first;
		}

		return count;
	}


	static const char_type* find(const char_type* first, size_t count, const char_type& ch)
	{
		for (; count > 0; --count, ++first)
		{
			if (*first == ch)
			{
				return first;
			}
		}

		return nullptr;
	}


	static char_type to_char_type(int_type v) noexcept
	{
		return static_cast<char_type>(v);
	}


	static int_type to_int_type(char_type c) noexcept
	{
		return static_cast<int_type>(c);
	}


	static bool eq_int_type(int_type c1, int_type c2) noexcept
	{
		return c1 == c2;
	}


	static int_type eof() noexcept
	{
		return static_cast<int_type>(WEOF);
	}


	static int_type not_eof(int_type e) noexcept
	{
		return e != eof() ? e : static_cast<int_type>(!eof());
	}

};

template<typename CharType>
class CharTraits : public BasicCharTraits<CharType, int> {};

template<>
class CharTraits<wchar_t> : public BasicWCharTraits<wchar_t, int> {};

ANY_END

#endif // !_CHAR_TRAITS_