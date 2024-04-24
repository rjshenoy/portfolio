#include "teachercourseviewwindow.h"
#include "qdialog.h"
#include "QTableView"
#include "qlineedit.h"
#include "teacherwindow.h"
#include "ui_teachercourseviewwindow.h"
#include "assignmentfactory.h"

teacherCourseViewWindow::teacherCourseViewWindow(QWidget *parent, Course* course_, TeacherWindow* teacherWindow_) :
    QMainWindow(parent),
    course(course_),
    ui(new Ui::teacherCourseViewWindow),
    teacherWindow(teacherWindow_)
{
    ui->setupUi(this);
    ui->courseNameLabel->setText(QString::fromStdString(course->getClassName()));

    updateAssignmentList();
}

teacherCourseViewWindow::~teacherCourseViewWindow()
{
    delete ui;
}

// helper function for drawing a frame for an Assignment
void teacherCourseViewWindow::drawAssignment(Assignment *a, int x, int y)
{
    // create frame
    QFrame* aFrame = new QFrame(this);
    aFrame->setFrameStyle(QFrame::Box | QFrame::Plain);
    aFrame->setGeometry(x, y, 760, 100);
    // create label
    QLabel* assignmentLabel = new QLabel(QString::fromStdString(a->getTitle()), aFrame);
    assignmentLabel->setGeometry(10, 10, 200, 80);
    assignmentLabel->setFont(QFont("Arial", 16));

    // create view grades button
    QPushButton* viewGradesButton = new QPushButton("View Grades", aFrame);
    viewGradesButton->setGeometry(600,30,100,30);
    // connect button signal to slot
    connect(viewGradesButton, &QPushButton::clicked, this, [=]() {
        // create dialog
        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle(QString::fromStdString(a->getTitle() + " Grades"));
        dialog->setGeometry(100, 100, 400, 400);

        // add contents to dialog
        QLabel* gradesLabel = new QLabel("Grades for " + QString::fromStdString(a->getTitle()), dialog);
        gradesLabel->setGeometry(10, 10, 200, 40);
        QTableView* tableView = new QTableView(dialog);
        tableView->setGeometry(10, 50, 380, 340);

        // set up table model and view
        GradesTableModel* model = new GradesTableModel(a, this);
        tableView->setModel(model);

        // show dialog
        dialog->exec();

        // clean up
        delete dialog;
    });
    this->assignmentFrames.push_back(aFrame);
    aFrame->show();
}

#include "QComboBox"

void teacherCourseViewWindow::on_newAssignmentButton_clicked()
{
    // Create dialog
    QDialog *createAssignmentWindow = new QDialog(this);
    createAssignmentWindow->setWindowTitle("Create New Assignment");

    // Drop down menu for type of assignment
    QLabel *assignmentTypeLabel = new QLabel("Assignment Type:", createAssignmentWindow);
    QComboBox *assignmentTypeComboBox = new QComboBox(createAssignmentWindow);
    assignmentTypeComboBox->addItem("Exam");
    assignmentTypeComboBox->addItem("Quiz");
    assignmentTypeComboBox->addItem("Homework");
    QHBoxLayout *assignmentTypeLayout = new QHBoxLayout();
    assignmentTypeLayout->addWidget(assignmentTypeLabel);
    assignmentTypeLayout->addWidget(assignmentTypeComboBox);

    // Input score box
    QLabel *scoreLabel = new QLabel("Total Points:", createAssignmentWindow);
    QLineEdit *scoreLineEdit = new QLineEdit(createAssignmentWindow);
    QHBoxLayout *scoreLayout = new QHBoxLayout();
    scoreLayout->addWidget(scoreLabel);
    scoreLayout->addWidget(scoreLineEdit);

    // Submit button
    QPushButton *submitButton = new QPushButton("Submit", createAssignmentWindow);
    connect(submitButton, &QPushButton::clicked, createAssignmentWindow, &QDialog::accept);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(assignmentTypeLayout);
    mainLayout->addLayout(scoreLayout);
    mainLayout->addWidget(submitButton);
    createAssignmentWindow->setLayout(mainLayout);

    // Execute Dialog
    int result = createAssignmentWindow->exec();
    if (result == QDialog::Accepted) {
        QString assignmentType = assignmentTypeComboBox->currentText();
        int score = scoreLineEdit->text().toInt();
        AssignmentFactory af;
        course->addAssignment(af.createAssignment(assignmentType, score));
        updateAssignmentList();
    }
}

void teacherCourseViewWindow::updateAssignmentList()
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

void teacherCourseViewWindow::on_exitButton_clicked()
{
    this->close();
    teacherWindow->show();
}

