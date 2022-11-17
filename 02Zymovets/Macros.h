#ifndef _MACROS_ANYSTRING_
#define _MACROS_ANYSTRING_

#define ANY_MEMBER                               \
template<typename CharType, typename BasicCharTraits> \
inline AnyString<CharType, BasicCharTraits> ::      

#define DATA_MEMBER                                      \
template<typename CharType, typename BasicCharTraits>         \
inline AnyString<CharType, BasicCharTraits> :: string_data ::  

#define PROXY_MEMBER                                     \
template<typename CharType, typename BasicCharTraits>         \
inline AnyString<CharType, BasicCharTraits> :: CharProxy :: 

#define ANY_METHOD                               \
template<typename CharType, typename BasicCharTraits> \
inline auto AnyString<CharType, BasicCharTraits> ::      

#define DATA_METHOD                                            \
template<typename CharType, typename BasicCharTraits>               \
inline auto AnyString<CharType, BasicCharTraits> :: string_data ::  

#define PROXY_METHOD                                           \
template<typename CharType, typename BasicCharTraits>               \
inline auto AnyString<CharType, BasicCharTraits> :: CharProxy :: 

#define ANY_BEGIN namespace Zymovets02_AnyString {
#define ANY_END   }

#define PRINT(message) _STD cout << message << '\n';

#ifndef NDEBUG
#include <iostream>
#endif // !NDEBUG

#endif // !_MACROS_ANYSTRING_