#ifndef POSITION_H
#define POSITION_H
#include <fstream>
#include <iostream>
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

    Position operator+(Position& pos)
    {
        return Position(line+pos.line, column+ pos.column);
    }

    Position operator-(Position &pos)
    {
        return Position(line - pos.line, column - pos.column);
    }

    Position operator/(int d)
    {
        return Position(line/d, column/d);
    }

    bool operator==(Position &pos)
    {
        return line == pos.line && column == pos.column;
    }

    bool operator!=(Position &pos)
    {
        return line != pos.line || column != pos.column;
    }

    friend ostream &operator<<(ostream &os, Position &pos);
};

ostream &operator<<(ostream &os, Position &pos)
{
    os << pos.line << ", " << pos.column;

    return os;
}

#endif