#ifndef PIECE_H
#define PIECE_H



#include <vector>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QKeyEvent>
#include <QObject>
//#include <QGraphicsSceneMouseEvent>

using namespace std;
class Piece : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT

private:
    bool isKing;        // true when piece is king and can move back and forth
    bool isClickedOn;   // true when it is the tile that needs to move
    int index;          // 1-64 index on the 8x8 board

public:
    Piece();

    bool getIsKing();            // returns if the piece is a king
    void setIsKing(bool king);   // sets king status to piece
    int getIndex();              // returns index of the tile
    void setIndex(int i);        // sets index of the tile
//    void focusInEvent(QFocusEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void clickedPiece(int index);  // lets board know when the tile is clicked.

};

#endif // PIECE_H
