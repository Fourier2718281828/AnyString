#ifndef _ANYSTRING_ZYMOVETS_
#define _ANYSTRING_ZYMOVETS_
#include "CharTraits.h"
#include "Macros.h"
#include <memory>
#include <ostream>
#include <string>

ANY_BEGIN

template<typename CharType, typename CharTraits = CharTraits<CharType> >
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
private:
	AnyString(data_ptr&&);
	void check_at(const size_type) const;
	const char_type& read_at(const size_type) const;
	void write_at(char_ñref, const size_type);
public:
	AnyString();
	AnyString(std::nullptr_t) = delete;
	AnyString(const char_type);
	AnyString(const char_type* const);
	AnyString(const AnyString&);
	AnyString(AnyString&&) noexcept;
	~AnyString();

	template<typename OtherTraits, typename Alloc, typename = 
		std::enable_if_t<!std::is_array_v<char_type> && 
		std::is_trivial_v<char_type>                 && 
		std::is_standard_layout_v<char_type>>
		>
	AnyString(const std::basic_string<char_type, OtherTraits, Alloc>&);
public:
	AnyString& operator=(const AnyString&)&;
	AnyString& operator=(AnyString&&)& noexcept;
	AnyString& operator+=(const AnyString&)&;
public:
	char_ñref  operator[](const size_type)&&;
	CharProxy  operator[](const size_type)&;
	char_ñref  operator[](const size_type) const&;
	size_type  size()  const noexcept;
	bool empty() const noexcept;
	void clear();
	bool is_shareable() const;
	int compare(const AnyString&) const;
	size_type ref_counter() const;
private:
	data_ptr _data;

public:

	friend inline bool operator==(const AnyString& a, const AnyString& b)
	{
		using size_type = AnyString<CharType, CharTraits>::size_type;
		if (a.size() != b.size()) return false;

		for (size_type i = 0u; i < a.size(); ++i)
		{
			if (a[i] != b[i]) return false;
		}

		return true;
	}

	friend inline typename char_traits::comparison_category operator<=> (const AnyString& a, const AnyString& b)
	{
		return static_cast<typename char_traits::comparison_category>(a.compare(b) <=> 0);
	}

	friend inline AnyString operator+ (const AnyString& a, const AnyString& b)
	{
		using allocate_tag = typename string_data::AllocateOnly_tag;
		size_type size = a.size() + b.size();
		data_ptr res = std::make_shared<string_data>(size, allocate_tag{});
		res->construct_range(res->chars(), a._data->chars(), a.size());
		res->construct_range(res->chars() + a.size(), b._data->chars(), b.size());
		return AnyString(std::move(res));
	}

};

template<typename CharType, typename CharTraits>
std::ostream& operator<<(std::ostream& o, const AnyString<CharType, CharTraits>& str)
{
	using size_type = AnyString<CharType, CharTraits>::size_type;
	for (size_type i = 0u; i < str.size(); ++i)
	{
		o << str[i];
	}

	return o;
}

template<typename CharType, typename CharTraits>
std::wostream& operator<<(std::wostream& o, const AnyString<CharType, CharTraits>& str)
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
#include "Typedefs.h"
#endif // !_ANYSTRING_ZYMOVETS_