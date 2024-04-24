#include "playernamedialog.h"
#include "ui_playernamedialog.h"
#include "qpushbutton.h"

PlayerNameDialog::PlayerNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerNameDialog)
{
    ui->setupUi(this);
}

PlayerNameDialog::~PlayerNameDialog()
{
    delete ui;
}

void PlayerNameDialog::enterNames() {

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(10); // Set the vertical spacing between widgets


    QLabel* x = new QLabel("Enter Player Name: ", this);
    QTextEdit* playerName1 = new QTextEdit(this);
    layout->addWidget(x);
    layout->addWidget(playerName1);

    QLabel* x1 = new QLabel("Enter Player Name: ", this);
    QTextEdit* playerName2 = new QTextEdit(this);
    layout->addWidget(x1);
    layout->addWidget(playerName2);




    QPushButton* confirmButton = new QPushButton("Confirm", this);
    layout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, [=]() {
            names[0] = playerName1->toPlainText().toStdString();
            names[1] = playerName2->toPlainText().toStdString();
            accept();
    });

    this->setFixedSize(200, 200);
    this->setLayout(layout);

}






string* PlayerNameDialog::getNames() {

    return names;

}
