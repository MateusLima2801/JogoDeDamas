#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include ".\Board\Position.h"
#include ".\Checkers\CheckersPosition.h"
#include "Global.h"

using namespace std;

class Util
{
    public:

    static void ReadKey()
    {
        cout << "Press SPACE + ENTER for continue...";
        while (cin.get() != ' ');
    }

    static CheckersPosition toCheckersPosition(Position pos)
    {
        return CheckersPosition(pos.column+'a',Dim-pos.line);
    }
};

#endif