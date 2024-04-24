#include "course.h"
#include "student.h"

// Constructors
Course::Course(string name_, int classID_)
{
    name = name_;
    classID = classID_;
}

Course::Course(string name, int classID, Teacher *t)
{
    this->name = name;
    this->classID = classID;
    this->teacher = t;
    this->allAssignments = vector<Assignment*>();
}

//int Class::getStudentGrade(Student s) {



//}

// Getters
int Course::getClassID() { return classID; }
string Course::getClassName() { return name; }
//    Teacher getTeacher() const;
vector<Student> Course::getStudents() { return students; }

void Course::addStudent(Student s) {
    students.push_back(s);
}

void Course::removeStudent(Student s) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].getUsername() == s.getUsername()) {
            students.erase(students.begin()+i);
        }
    }
}

void Course::assignTeacher(Teacher *t) { this->teacher = t; }



int Course::getStudentGrade(Student s) {

//    for (pair<Assignment, Student> assignment: assignments) {

    // need to calculate grade before returning

//    }

    return NULL;

}
void Course::addAssignment(Student* s, Assignment* a) {

    assignments.insert(make_pair(s,a));

}

void Course::addAssignment(Assignment* a) { this->allAssignments.push_back(a); }
vector<Assignment*> Course::getAllAssignments() { return this->allAssignments; }
