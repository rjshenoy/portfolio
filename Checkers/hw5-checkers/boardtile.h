#ifndef BOARDTILE_H
#define BOARDTILE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QObject>
#include <QWidget>

using namespace std;

class BoardTile : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    bool hasPlayer; // flag for when there is a piece on the tile
    bool player1;   // flag for which player's piece is on the current tile
    int tileIndex;  // 1-64 index of the tile

public:
    BoardTile();                 // Default cnstructor
    void setHasPlayer(bool t);   // called when player has moved to/ generated in tile
    void setPlayer1(bool b);     // called when player 1 is on the tile
    void setIndex(int i);
    int getIndex();
    bool getHasPlayer();         // used to check if there is a piece already in the tile
    bool getIfPlayer1();

    // lets board know when the tile
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        qDebug() << "mousepress working for tile";
        emit clicked(tileIndex);
    }

signals:
    void clicked( int ndx);
};

#endif // BOARDTILE_H
