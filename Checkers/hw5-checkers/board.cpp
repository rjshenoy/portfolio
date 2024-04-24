#include "board.h"


#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

#include <random>

//#include <QColorConstants>

using namespace std;

board::board(QGraphicsScene* scene)
{
    
    int counter = 0; // 1-64 counter to better visualize the board
    playerPickedAPiece = false; // a piece has been picked
    numPlayer1Pieces = 0; // keep track player1's pieces, taken/not
    numPlayer2Pieces = 0; // keep track player2's pieces, taken/not
    bool alternate = false; // alternates the red and white color of the board
    player1Turn = true; // true when player 1 turn, false when player2 turn

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {

            grid[i][j] = 0; // board

            int s = 40; // square size
            BoardTile* spot = new BoardTile(); // create a square
            spot->setRect(s*j, s * (9 - i), s, s); // place it on the board
            if(alternate) {
                if(counter % 2 == 0){
                    spot->setBrush(QBrush(Qt::red)); // alternating colors for board

                }
                else{
                    spot->setBrush(QBrush(Qt::white)); // alternating colors for board
                }
            }
            else {
                if(counter % 2 == 0){
                    spot->setBrush(QBrush(Qt::white)); // alternating colors for board
                }
                else{
                    spot->setBrush(QBrush(Qt::red)); // alternating colors for board
                }
            }


            QGraphicsTextItem* text = new QGraphicsTextItem(spot);
            int number;
            if (i % 2 == 0) {
                number = counter;
            } else {
                number = counter;
            }
       
            text->setPlainText("");
            text->setDefaultTextColor(Qt::black);
            QPointF currPos = spot->rect().center() - QPointF(text->boundingRect().width(), text->boundingRect().height() / 2);
            text->setPos(currPos);
            navigateBoard.insert(make_pair(number+1, currPos)); // create a map to navigate the board
            coords.insert(coords.begin(), {currPos.x(), currPos.y()});
            connect(spot, &BoardTile::clicked, this, &board::handleTileClicked); // make a tile clickable

            scene->addItem(spot); // add the tile to the scene

            allTiles.insert(make_pair(number+1, spot)); 
            allTiles[number + 1]->setIndex(number + 1); // set tile index


            counter++;
        }
        alternate = !alternate; // alternate the color
    }
    specialTile(); // create the special tile
    setPlayers(scene); // add the players to the scene

    boardScene = scene;
}

// picks the special tile for the 
int specialTilePick() { 

    int arr[8] = {25, 27, 29, 31, 34, 36, 38, 40};
    int size = 8;
    int index = rand() % size;
    return arr[index];

}

void board::specialTile() {

    int r = specialTilePick();
    allTiles[r]->setBrush(QBrush(Qt::magenta));
    special = allTiles[r];


}

void board::setPlayers(QGraphicsScene* scene) {
    bool alternate = false;
    PieceFactory factory; // create a factory pattern for the pieces
    // player 1
    for(int i = 0; i < 64; i++)
    {
        
        Piece* player = factory.createPiece(false, i); // create piece

        if(alternate){
            if(i % 2 == 0 && i < 25) {
                player->setRect(navigateBoard[i].x(), navigateBoard[i].y(), 25, 25); // piece size and location set
                currPosition = {1, {navigateBoard[i].x(), navigateBoard[i].y()}}; // update currPos
                player->setBrush(QBrush(QColor(135, 206, 235))); // add color to piece
                player->setFocus();
                player->setIndex(i); // set index
                scene->addItem(player); // add piece to scene
                player1Pieces.push_back(player); // add piece to player's pieces set
                numPlayer1Pieces++; // increase total count of p1 pieces

                // setIndex not working
                qDebug() << "Player 1 piece up made" << i;
                allTiles[i]->setHasPlayer(true);
                allTiles[i]->setPlayer1(true);


            }

            if(i % 2 == 0 && i > 40) {
                player->setRect(navigateBoard[i].x(), navigateBoard[i].y(), 25, 25); // piece size and location set
                currPosition = {1, {navigateBoard[i].x(), navigateBoard[i].y()}}; // update currPos
                player->setBrush(QBrush(QColor(182, 212, 163))); // add color to piece
                player->setFocus();
                player->setIndex(i); // set index
                scene->addItem(player); // add piece to scene
                player2Pieces.push_back(player); // add piece to player's pieces set
                numPlayer2Pieces++; // increase total count of p1 pieces

                qDebug() << "Player 2 piece down made" << i;
                allTiles[i]->setHasPlayer(true);
               allTiles[i]->setIndex(i); // set index
            }

            if(i % 8 == 0){
                alternate = !alternate; // change alternate
            }
        }
        else{
            if(i % 2 == 1 && i < 25) {
                player->setRect(navigateBoard[i].x(), navigateBoard[i].y(), 25, 25);
                currPosition = {1, {navigateBoard[i].x(), navigateBoard[i].y()}};
                player->setBrush(QBrush(QColor(135, 206, 235)));
                player->setFocus();
                player->setIndex(i);
                scene->addItem(player);
                player1Pieces.push_back(player);
                numPlayer1Pieces++;

                qDebug() << "Player 1 piece up made" << i;
                allTiles[i]->setHasPlayer(true);
                allTiles[i]->setPlayer1(true);
            }

            if(i % 2 == 1 && i > 40) {
                player->setRect(navigateBoard[i].x(), navigateBoard[i].y(), 25, 25);
                currPosition = {1, {navigateBoard[i].x(), navigateBoard[i].y()}};
                player->setBrush(QBrush(QColor(182, 212, 163))); 
                player->setFocus();
                player->setIndex(i);
                scene->addItem(player);
                player2Pieces.push_back(player);
                numPlayer1Pieces++;

                qDebug() << "Player 2 piece down made" << i;
                allTiles[i]->setHasPlayer(true);
                
            }

            // makes sure pieces only spawn on red tiles
            if(i % 8 == 0){
                alternate = !alternate;
            }
        }
        Piece::connect(player, &Piece::clickedPiece, this, &board::handlePieceClicked);
    }
}

void board::handlePieceClicked( int index) {
    // this is how we could check which tile was clicked on and move accordingly
    for(int i = 0; i < player1Pieces.size(); i++){
        if (player1Pieces[i]->getIndex() == index){
            if(player1Turn){
                toMove = player1Pieces[i];
                playerPickedAPiece = true;
                qDebug() << "player1 piece";
                break;
            }
            else{
                playerPickedAPiece = false;
                qDebug() << "not your piece. cannot move";
            }

        }
    }
    for(int i = 0; i < player2Pieces.size(); i++){
        if (player2Pieces[i]->getIndex() == index){
            if(!player1Turn){
                toMove = player2Pieces[i];
                playerPickedAPiece = true;
                qDebug() << "player 2 piece";
                break;
            }
            else{
                playerPickedAPiece = false;
                qDebug() << "not your piece. cannot move";
            }
        }
    }

}


void board::removePiece(int index, bool p1) { // remove a piece
    bool deleted = false;
    if(!deleted) {
        for (int i = 0; i < player1Pieces.size(); i++) {
            if (player1Pieces[i]->getIndex() == index && !deleted) {
                boardScene->removeItem(player1Pieces[i]); // remove from scene
                player1Pieces.erase(player1Pieces.begin() + i); // remove from player's piece set
                allTiles[index]->setHasPlayer(false); // remove from board
                deleted = true;
            }
        }
    }
    if(!deleted) {
        for (int i = 0; i < player2Pieces.size(); i++) {
            if (player2Pieces[i]->getIndex() == index && !deleted) {
                boardScene->removeItem(player2Pieces[i]);
                player2Pieces.erase(player2Pieces.begin() + i);
                allTiles[index]->setHasPlayer(false);
                deleted = true;
            }
        }
    }
}

void board::checkPieceKing(Piece* p, int newidx) { // check if a piece is a king
    // player 1, check if at end of board 
    if(allTiles[p->getIndex()]->getIfPlayer1()){
        if(newidx >= 57 && newidx <= 64){
            p->setIsKing(true);
        }
    }
    if(!allTiles[p->getIndex()]->getIfPlayer1()){
        if(newidx >= 1 && newidx <= 8){
            p->setIsKing(true);
        }
    }
    
}


// called when an empty tile is clicked for the current piece to move to. 
// Handles regular diagonal movements as well as the killing of opponent pieces
// handles all movements of the game
void board::handleTileClicked(int ndx){
   bool validExtend = false;
   // for king movements/ legal movemnts
   bool player1moves = false; 
   bool player2moves = false;

   // flag for if player just selected a random tile on the board without clicking on a piece to move
    if(!playerPickedAPiece){
        playerPickedAPiece = false;
        qDebug() << "Picked the tile with the piece: " << ndx;
    } 
    else if(!allTiles[ndx]->getHasPlayer()){ // checks if the tile you want to move to is empty
        // established legal movements for the current piece [toMove- set in handlePiece function]
        if(toMove->getIsKing() || allTiles[toMove->getIndex()]->getIfPlayer1()) {player1moves = true;}
        if(toMove->getIsKing() || !allTiles[toMove->getIndex()]->getIfPlayer1()) {player2moves = true;}

        // Player 1 valid moves (directly diagonal)
        if (player1moves && (ndx == toMove->getIndex()+7 || ndx == toMove->getIndex()+9)){

            // updates allTiles values 
            allTiles[toMove->getIndex()]->setHasPlayer(false);
            allTiles[ndx]->setHasPlayer(true);
            allTiles[ndx]->setPlayer1(allTiles[toMove->getIndex()]->getIfPlayer1());
            // sets a new rectangle somewhere on the board with the same piece
            toMove->setRect(navigateBoard[ndx].x(), navigateBoard[ndx].y(), 25, 25);
            // sets new index of pieces 
            toMove->setIndex(ndx);
            playerPickedAPiece = false;
            
            // checks if the player is king now
            checkPieceKing(toMove, ndx);
            turnEnd();
            qDebug() << "Player 1 ended turn";
        }
        // Player 2 valid moves
        if (player2moves && (ndx == toMove->getIndex()-7 || ndx == toMove->getIndex()-9)){
            allTiles[toMove->getIndex()]->setHasPlayer(false);
            allTiles[ndx]->setHasPlayer(true);
            allTiles[ndx]->setPlayer1(allTiles[toMove->getIndex()]->getIfPlayer1());

            toMove->setRect(navigateBoard[ndx].x(), navigateBoard[ndx].y(), 25, 25);
            toMove->setIndex(ndx);
            playerPickedAPiece = false;

            checkPieceKing(toMove, ndx);
            turnEnd();
            qDebug() << "Player 2 ended turn";
        }

        // taking a piece
        // player 2 taking a piece
        if ( player2moves && (ndx == toMove->getIndex()-14 || ndx == toMove->getIndex()-18) && allTiles[toMove->getIndex()]->getHasPlayer())
        {
            // piece moving to the right to take a piece
            if(allTiles[toMove->getIndex()-7]->getHasPlayer() && ndx == toMove->getIndex()-14)
            {
                allTiles[toMove->getIndex()]->setHasPlayer(false);
                allTiles[ndx]->setHasPlayer(true);
                allTiles[ndx]->setPlayer1(allTiles[toMove->getIndex()]->getIfPlayer1());

                // remove piece in the middle here
                removePiece(toMove->getIndex() - 7, false);

                toMove->setRect(navigateBoard[ndx].x(), navigateBoard[ndx].y(), 25, 25);
                toMove->setIndex(ndx);

                // resets value for next time
                playerPickedAPiece = false;

                checkPieceKing(toMove, ndx);
                turnEnd();
                qDebug() << "Player 2 ate a piece when moving right";
            }

            // piece moving to rhe left to take a piece 
            if(allTiles[toMove->getIndex()-9]->getHasPlayer() && ndx == toMove->getIndex()-18) {
                allTiles[toMove->getIndex()]->setHasPlayer(false);
                allTiles[ndx]->setHasPlayer(true);
                allTiles[ndx]->setPlayer1(allTiles[toMove->getIndex()]->getIfPlayer1());

                // remove piece here
                removePiece(toMove->getIndex() - 9, false);

                toMove->setRect(navigateBoard[ndx].x(), navigateBoard[ndx].y(), 25, 25);
                toMove->setIndex(ndx);
                playerPickedAPiece = false;

                checkPieceKing(toMove, ndx);
                turnEnd();
                qDebug() << "Player 2 ended turn";
                // erase player 1 piece
                // add to player 2 collection
            }
        }

        // taking a piece
        // player 1 taking a piece
        if ( player1moves && (ndx == toMove->getIndex()+14 || ndx == toMove->getIndex()+18))
        {
            // tile moving to the right
            if(allTiles[toMove->getIndex()+7]->getHasPlayer() && ndx == toMove->getIndex()+14)
            {
                allTiles[toMove->getIndex()]->setHasPlayer(false);
                allTiles[ndx]->setHasPlayer(true);
                allTiles[ndx]->setPlayer1(allTiles[toMove->getIndex()]->getIfPlayer1());

                // remove piece here
                removePiece(toMove->getIndex() + 7, false);

                toMove->setRect(navigateBoard[ndx].x(), navigateBoard[ndx].y(), 25, 25);
                toMove->setIndex(ndx);
                playerPickedAPiece = false;

                checkPieceKing(toMove, ndx);
                turnEnd();
                qDebug() << "Player 2 ate a piece when moving right";
            }

            // piece moving to the left
            if(allTiles[toMove->getIndex()+9]->getHasPlayer() && ndx == toMove->getIndex()+18) {
                allTiles[toMove->getIndex()]->setHasPlayer(false);
                allTiles[ndx]->setHasPlayer(true);
                allTiles[ndx]->setPlayer1(false);

                // remove piece here
                removePiece(toMove->getIndex() + 9, false);

                toMove->setRect(navigateBoard[ndx].x(), navigateBoard[ndx].y(), 25, 25);
                toMove->setIndex(ndx);
                playerPickedAPiece = false;

                checkPieceKing(toMove, ndx);
                turnEnd();
                qDebug() << "Player 2 ended turn";
            }
        }
    }
    if(allTiles[toMove->getIndex()] == allTiles[special->getIndex()]){
        int king = rand() % 2 + 1;
        if(king == 2) {
            toMove->setIsKing(true); // is a king
        }
        else{
            removePiece(toMove->getIndex(), false); // piece gets removed
        }

    }

    checkEndGame();
}

// checks if the game has ended. 
void board::checkEndGame() {
    numPlayer1Pieces = player1Pieces.size();
    numPlayer2Pieces = player2Pieces.size();
    if(numPlayer1Pieces == 0 || numPlayer2Pieces == 0)
    {
//        accept();
    }
}

// prints x and y position of all the tiles 
void board::printMap() {

    for (int i = 0; i < 100; i++) {

        qDebug() << "index: " << i;
        qDebug() << "position x: " << navigateBoard[i].x();
        qDebug() << "position y: " << navigateBoard[i].y();
    }
}


// increments turn of the current player so game knows which pieces are movable
void board::incrementTurn() {
    player1Turn = !player1Turn;
    qDebug() << "Increment Turn: " << player1Turn;

}


// lets mainwindow know when a turn has ended so it can change the name of the current player
void board::turnEnd() {
    emit endTurn();
}




