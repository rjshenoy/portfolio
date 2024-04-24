#ifndef PLAYERNAMEDIALOG_H
#define PLAYERNAMEDIALOG_H

#include <QDialog>
#include <vector>
using namespace std;
#include <QLabel>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QRect>
#include <QPushButton>

namespace Ui {
class PlayerNameDialog;
}

class PlayerNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerNameDialog(QWidget *parent = nullptr);
    ~PlayerNameDialog();
    void enterNames();
    string* getNames();


private:
    Ui::PlayerNameDialog *ui;
    string names[2];

};

#endif // PLAYERNAMEDIALOG_H
