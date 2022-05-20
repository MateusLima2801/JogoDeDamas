#include <iostream>

using namespace std;

namespace board{
    class Board{
        private:
            Piece[,] Pieces;

        public:
            int Lines; 
            int Columns;

            Board(int lines, int columns)
            {
                Lines = lines;
                Columns = columns;
                Pieces = new Piece[Lines, Columns];
            }

            public Peca peca(int linha, int coluna){
                return Pecas[linha, coluna];
            }

            public Peca peca(Posicao pos){
                return Pecas[pos.Linha, pos.Coluna];
            }

            public bool existePeca(Posicao pos){
                validarPosicao(pos);
                return peca(pos)!=null;
            }

            public void colocarPeca(Peca p, Posicao pos){
                if(existePeca(pos)){
                    throw new TabuleiroException("Já existe uma peça nessa posição!");
                }
                Pecas[pos.Linha, pos.Coluna] = p;
                p.Posicao = pos;
            }

            public Peca retirarPeca(Posicao pos){
                if(peca(pos) == null){
                    return null;
                }
                else{
                    Peca aux = peca(pos);
                    aux.Posicao = null;
                    Pecas[pos.Linha, pos.Coluna] = null;
                    return aux; //i have to return the piece because i am eliminating it from the code
                }
            }

            public bool posicaoValida(Posicao pos){
                if(pos.Linha < 0 || pos.Linha>=Linhas || pos.Coluna<0 || pos.Coluna>=Colunas)
                {
                    return false;
                }    
                return true;
            }

            public void validarPosicao(Posicao pos){
                if(!posicaoValida(pos)){
                    throw new TabuleiroException("Posição inválida!");
                }
            }
    };
}