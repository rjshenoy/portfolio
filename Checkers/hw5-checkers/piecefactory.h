#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include "piece.h"

class PieceFactory {
public:
    Piece* createPiece(bool isKing, int index);
};


#endif // PIECEFACTORY_H
