#include <vector>
#include <iostream>
#include <bits/stdc++.h> 
#include <string>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#define SIZE 8
using namespace std;
class Point{
public:
    int x;
    int y;
    Point(int x,int y);
};

class Move{
public:
    Point *start;
    Point *end;
public:
    Move();
    Move(int x,int y, int xx, int yy);
    Move(Point *_start, Point *_end);
    Point *getStart();
    Point *getEnd();
    void setStart(int x, int y);
    void setEnd(int x, int y);
    //string toString();
    //bool equals();
};

class Board {
private:
    enum Type {EMPTY, WHITE, BLACK, WHITE_KING, BLACK_KING};
    vector<Type>cell;
    vector<vector<Type>>board;
    int numWhiteNormalPieces;
    int numBlackNormalPieces;
    int numBlackKingPieces;
    int numWhiteKingPieces;
public:
    enum Decision {COMPLETED,FAILED_MOVING_INVALID_PIECE,FAILED_INVALID_DESTINATION,ADDITIONAL_MOVE,GAME_ENDED};
public:    
    Board();
    Board(vector<vector<Type>>board);      
    Type getPiece(int row, int col);
    Type getPiece(Point *point);
    vector<vector<Type>>getBoard();
    int getNumWhitePieces();
    int getNumBlackPieces();
    int getNumWhiteKingPieces();
    int getNumBlackKingPieces();
    int getNumWhiteNormalPieces();
    int getNumBlackNormalPieces();
    Decision makeMove(Move *move, int side);
    vector <Move*>getAllValidMoves(int side);
    Point* findMidSquare(Move *move);
    bool isMovingOwnPiece(int row, int col, int side);
    vector <Move*>getValidMoves(int row, int col, int side);
    vector <Move*>getValidSkipMoves(int row, int col, int side);
    bool isOpponentPiece(int current, Type opponentPiece);
    Board *clone();
    bool contains(vector<Move*> possibleMoves,Move *move);
private: 
    void setUpBoard();
    void setUpTestBoard();
    void populateEmptyOnBoard();  
};

class Player {  
public:
    Point *skippingPoint;
public:     
    string name;
    int side; //Side 1 = Black : 2 = White
    int depth;
    Player(string name, int side);
    Player(int side);
    Player(string name, int side, int depth);
    int FlipSide(int side);
    double GetHeuristic(Board *b);
    double Minimax(Board *b, int depth, int side, bool maximizingPlayer, double alpha, double beta);
    Move *MinimaxStart(Board *b,int depth, int side,bool maximizingPlayer);
    Board::Decision makeMove(Move *m, Board *b);
    Board::Decision makeMove(Board *board);
    Board::Decision makeAImove(Board *board, int side);
    // Board::Decision makeRandomMove(Board *b);
};
