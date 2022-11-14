#ifndef _ANY_STRING_PROXY_
#define _ANY_STRING_PROXY_
#include "AnyString.h"
#include "AnyStringData.h"
#include "AnyStringRealization.h"
#include <ostream>

template<typename CharType, typename CharTraits>
class AnyString<CharType, CharTraits>::CharProxy
{
public:
	friend AnyString<CharType, CharTraits>;
public:

	/*
	* There's no other way to define operator<<
	* as the compiler merely cannot deduce the
	* appropriate type to instantiate the template,
	* provided Proxy is a nested class (nested within template AnyString) 
	*/

	friend std::ostream& operator<<(std::ostream& o, const CharProxy& proxy) 
	{
		return o << static_cast<const char_type&>(proxy);
	}

public:
	using char_type = AnyString::char_type;
	using char_ñref = AnyString::char_ñref;
	using char_traits = AnyString::char_traits;
	using size_type = AnyString::size_type;
public:
	~CharProxy() = default;
private:
	CharProxy(AnyString&, const size_type);
public:
	const char_type* operator&() const;
	char_type* operator&();
	operator char_type() const;
	operator char_type& ();
	operator const char_type& () const;
	CharProxy& operator=(char_ñref c);
private:
	void get_infected();
private:
	AnyString<char_type, char_traits>& _proxyship;
	const size_type _index;
};


template<typename CharType, typename CharTraits>
AnyString<CharType, CharTraits>::CharProxy::CharProxy(AnyString& str, const size_type index) :
	_proxyship(str),
	_index(index)
{
}

template<typename CharType, typename CharTraits>
inline auto AnyString<CharType, CharTraits>::CharProxy::operator&() const -> const char_type*
{
	return &_proxyship->_data->chars()[_index];
}

template<typename CharType, typename CharTraits>
inline auto AnyString<CharType, CharTraits>::CharProxy::operator&() -> char_type*
{
	get_infected();
	return &_proxyship->_data->chars()[_index];
}

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::CharProxy::operator char_type() const
{
	return _proxyship.read_at(_index);
}

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::CharProxy::operator char_type& ()
{
	get_infected();
	return _proxyship._data->chars()[_index];
}

template<typename CharType, typename CharTraits>
inline AnyString<CharType, CharTraits>::CharProxy::operator const char_type& () const
{
	return _proxyship.read_at(_index);
}

template<typename CharType, typename CharTraits>
inline auto AnyString<CharType, CharTraits>::CharProxy::operator=(char_ñref c) -> CharProxy&
{
	_proxyship.write_at(c, _index);
	return *this;
}


template<typename CharType, typename CharTraits>
inline void AnyString<CharType, CharTraits>::CharProxy::get_infected()
{
	if (_proxyship._data->isShareable() && _proxyship._data.use_count() > 1)
		_proxyship._data = std::make_shared<string_data>(_proxyship._data->chars(), _proxyship._data->size());
	_proxyship._data->setShareable(false);
}

//template<typename CharType, typename CharTraits>
//std::ostream& operator<<(std::ostream& o, const typename AnyString<CharType, CharTraits>::CharProxy& proxy)
//{
//	using char_cref = typename AnyString<CharType, CharTraits>::CharProxy::char_cref;
//	return o << static_cast<char_cref>(proxy); //Why used (char&) but not (const char&) cast?
//}
#endif // !_ANY_STRING_PROXY_