#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include "teacher.h"
#include <QWidget>
#include <QPushButton>
#include "teacherviewcoursebutton.h"
#include "teachercourseviewwindow.h"

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = nullptr, Teacher *t = nullptr);
    ~TeacherWindow();

public slots:
    void courseButton(Course* c);

private:
    Ui::TeacherWindow *ui;
    Teacher *teacher;
    void displayCourses();
    vector<teacherViewCourseButton*> courseButtons;
};

#endif // TEACHERWINDOW_H
