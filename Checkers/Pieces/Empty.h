#ifndef EMPTY_H
#define EMPTY_H
#include "..\..\Board\Piece.h"
#include "..\..\Board\Board.h"
#include "..\..\Board\Color.h"
#include "..\..\Board\Position.h"
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

class Empty : public  Piece
{
public:
    Empty() : Piece(emptyColor)
    {
        symbol = " ";
        wsymbol = L" ";
    }

    virtual vector<vector<bool>> possibleMoves()
    {
        return vector<vector<bool>>();
    }
};

#endif