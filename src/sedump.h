//
// Author: Jin Yuqi (Ricky)
// Email: 179386223@qq.com
// Date: 2018.08.08
//

#ifndef __SEDUMP__
#define __SEDUMP__

#include <string>
#include <vector>

class SEDump
{
public:
    static std::string dumpString(std::string, ...);
    static std::vector<std::string> dumpStringList(std::string, ...);
    static void splitTokensFromString(std::vector<std::string> &tokens, const std::string &format, char c) ;
    static bool IsArrayType(const std::string &str);
    static std::string generateArrayString(const std::string &type, const std::vector<std::string> &vec);
    static std::string vec2string(const std::vector<std::string> &vector);
private:
    static std::vector<std::string> dumpStringList(std::string, va_list list);
};

#endif
