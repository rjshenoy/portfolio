#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QObject>
#include <QGraphicsView>
#include "playernamedialog.h"
#include "board.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initBoard(QWidget* parentWidget);
    void playerMovement();
    void startGame();
    void endGame();
    void changeTurn();

private:
    Ui::MainWindow *ui;
    PlayerNameDialog* pNameDialog;
    QGridLayout* checkersBoardLayout;
    const int tileSize = 50;
    string* names;
    int currentPlayer;
    QPixmap circlePixmap;

    QGraphicsScene* scene;
    board* board1;

    QPushButton* startButton;
    QPushButton* endButton;
    QPushButton* changeTurnButton;
    QHBoxLayout *layout;
    QGraphicsView *view;
    QVBoxLayout *buttonLayout;
    QLabel* changeTurnLabel;


};
#endif // MAINWINDOW_H
