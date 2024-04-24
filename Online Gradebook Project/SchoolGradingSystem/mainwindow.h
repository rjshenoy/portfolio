#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"
#include "course.h"
#include "datatest.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SignInButton_clicked();

private:
    Ui::MainWindow *ui;
    DataTest *data;


    bool submitReady;
    void hideLogin();
    void showLogin();
    Teacher* verifyTeacherLogin(string user_, string pass_);
    Student* verifyStudentLogin(string user_, string pass_);





};
#endif // MAINWINDOW_H
