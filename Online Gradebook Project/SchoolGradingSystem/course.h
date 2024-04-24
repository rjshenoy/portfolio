#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>
using namespace std;
#include <vector>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include "assignment.h"


class Student;
class Teacher;
class Course
{
public:
    Course(string name, int classID);
    Course(string name, int classID, Teacher* t);
    int getClassID();
    string getClassName();
//    Teacher getTeacher() const;

    vector<Student> getStudents();
    void assignTeacher(Teacher* t);
    void addStudent(Student s);
    void removeStudent(Student s);
    void printGradesHelper(QWidget* parent);
    void addAssignment(Student* s, Assignment* a);
    void addAssignment(Assignment* a);
    int getStudentGrade(Student s);
//    map<Student*, Assignment*> assignments;
    vector<Assignment*> getAllAssignments();

private:
    int classID;
    string name;
    Teacher* teacher;
    vector<Student> students;
    map<Student*, Assignment*> assignments;
    vector<Assignment*> allAssignments;


};

#endif // COURSE_H
