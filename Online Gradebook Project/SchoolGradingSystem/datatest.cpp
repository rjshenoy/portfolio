
#include "datatest.h"

DataTest::DataTest()
{
    // Test Teachers
    this->teachers.push_back(new Teacher("John Doe", "jdoe", "test123"));
    this->teachers.push_back(new Teacher("Jeff Hoefs", "jhoefs", "hoefs123"));
    // Test Students
    this->students.push_back(new Student("James Green", "jgreen", "password123"));
    this->students.push_back(new Student("Rachel Green", "rgreen", "jamesgreensux"));
    // Test Courses
    courses = {new Course("Calculus 1", 1000), new Course("Calculus 2", 1100), new Course("Calculus 3", 1200)};
    Course *course1 = new Course("Computer Science A", 700, this->teachers[0]);
    this->teachers[0]->assignCourse(course1);
    this->students[0]->assignCourse(course1);
    Course *course2 = new Course("Computer Science B", 800, this->teachers[0]);
    this->students[0]->assignCourse(course1);
    this->students[1]->assignCourse(course1);
    this->teachers[0]->assignCourse(course2);
    this->courses.push_back(course1);
    this->courses.push_back(course2);
    // Test Assignments & Assignment Factory
    AssignmentFactory aFactory = AssignmentFactory();
    Exam* testExam1 = aFactory.createExam("Test Exam 1");
    testExam1->inputScore(students[0], 80);
    testExam1->inputScore(students[1], 75);
    Homework* testHW1 = aFactory.createHomework("Test Homework 1");
    testHW1->inputScore(students[0], 95);
    testHW1->inputScore(students[1], 100);
    Quiz* testQuiz1 = aFactory.createQuiz("Test Quiz 1");
    testQuiz1->inputScore(students[0], 87);
    testQuiz1->inputScore(students[1], 91);
    course1->addAssignment(testExam1);
    course1->addAssignment(testHW1);
    course1->addAssignment(testQuiz1);

}

Teacher* DataTest::findTeacherUser(string user_) {
    for (auto t : this->teachers)
    {
        if (t->getUsername() == user_) return t;
    }
    return nullptr;
}

Student* DataTest::findStudentUser(string user_) {

    for (auto s : this->students)
    {
        if (s->getUsername() == user_) return s;
    }
    return nullptr;

}

vector<Course*> DataTest::getCourses() {

    return courses;
}


vector<Student*> DataTest::getStudents() {

    return students;

}


vector<Teacher*> DataTest::getTeachers() {

    return teachers;

}

void DataTest::addCourse(Course* c) {

    courses.push_back(c);

}
