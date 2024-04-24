
#include "student.h"

int Student::currentID = 0;

Student::Student()
{
    this->name = "Daniel Green";
    this->courses = vector<Course*>();
}

Student::Student(string name, string username, string password)
{
    this->name = name;
    this->username = username;
    this->password = password;
    this->id = currentID;
    currentID += 1;
}

string Student::getName() { return this->name; }
string Student::getUsername() { return this->username; }
vector<Course*> Student::getCourses() { return this->courses; }

bool Student::verifyPassword(string pass_)
{
    return (pass_ == this->password);
}

void Student::assignCourse(Course* c)
{
    this->courses.push_back(c);
}
