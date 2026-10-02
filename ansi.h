#pragma once
#include <string>

class ANSI 
{
public:
	static std::string reset() { return "\033[0m"; }
	static std::string red() { return "\033[31m"; }
	static std::string green() { return "\033[32m"; }
	static std::string yellow() { return "\033[33m"; }
	static std::string blue() { return "\033[34m"; }
	static std::string magenta() { return "\033[35m"; }
	static std::string cyan() { return "\033[36m"; }
	static std::string white() { return "\033[37m"; }
	static std::string bold() { return "\033[1m"; }
	static std::string underline() { return "\033[4m"; }
	static std::string purple() { return "\033[35m"; }
	static std::string black() { return "\033[30m"; }
	static std::string grey() { return "\033[90m"; }
	static std::string orange() { return "\033[38;5;208m"; }
	static std::string lightBlue() { return "\033[94m"; }
	static std::string lightGreen() { return "\033[92m"; }
	static std::string lightRed() { return "\033[91m"; }
	static std::string lightYellow() { return "\033[93m"; }
	static std::string lightMagenta() { return "\033[95m"; }
	static std::string lightCyan() { return "\033[96m"; }

    static std::string backgroundReset() { return "\033[49m"; }
    static std::string backgroundRed() { return "\033[41m"; }
    static std::string backgroundGreen() { return "\033[42m"; }
    static std::string backgroundYellow() { return "\033[43m"; }
    static std::string backgroundBlue() { return "\033[44m"; }
    static std::string backgroundMagenta() { return "\033[45m"; }
    static std::string backgroundCyan() { return "\033[46m"; }
    static std::string backgroundWhite() { return "\033[47m"; }
    static std::string backgroundBlack() { return "\033[40m"; }
    static std::string backgroundGrey() { return "\033[100m"; }
    static std::string backgroundLightRed() { return "\033[101m"; }
    static std::string backgroundLightGreen() { return "\033[102m"; }
    static std::string backgroundLightYellow() { return "\033[103m"; }
    static std::string backgroundLightBlue() { return "\033[104m"; }
    static std::string backgroundLightMagenta() { return "\033[105m"; }
    static std::string backgroundLightCyan() { return "\033[106m"; }
    static std::string backgroundLightWhite() { return "\033[107m"; }
    static std::string backgroundLightBlack() { return "\033[100m"; }
    static std::string backgroundLightGrey() { return "\033[47m"; }


	static std::string carriageReturn() { return "\033[1G"; }
	static std::string eraseLine() { return "\033[2K"; }
	static std::string eraseLineAndCarriageReturn() { return "\033[2K\033[1G"; }
};
