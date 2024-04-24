
#ifndef TEACHER_H
#define TEACHER_H

#include <vector>
#include "course.h"


class Teacher
{

    public:

        Teacher();
        Teacher(string name, string username, string password);

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

#endif // TEACHER_H
