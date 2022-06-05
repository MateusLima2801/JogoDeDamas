#ifndef CHECKERS_POSITION_H
#define CHECKERS_POSITION_H
#include "Global.h"
#include "Position.h"
#include <fstream>

using namespace std;

class CheckersPosition
{
    char column;
    int line;

    public:
        CheckersPosition(char column, int line)
        {
            this->column = column;
            this->line = line;
        }

        Position toPosition()
        {
            return Position(Dim - line, column - 'a');
        }

        friend ostream& operator<<(ostream &os, CheckersPosition pos);

};

ostream &operator<<(ostream &os, CheckersPosition pos)
{
    os << pos.column << pos.line;
    return os;
}

#endif