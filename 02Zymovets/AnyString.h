#ifndef _ANYSTRING_ZYMOVETS_
#define _ANYSTRING_ZYMOVETS_
#include "CharTraits.h"
#include "Macros.h"
#include <memory>
#include <ostream>

ANY_BEGIN

template<typename CharType, typename CharTraits = CharTraits<CharType, int>>
class AnyString
{
public:
	using char_type = CharType;
	using char_ñref  = const char_type&;
	using char_traits = CharTraits;
	using size_type = size_t;
public:
	static_assert(std::is_same_v<char_type, typename char_traits::char_type>, 
		"String char_type and CharTraits char_type must match");
private:
	class string_data;
public:
	class CharProxy;
	class BadAnyString;
private:
	using data_ptr = std::shared_ptr<string_data>;
public:
	AnyString();
	AnyString(std::nullptr_t) = delete;
	AnyString(const char_type);
	AnyString(const char_type* const);
	AnyString(const AnyString&);
	AnyString(AnyString&&) noexcept;
	~AnyString();
public:
	AnyString& operator=(const AnyString&)&;
	AnyString& operator=(AnyString&&)& noexcept;
	AnyString& operator+=(const AnyString&)&;
public:
	CharProxy  operator[](const size_type);
	char_ñref  operator[](const size_type) const;
	size_type  size()  const noexcept;
	bool empty() const noexcept;
	void clear();
	void check_at(const size_type) const;
	const char_type& read_at(const size_type) const;
	void write_at(char_ñref, const size_type);
	bool is_shareable() const;
	size_type ref_counter() const;

private:
	data_ptr _data;
public:
	friend inline bool operator==(const AnyString<CharType, CharTraits>& a, const AnyString<CharType, CharTraits>& b)
	{
		using size_type = AnyString<CharType, CharTraits>::size_type;
		if (a.size() != b.size()) return false;

		for (size_type i = 0u; i < a.size(); ++i)
		{
			if (a[i] != b[i]) return false;
		}

		return true;
	}

	friend inline bool operator!=(const AnyString& a, const AnyString& b)
	{
		return !(a == b);
	}

	friend inline bool operator<(const AnyString& a, const AnyString& b)
	{
		using size_type = AnyString<CharType, CharTraits>::size_type;
		for (size_type i = 0; i < std::min(a.size(), b.size()); ++i)
		{
			if (a[i] != b[i])
			{
				return a[i] < b[i];
			}
		}

		return a.size() < b.size();
	}

	friend inline bool operator>(const AnyString& a, const AnyString& b)
	{
		return b < a;
	}

	friend inline bool operator<=(const AnyString& a, const AnyString& b)
	{
		return !(b < a);
	}

	friend inline bool operator>=(const AnyString& a, const AnyString& b)
	{
		return !(a < b);
	}

	friend inline AnyString operator+ (const AnyString& a,const AnyString& b)
	{
		using char_type = AnyString<CharType, CharTraits>::char_type;
		using size_type = AnyString<CharType, CharTraits>::size_type;

		size_type size = a.size() + b.size();
		char_type* res = new char_type[size + 1];
		for (size_type i = 0u; i < size; ++i)
		{
			res[i] = i < a.size()
				? a[i]
				: b[i - a.size()];
		}

		res[size] = 0; // TODO make more reusable (not using 0)

		return res;
	}
};

template<typename CharType, typename CharTraits>
std::ostream&
operator<<(std::ostream& o, const AnyString<CharType, CharTraits>& str)
{
	using size_type = AnyString<CharType, CharTraits>::size_type;
	for (size_type i = 0u; i < str.size(); ++i)
	{
		o << str[i];
	}

	return o;
}

//template<typename CharType, typename CharTraits>
//std::basic_ostream<CharType, CharTraits>& 
//operator<<(std::basic_ostream<CharType, CharTraits>& o, const AnyString<CharType, CharTraits>& str)
//{
//	using size_type = AnyString<CharType, CharTraits>::size_type;
//	for (size_type i = 0u; i < str.size(); ++i)
//	{
//		o << str[i];
//	}
//
//	return o;
//}

ANY_END

#include "AnyStringRealization.h"
#include "AnyStringData.h"
#endif // !_ANYSTRING_ZYMOVETS_