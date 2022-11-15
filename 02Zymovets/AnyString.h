#ifndef _ANYSTRING_ZYMOVETS_
#define _ANYSTRING_ZYMOVETS_
#include "CharTraits.h"
#include "Macros.h"
#include <memory>
#include <ostream>

ANY_BEGIN

template<typename CharType, typename CharTraits = CharTraits<CharType>>
class AnyString
{
public:
	using char_type = CharType;
	using char_�ref  = const char_type&;
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
	AnyString(const AnyString&);     //TODO check
	AnyString(AnyString&&) noexcept = default; //TODO check
	~AnyString();
public:
	AnyString& operator=(const AnyString&)&;     //TODO check
	AnyString& operator=(AnyString&&)& noexcept = default; //TODO check
	AnyString& operator+=(const AnyString&)&;
public:
	CharProxy  operator[](const size_type);
	char_�ref  operator[](const size_type) const;
	size_type  size()  const noexcept;
	bool empty() const noexcept;
	void clear();
	void check_at(const size_type) const;
	const char_type& read_at(const size_type) const;
	void write_at(char_�ref, const size_type);
private:
	data_ptr _data;
};

//bool operator==	(const String&, const String&);
//bool operator!=	(const String&, const String&);
//bool operator<	(const String&, const String&);
//bool operator>	(const String&, const String&);
//bool operator<=	(const String&, const String&);
//bool operator>=	(const String&, const String&);
//
//String operator+(const String&, const String&);

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

ANY_END

#include "AnyStringRealization.h"
#include "AnyStringData.h"
#endif // !_ANYSTRING_ZYMOVETS_