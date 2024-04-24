#include "studentcourseviewwindow.h"
#include "qdialog.h"
#include "QTableView"
#include "qlineedit.h"
#include "ui_studentcourseviewwindow.h"
#include "assignmentfactory.h"
#include "studentwindow.h"


studentcourseviewwindow::studentcourseviewwindow(QWidget *parent, Course* course_, Student* s, StudentWindow* stw) :
    QMainWindow(parent),
    course(course_),
    ui(new Ui::studentcourseviewwindow),
    currStudent(s),
    sw(stw)
{
    ui->setupUi(this);
    ui->courseNameLabel->setText(QString::fromStdString(course->getClassName()));

    updateAssignmentList();
}

studentcourseviewwindow::~studentcourseviewwindow()
{
    delete ui;
}

// helper function for drawing a frame for an Assignment
void studentcourseviewwindow::drawAssignment(Assignment *a, int x, int y)
{
    // create frame
    QFrame* aFrame = new QFrame(this);
    aFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
    aFrame->setGeometry(x, y, 760, 100);
    // create label
    QLabel* assignmentLabel = new QLabel(QString::fromStdString(a->getTitle()), aFrame);
    assignmentLabel->setGeometry(10, 10, 200, 80);
    assignmentLabel->setFont(QFont("Arial", 16));

    QLabel* viewGrade = new QLabel(QString::fromStdString(to_string(a->getScore(currStudent))), aFrame);
    viewGrade->setGeometry(600,30,100,30);
    viewGrade->show();
    // create view grades button
//    QPushButton* viewGradesButton = new QPushButton("View Grades", aFrame);
//    viewGradesButton->setGeometry(600,30,100,30);
//    // connect button signal to slot
//    connect(viewGradesButton, &QPushButton::clicked, this, [=]() {
//        // create dialog
//        QDialog* dialog = new QDialog(this);
//        dialog->setWindowTitle(QString::fromStdString(a->getTitle() + " Grades"));
//        dialog->setGeometry(100, 100, 400, 400);

//        // add contents to dialog
//        QLabel* gradesLabel = new QLabel("Grades for " + QString::fromStdString(a->getTitle()), dialog);
//        gradesLabel->setGeometry(10, 10, 200, 40);
//        QTableView* tableView = new QTableView(dialog);
//        tableView->setGeometry(10, 50, 380, 340);

//        // set up table model and view
//        GradesTableModel* model = new GradesTableModel(a, this);
//        tableView->setModel(model);

//        // show dialog
//        dialog->exec();

//        // clean up
//        delete dialog;
//    });
    this->assignmentFrames.push_back(aFrame);
    aFrame->show();
}

#include "QComboBox"

void studentcourseviewwindow::on_newAssignmentButton_clicked()
{

}

void studentcourseviewwindow::updateAssignmentList()
{
    for (auto frame : assignmentFrames) {
        delete frame;
    }
    assignmentFrames.clear();

    int i = 0;
    for (auto a : course->getAllAssignments())
    {
        drawAssignment(a, 20, 150+i);
        i += 110;
    }
}


void studentcourseviewwindow::on_exitButton_clicked()
{

    this->close();
    sw->show();

}

