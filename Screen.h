#ifndef SCREEN_H
#define SCREEN_H
#include ".\Board\Board.h"
#include ".\Board\Piece.h"
#include ".\Board\Color.h"
#include ".\Board\Position.h"
#include "Global.h"
#include ".\Checkers\CheckersMatch.h"
#include ".\Checkers\CheckersPosition.h"
#include ".\Checkers\Pieces\Checker.h"
#include <io.h>
#include <fcntl.h>

using namespace std;

class Screen{
    public:
        void static printMatch(CheckersMatch match)
        {
            printBoard(match.board);
            cout <<"Turn: " << match.turn << endl;

        }

        void static printHeader()
        {
            cout << "*****************************" << endl;
            cout << "******  CHECKERS GAME  ******" << endl;
            cout << "*****************************" << endl;
            cout << "***                       ***" << endl;
        }

        void static printBoard(Board board)
        {
            printHeader();
            for(int i = 0; i<Dim; i++)
            {
                cout << (Dim -i) << " ";
                for(int j = 0; j <Dim; j++)
                {
                    SetConsole(board,Position(i,j));
                    //what is the problem?
                    Piece p = board.piece(i, j);
                    //Piece p = Checker(white, board, white);
                    //string c=p.symbol;
                    cout << " " << p << " ";
                    ResetConsole();
                }
                cout << endl;
            }
            cout << "   a  b  c  d  e  f  g  h"<< endl;
        }

        void static printBoard(Board board, vector<vector<bool>> possiblePositions)
        {
            printHeader();
            for (int i = 0; i < Dim; i++)
            {
                cout << (Dim - i) << " ";
                for (int j = 0; j < Dim; j++)
                {
                    if(possiblePositions[i][j])
                    {
                        SetConsoleEspecial();
                    }
                    else SetConsole(board, Position(i, j));
                    // what is the problem?
                    Piece p = board.piece(i, j);
                    cout << p;
                    ResetConsole();
                }
                cout << endl;
            }
            cout << "   a  b  c  d  e  f  g  h"<< endl;
        }

        static CheckersPosition readCheckersPosition()
        {
            string s;
            cin >> s;
            char column = s[0];
            int line = s[1]-'0';

            return CheckersPosition(column, line);
        }

        static void SetConsole(Board board, Position pos)
        {
            SetBackground(pos);
            SetForeground(board, pos);
        }

        static void SetBackground(Position pos)
        {
            if((pos.line + pos.column)%2 == 0) cout << "\u001b[48;5;255m";
            else cout << "\u001b[48;5;245m";
        }

        static void SetForeground(Board board, Position pos)
        {
            if(board.piece(pos).getColor() == white) cout << "\u001b[38;5;196m";
            else if(board.piece(pos).getColor() == black) cout << "\u001b[38;5;0m";
        }

        static void SetConsoleEspecial()
        {
            //background configuration
            cout << "\u001b[48;5;228m";
        }

        static void ResetConsole()
        {
            cout << "\u001b[0m";
        }

};

#endif