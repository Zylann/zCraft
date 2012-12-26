#ifndef STRINGUTILS_HPP_INCLUDED
#define STRINGUTILS_HPP_INCLUDED

namespace engine
{
    std::string toString(float x);
    std::string toString(double x);
    std::string toString(int x);
    std::string toString(unsigned int x);
    std::string toString(bool b);

    std::string toStringBin(unsigned int x, unsigned char n=32);
    std::string toStringAlnum(int x);

	int toInt(std::string s);
    void toUpper(std::string & str);

    // convert a time given in seconds to a time string formated like "hh:mm:ss:ms"
    std::string toTimeString(float s);

    bool isPrintableChar(char c);

    std::string cropStr(std::string str, char c);


} // namespace engine

#endif // STRINGUTILS_HPP_INCLUDED
