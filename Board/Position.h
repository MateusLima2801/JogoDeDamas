#ifndef POSITION_H
#define POSITION_H
#include <fstream>
#include <iostream>

using namespace std;

class Position
{

public:
    int line;
    int column;

    Position(){}

    Position(int line, int column)
    {
        this->line = line;
        this->column = column;
    }

    void setPosition(int line, int column)
    {
        this->line = line;
        this->column = column;
    }

    void setPosition(Position pos)
    {
        this->line = pos.line;
        this->column = pos.column;
    }

    friend ostream &operator<<(ostream &os, Position &pos);
};

ostream &operator<<(ostream &os, Position &pos)
{
    os << pos.line << ", " << pos.column;

    return os;
}

#endif