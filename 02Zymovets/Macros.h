#ifndef _MACROS_ANYSTRING_
#define _MACROS_ANYSTRING_

#define ANY_MEMBER                               \
template<typename CharType, typename CharTraits> \
inline AnyString<CharType, CharTraits> ::      

#define DATA_MEMBER                                      \
template<typename CharType, typename CharTraits>         \
inline AnyString<CharType, CharTraits> :: string_data ::  

#define PROXY_MEMBER                                     \
template<typename CharType, typename CharTraits>         \
inline AnyString<CharType, CharTraits> :: CharProxy :: 

#define ANY_METHOD                               \
template<typename CharType, typename CharTraits> \
inline auto AnyString<CharType, CharTraits> ::      

#define DATA_METHOD                                            \
template<typename CharType, typename CharTraits>               \
inline auto AnyString<CharType, CharTraits> :: string_data ::  

#define PROXY_METHOD                                            \
template<typename CharType, typename CharTraits>               \
inline auto AnyString<CharType, CharTraits> :: CharProxy :: 

#define ANY_BEGIN namespace Zymovets02_AnyString {
#define ANY_END   }

#endif // !_MACROS_ANYSTRING_