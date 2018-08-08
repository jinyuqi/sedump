//
// Author: Jin Yuqi (Ricky)
// Email: 179386223@qq.com
// Date: 2018.08.08
//

#include <algorithm>
#include "sedump.h"
#include <cstdarg>
#include <sstream>

using namespace std;

string SEDump::dumpString(string format, ...)
{
    vector<string> resString;

    auto dotcount = std::count(format.begin(), format.end(), ',');
    auto paramCount = (dotcount + 1) * 2;

    va_list list;
    va_start(list, format);

    resString = dumpStringList(format, list);

    va_end(list);

    return vec2string(resString);
}


std::vector<std::string> SEDump::dumpStringList(std::string format, ...)
{
    vector<string> resStringList;

    auto dotcount = std::count(format.begin(), format.end(), ',');
    auto paramCount = (dotcount + 1) * 2;

    va_list list;
    va_start(list, format);

    resStringList = dumpStringList(format, list);

    va_end(list);

    return resStringList;
}



std::vector<std::string> SEDump::dumpStringList(std::string format, va_list list)
{
    vector<string> resString;

    auto dotcount = std::count(format.begin(), format.end(), ',');
    auto paramCount = (dotcount + 1) * 2;

    vector<string> tokens;
    splitTokensFromString(tokens, format, ',');

    string currentCategory;

    for (int i = 0; i < paramCount; ++i)
    {
        auto curType = tokens[i / 2];
        if ( i % 2 == 0)
        {
            currentCategory = va_arg(list, char *);
            continue;
        }

        if (IsArrayType(curType))
        {
            string curVal;

            string numberString = curType.substr(curType.find('[') + 1, curType.find(']') - curType.find('[') - 1);
            int count = stoi(numberString);

            string type = curType.substr(0, curType.find('['));
            auto value = va_arg(list, int *);

            vector<string> vec;
            for (int j = 0; j < count; ++j)
            {

                if (type == "int" && i % 2 != 0)
                {
                    int *p = (int *)value;
                    vec.push_back(std::to_string(p[j]));
                }
                else if (type == "double" && i % 2 != 0)
                {
                    double *p = (double *)value;
                    vec.push_back(std::to_string(p[j]));
                }
                else if (type == "float" && i % 2 != 0)
                {
                    float *p = (float *)value;
                    vec.push_back(std::to_string(p[j]));
                }
                else if (type == "uint" && i % 2 != 0)
                {
                    unsigned int *p = (unsigned int *)value;
                    vec.push_back(std::to_string(p[j]));
                }
                else if (type == "bool" && i % 2 != 0)
                {
                    bool *p = (bool *)value;
                    if (p[j] > 0)
                    {
                        curVal = "true";
                    }
                    else
                    {
                        curVal = "false";
                    }

                    vec.push_back(curVal);
                }
                else if (type == "BOOL" && i % 2 != 0)
                {
                    int *p = (int *)value;
                    if (p[j] > 0)
                    {
                        curVal = "true";
                    }
                    else
                    {
                        curVal = "false";
                    }

                    vec.push_back(curVal);
                }
                else if (type == "char" && i % 2 != 0)
                {
                    char *p = (char *)value;
                    char cValue = p[j];
                    curVal = string() + cValue;

                    vec.push_back(curVal);
                }
            }

            string tempRes = generateArrayString(currentCategory, vec);
            resString.push_back(tempRes);
        }
        else
        {
            string curVal;
            if (curType == "int" && i % 2 != 0)
            {
                auto value = va_arg(list, int);
                curVal = std::to_string(value);
            }
            else if (curType == "double" && i % 2 != 0)
            {
                auto value = va_arg(list, double);
                curVal = std::to_string(value);
            }
            else if (curType == "float" && i % 2 != 0)
            {
                auto value = va_arg(list, double);
                curVal = std::to_string(value);
            }
            else if (curType == "uint" && i % 2 != 0)
            {
                auto value = va_arg(list, unsigned int);
                curVal = std::to_string(value);
            }
            else if (curType == "bool" && i % 2 != 0)
            {
                auto value = va_arg(list, int);
                if (value > 0)
                {
                    curVal = "true";
                }
                else
                {
                    curVal = "false";
                }
            }
            else if (curType == "BOOL" && i % 2 != 0)
            {
                auto value = va_arg(list, int);
                if (value > 0)
                {
                    curVal = "true";
                }
                else
                {
                    curVal = "false";
                }
            }
            else if (curType == "char" && i % 2 != 0)
            {
                auto value = va_arg(list, int);
                char cValue = char(value);
                curVal = string() + cValue;
            }

            string tempRes = currentCategory + ":" + curVal;
            resString.push_back(tempRes);
        }
    }

    return resString;
}


void SEDump::splitTokensFromString(std::vector<string> &tokens, const std::string &format, char c)
{
    istringstream f(format);
    string s;
    while (getline(f, s, c))
    {
        tokens.push_back(s);
    }
}

bool SEDump::IsArrayType(const string &str)
{
    return (str.find('[') != string::npos && str.find(']') != string::npos);
}

string SEDump::generateArrayString(const std::string &type, const std::vector<std::string> &vec)
{
    string res;

    int i = 0;
    for (auto it : vec)
    {
        res += type + "[" + std::to_string(i++) + "]" + ":" + it + ";";
    }

    return res;
}

string SEDump::vec2string(const std::vector<std::string> &vec)
{
    string res;

    for (auto it : vec)
    {
        res += it + "\n";
    }

    return res;
}
