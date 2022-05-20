namespace board{
    abstract class Piece{
        public Position Position {get; set;}
        public Color Color {get; protected set;}
        public int MovesQty {get; protected set;}
        public Board Tab {get; protected set;}

        public Piece(Color color, Board tab)
        {
            Position = null;
            Color = color;
            MovesQty = 0;
            Tab = tab;
        }


        protected bool canMove(Position pos){
            Piece p = Tab.Piece(pos);
            return p == null || p.Color != Color;
        }

        public bool thereIsPossibleMoves(){
            bool[,] mat = PossibleMoves();
            for(int i = 0; i < Tab.Lines; i++){
                for(int j = 0; j < Tab.Columns; j++){
                    if( mat[i,j] ){
                        return true;
                    }
                }
            }
            return false;
        }
        
        public abstract bool[,] movimentosPossiveis();

        public void incrementarQtdMovimentos(){
            QtdMovimentos ++;
        }

        public void decrementarQtdMovimentos(){
            QtdMovimentos --;
        }
        
        public bool podeMoverPara(Posicao pos){
            return movimentosPossiveis()[pos.Linha, pos.Coluna];
        }

    }
}