#include "boardtile.h"

using namespace std;
BoardTile::BoardTile()
{
    hasPlayer = false;
    player1 = false;
    tileIndex = 0;
}

void BoardTile::setHasPlayer(bool t){
    hasPlayer = t;
}

void BoardTile::setPlayer1(bool b){
    player1 = b;
}

bool BoardTile::getHasPlayer(){
    return hasPlayer;
}

bool BoardTile::getIfPlayer1(){
    return player1;
}

void BoardTile::setIndex(int i){
    tileIndex = i;
}

int BoardTile::getIndex(){
    return tileIndex;
}
