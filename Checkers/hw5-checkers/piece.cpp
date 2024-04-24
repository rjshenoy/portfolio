#include "piece.h"

Piece::Piece()
{
    isKing = false;
    isClickedOn = false;
    index = -1;
}


bool Piece::getIsKing() {
    return isKing;
}

void Piece::setIsKing(bool king){
    isKing = king;
}

void Piece::setIndex(int x){
    index = x;
}

int Piece::getIndex(){
    return index;
}

void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event) {


    emit clickedPiece( index);
}
