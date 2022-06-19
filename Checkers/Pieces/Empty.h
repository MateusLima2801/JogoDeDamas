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
    Empty() : Piece(emptyColor){}

    vector<vector<bool>> possibleMoves() override
    {
        vector<vector<bool>> matrix;
        for (int i = 0; i < Dim; i++)
        {
            vector<bool> aux(Dim, false);
            matrix.push_back(aux);
        }
        return matrix;
    }

    friend ostream &operator<<(ostream &os, Empty empty);
};

#endif