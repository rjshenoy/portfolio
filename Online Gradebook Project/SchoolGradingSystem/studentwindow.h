#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include "student.h"
#include <QWidget>
#include <QPushButton>
#include "studentviewcoursebutton.h"


namespace Ui {
class StudentWindow;
}

class studentcourseviewwindow;
class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr, Student *s = nullptr);
    ~StudentWindow();

public slots:
    void courseButton(Course* c);

private:
    Ui::StudentWindow *ui;
    Student *student;
    void displayCourses();
    vector<studentviewcoursebutton*> courseButtons;
};

#endif // TEACHERWINDOW_H
