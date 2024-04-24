
#include "teacher.h"

int Teacher::currentID = 0;

Teacher::Teacher()
{
    this->name = "Rob Bob";
    this->courses = vector<Course*>();
}

Teacher::Teacher(string name, string username, string password)
{
    this->name = name;
    this->username = username;
    this->password = password;
    this->id = currentID;
    currentID += 1;
}

string Teacher::getName() { return this->name; }
string Teacher::getUsername() { return this->username; }
vector<Course*> Teacher::getCourses() { return this->courses; }

bool Teacher::verifyPassword(string pass_)
{
    return (pass_ == this->password);
}

void Teacher::assignCourse(Course* c)
{
    this->courses.push_back(c);
}
