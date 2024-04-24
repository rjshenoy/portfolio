#include "teacherwindow.h"
#include "ui_teacherwindow.h"

TeacherWindow::TeacherWindow(QWidget *parent, Teacher *t) :
    QMainWindow(parent),
    ui(new Ui::TeacherWindow),
    teacher(t)
{
    ui->setupUi(this);
    QString qstrName = QString::fromStdString(this->teacher->getName());
    ui->teacherName->setText(qstrName);
    displayCourses();
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}

void TeacherWindow::displayCourses()
{
    // Retrieve Courses from Logged-in Teacher
    vector<Course*> courses = this->teacher->getCourses();
    qDebug() << courses.size();
    // Iterate through, draw to screen
    int i = 0;
    for (auto c : courses)
    {
        qDebug() << QString::fromStdString(c->getClassName());
        // Create new button for each course, connect with slot
        teacherViewCourseButton *vcButton = new teacherViewCourseButton(c, 30, 250+i);
        vcButton->setParent(this);
        connect(vcButton, &teacherViewCourseButton::viewCourseButtonClicked, this, &TeacherWindow::courseButton);
        i += 110;
    }
}

void TeacherWindow::courseButton(Course *c)
{
    qDebug() << QString::fromStdString(c->getClassName());
    teacherCourseViewWindow* courseWindow = new teacherCourseViewWindow(nullptr, c, this);
    this->hide();
    courseWindow->show();
}
