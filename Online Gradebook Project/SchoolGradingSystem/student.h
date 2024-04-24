
#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include "course.h"


class Student
{

    public:

        Student();
        Student(string name, string username, string password);

        // Getters
        int getID();
        string getName();
        string getUsername();
        vector<Course*> getCourses();

        bool verifyPassword(string pass_);

        void assignCourse(Course* c);

    private:

        static int currentID;

        int id;
        string name;
        string username;
        string password;
        vector<Course*> courses;

};

#endif // STUDENT_H
