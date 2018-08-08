#include <gtest/gtest.h>
#include "sedump.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

TEST(SEDump, DumpSimpleStruct) {
    struct Hello {
        int a;
        bool b;
        unsigned int c;
        char d;
        double e[5];
    };
    {

        Hello h;
        h.a = 3;
        h.b = true;
        h.c = 5;
        h.d = '=';
        h.e[0] = 1.2;
        h.e[1] = 2.3;
        h.e[2] = 3.4;
        h.e[3] = 4.5;

        auto dumpString = SEDump::dump("int,bool,uint,char,double[4]", "a", h.a, "b", h.b, "c", h.c, "d", h.d, "e", h.e);

        EXPECT_EQ(
                "a: 3\nb: true\nc: 5\nd: =\ndouble[0]: 1.200000  double[1]: 2.300000  double[2]: 3.400000  double[3]: 4.500000  \n",
                dumpString);
}


    struct Hello2
    {
        int name;
        bool age;
        float e[4];
        unsigned int c;
        char d[3];
    };

    {
        Hello2 h;
        h.name = 3;
        h.age = true;
        h.c = 5;
        h.e[0] = 1.0f;
        h.e[1] = 3.0f;
        h.e[2] = 5.0f;
        h.e[3] = 7.0f;
        h.d[0] = 'a';
        h.d[1] = 'c';
        h.d[2] = 'f';

        auto dumpString2 = SEDump::dump("int,bool,float[4],uint,char[3]", "namelabel", h.name, "ageaaa", h.age,"e",h.e, "c", h.c, "d", h.d);

        cout << dumpString2;
    }
}

