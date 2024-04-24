#ifndef ANNOUNCEWINNERDIALOG_H
#define ANNOUNCEWINNERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QWidget>
#include <QDialogButtonBox>
#include <QObject>
#include <QVBoxLayout>
using namespace std;

namespace Ui {
class AnnounceWinnerDialog;
}

class AnnounceWinnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnnounceWinnerDialog(QWidget *parent = nullptr);
    ~AnnounceWinnerDialog();
    void createDialog(int numPlayer1Pieces,int numPlayer2Pieces, string player1, string player2);

private:
    Ui::AnnounceWinnerDialog *ui;
};

#endif // ANNOUNCEWINNERDIALOG_H
