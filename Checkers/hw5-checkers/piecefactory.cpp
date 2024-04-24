#include "piecefactory.h"


// factory pattern for the piece
Piece* PieceFactory::createPiece(bool isKing, int index) {

    Piece* piece = new Piece();
    piece->setIsKing(isKing);
    piece->setIndex(index);
    return piece;
    


}
