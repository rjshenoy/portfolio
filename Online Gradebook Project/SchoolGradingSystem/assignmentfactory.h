
#ifndef ASSIGNMENTFACTORY_H
#define ASSIGNMENTFACTORY_H

#include "assignment.h"
#include <QString>

/*
 * Assignment Factory
 * uses Factory pattern
 * creates Assignment objects
*/

class AssignmentFactory
{

    public:
        AssignmentFactory();
        Homework* createHomework(string name);
        Quiz* createQuiz(string name);
        Exam* createExam(string name);
        Assignment* createAssignment(QString type, int totalScore);

};

#endif // ASSIGNMENTFACTORY_H
