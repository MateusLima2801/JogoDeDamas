#ifndef PIECE_H
#define PIECE_H
#include "Color.h";
#include "Position.h"
#include "Board.h"

class Piece
{
protected:
    Color color;
    Position position;
    int amtOfMoves;

public:
    Piece()
    {
        position = Position(-1, -1);
    }

    bool isEmpty()
    {
        if (color == emptyColor)
            return true;
        else
            return false;
    }

    void setEmpty()
    {
        color = emptyColor;
    }

    void setPosition(Position pos)
    {
        position.setPosition(pos);
    }
};

#endif