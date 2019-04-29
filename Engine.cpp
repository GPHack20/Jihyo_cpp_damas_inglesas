#include "Engine.h"

//Points for the board
Point::Point(int xx,int yy){
    x=xx;
    y=yy;
}

//Move class
Move::Move(){

}
Move::Move(int x, int y, int xx, int yy)
{
    Move::start=new Point(x,y);
    Move::end=new Point(xx,yy);
}
Move::Move(Point *_start, Point *_end)
{
    Move::start=_start;
    Move::end=_end;
}
Point* Move::getStart(){
    return Move::start;
}
Point* Move::getEnd(){
    return Move::end;
}
void Move::setStart(int x,int y){
    Move::start=new Point(x,y);
}
void Move::setEnd(int x, int y){
    Move::end=new Point(x,y);
}

//Board funtions
Board::Board(){
    setUpBoard();
}
Board::Board(vector<vector<Type>>_board){
    numWhiteNormalPieces = 0;
    numBlackNormalPieces = 0;
    numBlackKingPieces = 0;
    numWhiteKingPieces = 0;
    
    board=_board;
    for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j< SIZE; j++)
            {
                Type piece = (Type)getPiece(i, j);
                if(piece == BLACK)
                    numBlackNormalPieces++;
                else if(piece == BLACK_KING)
                    numBlackKingPieces++;
                else if(piece == WHITE)
                    numWhiteNormalPieces++;
                else if(piece == WHITE_KING)
                    numWhiteKingPieces++;
            }
        }
}
void Board::setUpBoard(){
    numWhiteNormalPieces = 12;
    numBlackNormalPieces = 12;
    numBlackKingPieces = 0;
    numWhiteKingPieces = 0;
    cell.resize(8);
    board.resize(8,cell);
    for (int i = 0; i < SIZE; i++) {
            int start = 0;
            if (i % 2 == 0)
                start = 1;

            Type pieceType = EMPTY;
            if (i <= 2)
                pieceType = WHITE;
            else if (i >= 5)
                pieceType = BLACK;

            for (int j = start; j < SIZE; j += 2) {
                board[i][j] = pieceType;
            }
    }
    populateEmptyOnBoard();
}
void Board::setUpTestBoard(){
        numBlackKingPieces = 1;
        numWhiteKingPieces = 1;
        cell.resize(8);
        board.resize(8,cell);
        board[6][1] = WHITE_KING;
        board[4][3] = BLACK_KING;
        populateEmptyOnBoard();
}
void Board::populateEmptyOnBoard(){
    for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (!board[i][j]){
                    board[i][j] = EMPTY;
                }
            }
    }
}
Board::Type Board::getPiece(int row, int col) {
        return board[row][col];
}
Board::Type Board::getPiece(Point *point){
        return board[point->x][point->y];
}
vector<vector<Board::Type>>Board::getBoard(){
    return board;
}
int Board::getNumWhitePieces(){
    return numWhiteKingPieces + numWhiteNormalPieces;
}
int Board::getNumBlackPieces(){
    return numBlackKingPieces + numBlackNormalPieces;
}
int Board::getNumWhiteKingPieces(){
    return numWhiteKingPieces;
}
int Board::getNumBlackKingPieces(){
    return numBlackKingPieces;
}
int Board::getNumWhiteNormalPieces(){
    return numWhiteNormalPieces;
}
int Board::getNumBlackNormalPieces(){
    return numBlackNormalPieces;
}
Board *Board::clone(){
    vector<Type>cell;
    vector<vector<Type>>newBoard;
    cell.resize(8);
    newBoard.resize(8,cell);
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j< SIZE; j++)
            {
                newBoard[i][j] = board[i][j];
            }
        }
    Board *b = new Board(newBoard);
    return b;
}
Board::Decision Board::makeMove(Move *move, int side){
        
        // if(fin == 1) {
        //     return Board::Decision::GAME_ENDED;
        // }
        Point *start = move->getStart();
        int startRow = start->x;
        int startCol = start->y;
        Point *end = move->getEnd();
        int endRow = end->x;
        int endCol = end->y;

        //can only move own piece and not empty space
        if (!isMovingOwnPiece(startRow, startCol, side) || getPiece(startRow, startCol) == Board::Type::EMPTY)
            return Board::Decision::FAILED_MOVING_INVALID_PIECE;
        vector<Move*> possibleMoves = getValidMoves(startRow, startCol, side); 

        Type currType = getPiece(startRow, startCol);
        if (contains(possibleMoves,move)) {
            
            bool jumpMove = false;
            //if it contains move then it is either 1 move or 1 jump
            if (startRow + 1 == endRow || startRow - 1 == endRow) {
                board[startRow][startCol] = Board::Type::EMPTY;
                board[endRow][endCol] = currType;
            } else {
                jumpMove = true;
                board[startRow][startCol] = Board::Type::EMPTY;
                board[endRow][endCol] = currType;
                Point *mid = findMidSquare(move);

                Type middle = getPiece(mid);
                if (middle == Board::Type::BLACK)
                    numBlackNormalPieces--;
                else if(middle == Board::Type::BLACK_KING)
                    numBlackKingPieces--;
                else if(middle == Board::Type::WHITE)
                    numWhiteNormalPieces--;
                else if(middle == Board::Type::WHITE_KING)
                    numWhiteKingPieces--;
                board[mid->x][mid->y] = Board::Type::EMPTY;
            }

            if (endRow == 0 && side == 1) {
                board[endRow][endCol] = Type::BLACK_KING;
                numBlackNormalPieces--;
                numBlackKingPieces++;
            }

            else if (endRow == SIZE - 1 && side == 2) {
                board[endRow][endCol] = Type::WHITE_KING;
                numWhiteNormalPieces--;
                numWhiteKingPieces++;
            }
            if (jumpMove) {
                vector<Move*> additional = getValidSkipMoves(endRow, endCol, side);
                if (additional.empty())
                    return Decision::COMPLETED;
                return Decision::ADDITIONAL_MOVE;
            }
            return Decision::COMPLETED;
        } else
            return Decision::FAILED_INVALID_DESTINATION;
    }

Point* Board::findMidSquare(Move *move){
        Point *ret = new Point((move->getStart()->x + move->getEnd()->x) / 2,
                (move->getStart()->y + move->getEnd()->y) / 2);

        return ret;
}
bool Board::isMovingOwnPiece(int row, int col, int side){
        Type pieceType = getPiece(row, col);
        if (side == 1 && pieceType != Type::BLACK && pieceType != Type::BLACK_KING)
            return false;
        else if (side == 2 && pieceType != Type::WHITE && pieceType != Type::WHITE_KING)
            return false;
        return true;
}
vector <Move*>Board::getValidMoves(int row, int col, int side){
        Type type = board[row][col];
        Point *startPoint = new Point(row, col);
        if (type == Type::EMPTY)
            throw std::invalid_argument("...");
        vector<Move*> moves;
        

        //4 possible moves, 2 if not king
        if (type == Type::WHITE || type == Type::BLACK) {
            //2 possible moves
            int rowChange = type == Type::WHITE ? 1 : -1;
            
            int newRow = row + rowChange;
            if (newRow >= 0 && newRow < SIZE) {
                int newCol = col + 1;
                if (newCol < SIZE && getPiece(newRow, newCol) == Type::EMPTY)
                    moves.push_back(new Move(startPoint, new Point(newRow, newCol)));
                newCol = col - 1;
                if (newCol >= 0 && getPiece(newRow, newCol) == Type::EMPTY)
                    moves.push_back(new Move(startPoint, new Point(newRow, newCol)));
            }

        }
        //must be king
        else {
            //4 possible moves

            int newRow = row + 1;
            if (newRow < SIZE) {
                int newCol = col + 1;
                if (newCol < SIZE && getPiece(newRow, newCol) == Type::EMPTY)
                    moves.push_back(new Move(startPoint, new Point(newRow, newCol)));
                newCol = col - 1;
                if (newCol >= 0 && getPiece(newRow, newCol) == Type::EMPTY)
                    moves.push_back(new Move(startPoint, new Point(newRow, newCol)));
            }
            newRow = row - 1;
            if (newRow >= 0) {
                int newCol = col + 1;
                if (newCol < SIZE && getPiece(newRow, newCol) == Type::EMPTY)
                    moves.push_back(new Move(startPoint, new Point(newRow, newCol)));
                newCol = col - 1;
                if (newCol >= 0 && getPiece(newRow, newCol) == Type::EMPTY)
                    moves.push_back(new Move(startPoint, new Point(newRow, newCol)));
            }
        }
        cout<<"\nValid skip moves:"<<endl;
        vector<Move*> ValidSkipMoves=getValidSkipMoves(row, col, side);
        for(int c=0;c<ValidSkipMoves.size();c++){
        cout<<ValidSkipMoves[c]->start->x<<"-";
        cout<<ValidSkipMoves[c]->start->y<<endl;
        cout<<ValidSkipMoves[c]->end->x<<"-";
        cout<<ValidSkipMoves[c]->end->y<<endl;
        moves.push_back(ValidSkipMoves[c]);
        }

        cout<<"Total Moves Posibles:"<<endl;
        for(int c=0;c<moves.size();c++){
        cout<<moves[c]->start->x<<"-";
        cout<<moves[c]->start->y<<endl;
        cout<<moves[c]->end->x<<"-";
        cout<<moves[c]->end->y<<endl;
        }
        return moves;
}
vector <Move*>Board::getValidSkipMoves(int row, int col, int side){
        vector<Move*> move;
        Point *start = new Point(row, col);

        vector<Point*> possibilities;

        if(side == 2 && getPiece(row, col) == Type::WHITE)
        {
            possibilities.push_back(new Point(row + 2, col + 2));
            possibilities.push_back(new Point(row + 2, col - 2));
        }
        else if(side == 1 && getPiece(row, col) == Type::BLACK)
        {
            possibilities.push_back(new Point(row - 2, col + 2));
            possibilities.push_back(new Point(row - 2, col - 2));
        }
        else if(getPiece(row, col) == Type::BLACK_KING || getPiece(row, col) == Type::WHITE_KING)
        {
            possibilities.push_back(new Point(row + 2, col + 2));
            possibilities.push_back(new Point(row + 2, col - 2));
            possibilities.push_back(new Point(row - 2, col + 2));
            possibilities.push_back(new Point(row - 2, col - 2));
        }

        for (int i = 0; i < possibilities.size(); i++) {
            Point *temp = possibilities[i];
            Move *m = new Move(start, temp);
            if (temp->x < SIZE && temp->x >= 0 && temp->y < SIZE && temp->y >= 0 && getPiece(temp->x, temp->y) == Type::EMPTY
                    && isOpponentPiece(side, getPiece(findMidSquare(m)))) {
                move.push_back(m);
            }
        }
        return move;
}

vector <Move*> Board::getAllValidMoves(int side){
        Type normal = side == 1? Type::BLACK : Type::WHITE;
        Type king = side == 1 ? Type::BLACK_KING : Type::WHITE_KING;

        vector<Move*> possibleMoves;
        for(int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                Type t = getPiece(i, j);
                if(t == normal || t == king){
                    vector<Move*>possibleMovesP=getValidMoves(i, j, side);
                    for(int c=0;c<possibleMovesP.size();c++){
                        possibleMoves.push_back(possibleMovesP[c]);
                    }
                }
                    //possibleMoves.insert(possibleMoves.end(),getValidMoves(i, j, side).begin(),getValidMoves(i, j, side).end());
            }
        }
        return possibleMoves;
}

bool Board::isOpponentPiece(int current, Type opponentPiece){
    if (current == 1 && (opponentPiece == Type::WHITE || opponentPiece == Type::WHITE_KING))
            return true;
        if (current == 2 && (opponentPiece == Type::BLACK || opponentPiece == Type::BLACK_KING))
            return true;
    return false;
}
bool Board::contains(vector<Move*> v,Move *x){  
    cout<<endl;  
    for(int c=0;c<v.size();c++){
        if(v[c]->start->x==x->start->x && v[c]->end->x==x->end->x   && v[c]->start->y==x->start->y && v[c]->end->y==x->end->y){
            return true;
        }
    }
    return false;
}

//Player class
Player::Player(string _name, int _side){
        Player::name=_name;
        Player::side=_side;
}
Player::Player(int _side){    
        Player::side=_side;
}
Player::Player(string _name,int _side, int _depth){   
        Player::name=_name; 
        Player::side=_side;
        Player::depth=_depth;
}

///AI funtions
int Player::FlipSide(int side){
    return side==1?2:1;
}

double Player::GetHeuristic(Board *b){
    double kingWeight = 1.2;
    double result = 0;
    if(side == 2){
        result = b->getNumWhiteKingPieces() * kingWeight + b->getNumWhiteNormalPieces() - b->getNumBlackKingPieces() * kingWeight - b->getNumBlackNormalPieces();
    }else{
        result = b->getNumBlackKingPieces() * kingWeight + b->getNumBlackNormalPieces() - b->getNumWhiteKingPieces() * kingWeight - b->getNumWhiteNormalPieces();
    }
    return result;
}

double Player::Minimax(Board *board, int depth, int side, bool maximizingPlayer, double alpha, double beta){
    if(depth == 0) {
            return GetHeuristic(board);
        }
        vector<Move*> possibleMoves = board->getAllValidMoves(side);

        double initial = 0;
        Board *tempBoard;
        if(maximizingPlayer)
        {
            initial = std::numeric_limits<double>::min(); //Double.NEGATIVE_INFINITY;
            for(int i = 0; i < possibleMoves.size(); i++)
            {
                tempBoard = board->clone();
                tempBoard->makeMove(possibleMoves[i], side);

                double result = Minimax(tempBoard, depth - 1, FlipSide(side), !maximizingPlayer, alpha, beta);

                initial = std::max(result, initial);
                alpha = std::max(alpha, initial);

                if(alpha >= beta)
                    break;
            }
        }
        //minimizing
        else
        {
            initial = std::numeric_limits<double>::max(); //Double.POSITIVE_INFINITY;
            for(int i = 0; i < possibleMoves.size(); i++)
            {
                tempBoard = board->clone();
                tempBoard->makeMove(possibleMoves[i], side);

                double result = Minimax(tempBoard, depth - 1, FlipSide(side), !maximizingPlayer, alpha, beta);

                initial = std::min(result, initial);
                alpha = std::min(alpha, initial);

                if(alpha >= beta)
                    break;
            }
        }

    return initial;
}

Move *Player::MinimaxStart(Board *board,int depth, int side,bool maximizingPlayer){
        double alpha = std::numeric_limits<double>::min();
        double beta = std::numeric_limits<double>::max(); 
        vector<Move*> possibleMoves;
        if(skippingPoint != NULL){            
            possibleMoves = board->getAllValidMoves(Player::side);            
        }
        else
        {
            possibleMoves = board->getValidSkipMoves(skippingPoint->x, skippingPoint->y, side);
            skippingPoint = NULL;
        }
        
        vector<double> heuristics;
        if(possibleMoves.empty())
            return NULL;
        Board *tempBoard;
        for(int i = 0; i < possibleMoves.size(); i++)
        {
            tempBoard = board->clone();
            tempBoard->makeMove(possibleMoves[i], side);
            heuristics.push_back(Minimax(tempBoard, depth - 1, FlipSide(side), !maximizingPlayer, alpha, beta));
        }
        double maxHeuristics = std::numeric_limits<double>::min();
        srand (time(NULL));  
        for(int i = heuristics.size() - 1; i >= 0; i--) {
            if (heuristics[i] >= maxHeuristics) {
                maxHeuristics = heuristics[i];
            }
        }
        for(int i = 0; i < heuristics.size(); i++)
        {
            if(heuristics[i] < maxHeuristics)
            {
                heuristics.erase(heuristics.begin()+i);
                possibleMoves.erase(possibleMoves.begin()+i);
                i--;
            }
        }
        return possibleMoves[rand() % (possibleMoves.size())];
}

///Human
Board::Decision Player::makeMove(Move *m, Board *b)
{
        return b->makeMove(m, Player::side);
}
///Stupid AI
Board::Decision Player::makeMove(Board *b){
    srand (time(NULL));    
    vector<Move*>moves=b->getAllValidMoves(Player::side);
    if(moves.size()==0){
        return Board::Decision::GAME_ENDED;
    }
    int move = rand() % (moves.size());
    Move *m=moves[move];
    cout<<"Selected move: "<<moves[move]->start->x<<"-"<<moves[move]->start->y<<" to "<<moves[move]->end->x<<"-"<<moves[move]->end->y<<endl;
    return b->makeMove(m,Player::side);
}
///AI
Board::Decision Player::makeAImove(Board *b, int side){
    Move *m = MinimaxStart(b, depth, side, true);        
    Board::Decision decision = b->makeMove(m, Player::side);
    if(decision == Board::Decision::ADDITIONAL_MOVE)
        skippingPoint = m->end;
    return decision;
}