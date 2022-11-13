#ifndef _ANYSTRING_ZYMOVETS_
#define _ANYSTRING_ZYMOVETS_
#include <memory>

template<typename CharType, typename CharTraits = int>
class AnyString
{
public:
	using char_type = CharType;
	using char_traits = CharTraits;
private:
	struct string_data;
private:
	using data_ptr = std::shared_ptr<string_data>;
public:
private:
	data_ptr _data;
};

template<typename CharType, typename CharTraits>
class AnyString<CharType, CharTraits>::string_data
{

};

#endif // !_ANYSTRING_ZYMOVETS_