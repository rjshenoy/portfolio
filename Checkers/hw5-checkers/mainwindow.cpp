#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , names(new string[2])
{

    ui->setupUi(this);
    QString styleSheet = "background-color: #336699;";
    this->setStyleSheet(styleSheet);
    pNameDialog = new PlayerNameDialog(this);
    pNameDialog->enterNames();
    pNameDialog->setModal(true);

    if (pNameDialog->exec() == QDialog::Accepted) {
        string *tempNames = pNameDialog->getNames();
        names[0] = tempNames[0];
        names[1] = tempNames[1];
    }

    // Create a horizontal layout to hold the board and buttons
    layout = new QHBoxLayout(ui->centralwidget);

    // Create the board and add it to the layout


    // Create the button widgets
    // Create the button widgets
    startButton = new QPushButton(tr("Start Game"));
    startButton->setFixedSize(100, 30);
    endButton = new QPushButton(tr("End Game"));
    endButton->setFixedSize(100, 30);


    // Create a vertical layout to hold the buttons
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(endButton);
    currentPlayer = 0;
    changeTurnLabel = new QLabel(QString::fromStdString(names[currentPlayer] + "'s turn"));
    endButton->hide();
    changeTurnLabel->hide();
    buttonLayout->addWidget(changeTurnLabel);



    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(endButton, &QPushButton::clicked, this, &MainWindow::endGame);
//    connect(changeTurnButton, &QPushButton::clicked, this, &MainWindow::changeTurn);



    // Add a stretch item to the layout to push the buttons to the right
//    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum);
//    buttonLayout->addSpacerItem(spacer);

    // Add the button layout to the main layout

    layout->addLayout(buttonLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    view = ui->board;
    scene = new QGraphicsScene;
    view->setScene(scene);
    board1 = new board(scene);
    //    board1->printMap();

    view->setFixedSize(400, 400);
    layout->addWidget(view);
    endButton->show();
//    changeTurnButton->show(); // access member variable
    changeTurnLabel->show();
    board::connect(board1, &board::endTurn, this, &MainWindow::changeTurn);
}


void MainWindow::endGame()
{

    view->setScene(nullptr);

}

void MainWindow::changeTurn()
{

    if (currentPlayer == 0) {
        currentPlayer = 1;
    }
    else {currentPlayer = 0;}
    board1->incrementTurn();
    qDebug() << "Calling changeTurn";
    changeTurnLabel->setText(QString::fromStdString(names[currentPlayer] + "'s turn"));
}

void MainWindow::playerMovement()
{
    // TODO: Implement the player movement functionality
}
