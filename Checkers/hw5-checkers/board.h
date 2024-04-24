#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsProxyWidget>
#include <QObject>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>

#include "piece.h"
#include "boardtile.h"
#include "piecefactory.h"
using namespace std;

class board : public QObject
{

    Q_OBJECT
private:
    int grid[10][10];                  // grid that holds the tiles

    vector <tuple<int,int>> coords;
    map<int, QPointF> navigateBoard;   // Maps 1-64 to x and y position on the board
    pair<int, QPointF> currPosition;
    int newSpot = 1;
    QPointF newPos;

    vector<Piece *> player1Pieces;     // holds all the player 1 pieces. might not need
    int numPlayer1Pieces;              // total number of player 1 pieces
    vector<Piece *> player2Pieces;     // holds all the player2 pieces
    int numPlayer2Pieces;              // total number of player 2 pieces. might not need

    map<int, BoardTile *> allTiles;    // maps all the tiles to number 1-64
    bool playerPickedAPiece;           // true when player has picked a tile to move
    bool player1Turn;                  // true when its player1's turn, false when its player 2's turn
    BoardTile* special;
    Piece* toMove;
    QGraphicsScene* boardScene;

public:
    board(QGraphicsScene* scene);
    void printMap();
    
    void setPlayers(QGraphicsScene* scene);   // places pieces of each player
    void handlePieceClicked( int index);      // handler for when a piece is clicked
    void handleTileClicked( int ndx);         // handler for when a tile is clicked
    void incrementTurn();                     // changes between player1 and player2
    bool getTurn();                           // returns which player's turn it is. true for player 1, false for player 2
    void turnEnd();
    void removePiece(int index, bool p1);

    void specialTile();
    void checkPieceKing(Piece* p, int newidx); 
    void checkEndGame();           // checks if the piece is at the edge of the board

signals:
    void endTurn();
    void endGame();


};

#endif // BOARD_H
