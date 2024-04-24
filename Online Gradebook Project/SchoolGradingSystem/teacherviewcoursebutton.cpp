#include "teacherviewcoursebutton.h"

void teacherViewCourseButton::onViewButtonClicked()
{
    emit this->viewCourseButtonClicked(this->course);
}

teacherViewCourseButton::teacherViewCourseButton(Course *c, int x, int y)
{
    // Create widget
    this->course = c;
    this->setGeometry(x, y, width_, height_);
    this->setFrameStyle(QFrame::Box | QFrame::Plain);
    this->setLineWidth(2);
    // Create label
    QLabel *courseLabel = new QLabel(QString::fromStdString(c->getClassName()), this);
    courseLabel->setGeometry(10,10, 200, 80);
    courseLabel->setAlignment(Qt::AlignVCenter);
    // Create the button to open that Course, emit the appropriate signal when pressed
    viewButton = new QPushButton("View Course", this);
    viewButton->setFlat(false);
    connect(viewButton, &QPushButton::clicked, this, &teacherViewCourseButton::onViewButtonClicked);
    viewButton->setGeometry(width_-110, 10, 100, 80);
}
