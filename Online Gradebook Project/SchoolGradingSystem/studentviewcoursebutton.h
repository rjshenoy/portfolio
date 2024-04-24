#ifndef STUDENTVIEWCOURSEBUTTON_H
#define STUDENTVIEWCOURSEBUTTON_H


#include <QObject>
#include <QWidget>
#include "course.h"
#include <QPushButton>

class studentviewcoursebutton : public QFrame
{
    Q_OBJECT

public:
    studentviewcoursebutton(Course *c, int x, int y);
    virtual ~studentviewcoursebutton() {};

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

#endif // STUDENTVIEWCOURSEBUTTON_H
