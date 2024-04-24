#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "studentcourseviewwindow.h"

StudentWindow::StudentWindow(QWidget *parent, Student *s) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow),
    student(s)
{
    ui->setupUi(this);
    QString qstrName = QString::fromStdString(this->student->getName());
    ui->studentName->setText(qstrName);
    displayCourses();
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::displayCourses()
{
    // Retrieve Courses from Logged-in Teacher
    vector<Course*> courses = this->student->getCourses();
    qDebug() << courses.size();
    // Iterate through, draw to screen
    int i = 0;
    for (auto c : courses)
    {
        qDebug() << QString::fromStdString(c->getClassName());
        // Create new button for each course, connect with slot
        studentviewcoursebutton *vcButton = new studentviewcoursebutton(c, 30, 250+i);
        vcButton->setParent(this);
        connect(vcButton, &studentviewcoursebutton::viewCourseButtonClicked, this, &StudentWindow::courseButton);
        i += 110;
    }
}

void StudentWindow::courseButton(Course *c)
{
    qDebug() << QString::fromStdString(c->getClassName());
    studentcourseviewwindow* courseWindow = new studentcourseviewwindow(nullptr, c, student, this);
    this->hide();
    courseWindow->show();
}
