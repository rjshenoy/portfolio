
#include "assignment.h"
Assignment::Assignment(){}
Assignment::Assignment(string name, int totalPoints)
{
    title = name;
    this->totalPoints = totalPoints;
}

void Assignment::inputScore(Student* student, int score) {

    scores.insert(make_pair(student, score));

}

int Assignment::getScore(Student* student) {

    return scores[student];

}

map<Student*, int> Assignment::getAllScores() {

    return scores;

}

void Assignment::updateScore(Student* student, int score) {

    scores[student] = score;

}

int Assignment::getWeight() {

    return weight;

}

string Assignment::getTitle() const {

    return title;
}
Homework::Homework(string name, int totalPoints) : Assignment(name, totalPoints) {

    weight = 50;

}

Quiz::Quiz(string name, int totalPoints) : Assignment(name, totalPoints) {

   weight = 20;

}

Exam::Exam(string name, int totalPoints) : Assignment(name, totalPoints) {

    weight = 30;

}

AssignmentDecorator::AssignmentDecorator(Assignment* a) :
    assignment(a)
{}

CurvedAssignment::CurvedAssignment(Assignment* a, int curve_) :
    AssignmentDecorator(a),
    curve(curve_)
{}

map<Student*, int> CurvedAssignment::getAllScores()
{
    map<Student*, int> curvedScores;
    for (auto const& [student, score] : scores)
    {
        curvedScores[student] = score + this->curve;
    }
    return curvedScores;
}
