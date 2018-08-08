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

        auto dumpStringList = SEDump::dumpStringList("int,bool,uint,char,double[4]", "a", h.a, "b", h.b, "c", h.c, "d", h.d, "e", h.e);
        vector<string> ivec;
        ivec.push_back("a:3");
        ivec.push_back("b:true");
        ivec.push_back("c:5");
        ivec.push_back("d:=");
        ivec.push_back("e[0]:1.200000;e[1]:2.300000;e[2]:3.400000;e[3]:4.500000;");
        EXPECT_EQ(ivec, dumpStringList);
    }


    struct Hello2
    {
        int a;
        bool b;
        float c[4];
        unsigned int d;
        char e[3];
    };

    {
        Hello2 h;
        h.a = 3;
        h.b = true;
        h.c[0] = 1;
        h.c[1] = 2;
        h.c[2] = 3;
        h.c[3] = 4;
        h.d = 5;
        h.e[0] = 'c';
        h.e[1] = 'd';
        h.e[2] = 'e';

        auto dumpStringList = SEDump::dumpStringList("int,bool,float[4],uint,char[3]", "a", h.a, "b", h.b,"c",h.c, "d", h.d, "e", h.e);
        vector<string> ivec;
        ivec.push_back("a:3");
        ivec.push_back("b:true");
        ivec.push_back("c[0]:1.000000;c[1]:2.000000;c[2]:3.000000;c[3]:4.000000;");
        ivec.push_back("d:5");
        ivec.push_back("e[0]:c;e[1]:d;e[2]:e;");
        EXPECT_EQ(ivec, dumpStringList);
    }

    class Test {
    public:
        int hello[3];
    };

    {
        Test t;
        t.hello[0] = 3;
        t.hello[1] = 2;
        t.hello[2] = 1;

        auto dumpStringList = SEDump::dumpStringList("int[3]", "hello", t.hello);
        vector<string> ivec;
        ivec.push_back("hello[0]:3;hello[1]:2;hello[2]:1;");
        EXPECT_EQ(ivec, dumpStringList);
    }


    class Test2 {
    public:
        char a;
        int hello[2];
        double c;
    };

    {
        Test2 t;
        t.a = '+';
        t.hello[0] = 3;
        t.hello[1] = 2;
        t.c = 3;

        auto dumpStringList = SEDump::dumpStringList("char,int[2],double", "a", t.a, "hello", t.hello, "c", t.c);
        vector<string> ivec;
        ivec.push_back("a:+");
        ivec.push_back("hello[0]:3;hello[1]:2;");
        ivec.push_back("c:3.000000");
        EXPECT_EQ(ivec, dumpStringList);


    }
    class Test3 {
    public:
        bool a[2];
    };

    {
        Test3 t;
        t.a[0] = false;
        t.a[1] = true;

        auto dumpStringList = SEDump::dumpStringList("bool[2]", "a", t.a);
        vector<string> ivec;
        ivec.push_back("a[0]:false;a[1]:true;");
        EXPECT_EQ(ivec, dumpStringList);
    }

    class Test4
    {
    public:
        int a;
    };
    {
        Test4 t;
        t.a = 15;

        auto dumpStringList = SEDump::dumpStringList("int", "a", t.a);
        vector<string> ivec;
        ivec.push_back("a:15");
        EXPECT_EQ(ivec, dumpStringList);
    }

}

