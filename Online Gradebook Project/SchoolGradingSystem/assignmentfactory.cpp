
#include "assignmentfactory.h"

AssignmentFactory::AssignmentFactory()
{

}

Homework* AssignmentFactory::createHomework(string name) {
    return new Homework(name, 100);
}

Exam* AssignmentFactory::createExam(string name) {
    return new Exam(name, 150);
}

Quiz* AssignmentFactory::createQuiz(string name) {
    return new Quiz(name, 20);
}

Assignment* AssignmentFactory::createAssignment(QString type, int totalScore) {
    if (type == "Exam") {
        return new Exam("Exam", totalScore);
    } else if (type == "Quiz") {
        return new Quiz("Quiz", totalScore);
    } else if (type == "Homework") {
        return new Homework("Homework", totalScore);
    }
    return nullptr;
}
