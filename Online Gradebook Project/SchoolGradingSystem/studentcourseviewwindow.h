#ifndef STUDENTCOURSEVIEWWINDOW_H
#define STUDENTCOURSEVIEWWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "course.h"
#include "assignment.h"
#include "gradestablemodel.h"
#include "studentwindow.h"
namespace Ui {
class studentcourseviewwindow;
}

class StudentWindow;
class studentcourseviewwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentcourseviewwindow(QWidget *parent = nullptr, Course* course_ = nullptr, Student* s = nullptr, StudentWindow* stw = nullptr);
    ~studentcourseviewwindow();

private slots:
    void on_newAssignmentButton_clicked();

    void on_exitButton_clicked();

private:
    Course* course;
    Ui::studentcourseviewwindow *ui;
    vector<QFrame*> assignmentFrames;
    Student* currStudent;
    StudentWindow* sw;

    void drawAssignment(Assignment *a, int x, int y);
    void updateAssignmentList();
};

#endif // STUDENTCOURSEVIEWWINDOW_H
