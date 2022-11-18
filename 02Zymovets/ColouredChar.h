#ifndef _COLOURED_CHAR_
#define _COLOURED_CHAR_
#include <ostream>
#include <windows.h>


class ColouredChar
{
public:
	enum class Color 
	{
		Black, DarkBlue, Green, 
		Blue, Red, DarkPurple, 
		DarkYellow, Gray, DarkGray, 
		LightBlue, LightGreen, Turquoise,
		Pink, Purple, Yellow, White
	};
public:
	ColouredChar(const char ch = '\0', const Color color = Color::White, const Color backColor = Color::Black);
	ColouredChar(const ColouredChar&) = default;
	~ColouredChar() = default;
public:
	ColouredChar& operator= (const ColouredChar&)& = default;
	//auto operator<=>(const ColouredChar&) const = default;
public:
	operator int() const;
	char& value();
	char  value() const;
	char& color();
	char  color() const;
	char& back_color();
	char  back_color() const;
private:
	char _char;
	char _color;
	char _backColor;
};

inline ColouredChar::ColouredChar(const char ch, const Color color, const Color backColor) :
	_char(ch),
	_color(static_cast<char>(color)),
	_backColor(static_cast<char>(backColor))
{
}

inline ColouredChar::operator int() const
{
	return _char;
}

inline char& ColouredChar::value()
{
	return _char;
}

inline char ColouredChar::value() const
{
	return _char;
}

inline char& ColouredChar::color()
{
	return _color;
}

inline char ColouredChar::color() const
{
	return _color;
}

inline char& ColouredChar::back_color()
{
	return _backColor;
}

inline char ColouredChar::back_color() const
{
	return _backColor;
}

std::ostream& operator<< (std::ostream& o, const ColouredChar& ch)
{
	using Color = ColouredChar::Color;
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//high 4 bits - background, low 4 bits - text 
	SetConsoleTextAttribute(hConsole, (ch.back_color() << 4) | ch.color());
	o << ch.value();
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(Color::White));
	return o;
}

bool operator==(const ColouredChar& c1, const ColouredChar& c2)
{
	return c1.value() == c2.value();
}

ColouredChar* fill(const char* chrs, const size_t len, const ColouredChar::Color color)
{
	ColouredChar* res = new ColouredChar[len + 1];
	for (size_t i = 0u; i < len; ++i)
	{
		res[i] = ColouredChar(chrs[i], color);
	}
	res[len] = ColouredChar('\0', color);
	return res;
}

ColouredChar* operator"" _black(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Black);
}

ColouredChar* operator"" _dblue(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::DarkBlue);
}

ColouredChar* operator"" _green(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Green);
}

ColouredChar* operator"" _blue(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Blue);
}

ColouredChar* operator"" _red(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Red);
}


ColouredChar* operator"" _dpurple(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::DarkPurple);
}

ColouredChar* operator"" _dyellow(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::DarkYellow);
}

ColouredChar* operator"" _gray(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Gray);
}


ColouredChar* operator"" _dgray(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::DarkGray);
}

ColouredChar* operator"" _lblue(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::LightBlue);
}

ColouredChar* operator"" _lgreen(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::LightGreen);
}

ColouredChar* operator"" _turq(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Turquoise);
}

ColouredChar* operator"" _pink(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Pink);
}

ColouredChar* operator"" _purple(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Purple);
}

ColouredChar* operator"" _yellow(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::Yellow);
}

ColouredChar* operator"" _white(const char* chrs, size_t len)
{
	using Color = ColouredChar::Color;
	return fill(chrs, len, Color::White);
}

//chars

ColouredChar operator"" _black(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Black);
}

ColouredChar operator"" _dblue(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::DarkBlue);
}

ColouredChar operator"" _green(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Green);
}

ColouredChar operator"" _blue(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Blue);
}

ColouredChar operator"" _red(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Red);
}


ColouredChar operator"" _dpurple(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::DarkPurple);
}

ColouredChar operator"" _dyellow(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::DarkYellow);
}

ColouredChar operator"" _gray(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Gray);
}


ColouredChar operator"" _dgray(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::DarkGray);
}

ColouredChar operator"" _lblue(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::LightBlue);
}

ColouredChar operator"" _lgreen(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::LightGreen);
}

ColouredChar operator"" _turq(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Turquoise);
}

ColouredChar operator"" _pink(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Pink);
}

ColouredChar operator"" _purple(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Purple);
}

ColouredChar operator"" _yellow(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::Yellow);
}

ColouredChar operator"" _white(const char chrs)
{
	using Color = ColouredChar::Color;
	return ColouredChar(chrs, Color::White);
}
#endif // !_COLOURED_CHAR_