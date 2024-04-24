#include "announcewinnerdialog.h"
#include "ui_announcewinnerdialog.h"

AnnounceWinnerDialog::AnnounceWinnerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnnounceWinnerDialog)
{
    ui->setupUi(this);
}

AnnounceWinnerDialog::~AnnounceWinnerDialog()
{
    delete ui;
}

void AnnounceWinnerDialog::createDialog(int numPlayer1Pieces,int numPlayer2Pieces, string player1, string player2) {

    QDialog* dialog = new QDialog();
    bool winner;
    
    // Set the dialog title
    dialog->setWindowTitle("Announce Winner");
 
    if (numPlayer1Pieces == 0) {winner = true;}
    else {winner = false;}

    QLabel* label = new QLabel(dialog);

    QString t;
    if (winner) {t = QString::fromStdString(player2) + QString::fromStdString(" won the game!");}
    else {t = QString::fromStdString(player1) + QString::fromStdString(" won the game!");}

    label->setText(t); // change
    label->setAlignment(Qt::AlignCenter);
    

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, dialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(buttonBox);
    

    dialog->setLayout(layout);
    

    dialog->exec();
    delete dialog;


}
