
#ifndef TEACHERVIEWCOURSEBUTTON_H
#define TEACHERVIEWCOURSEBUTTON_H


#include <QObject>
#include <QWidget>
#include "course.h"
#include <QPushButton>

class teacherViewCourseButton : public QFrame
{
    Q_OBJECT

public:
    teacherViewCourseButton(Course *c, int x, int y);
    virtual ~teacherViewCourseButton() {};

signals:
    void viewCourseButtonClicked(Course *c);

private slots:
    void onViewButtonClicked();

private:
    static const int width_  = 400;
    static const int height_ = 100;
    Course* course;
    QPushButton* viewButton;
};

#endif // TEACHERVIEWCOURSEBUTTON_H
