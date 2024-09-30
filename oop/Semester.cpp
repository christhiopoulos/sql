#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "classes.hpp"


using namespace std;


//Using initializer list
Semester::Semester(int semester): semester(semester) {

}

Semester::Semester(const Semester& obj) {
    this->semester = obj.semester;
    //We are reallocating the data from obj
    for (int i = 0; i < obj.courses.size(); i++) {
        courses.push_back(new Course(*obj.courses[i]));
    }
    for (int i = 0; i < obj.students.size(); i++) {
        students.push_back(new Student(*obj.students[i]));
    }
}

Semester::~Semester(void) {
    for (int i = 0; i < courses.size(); i++) {
        delete courses[i];
    }
    for (int i = 0; i < students.size(); i++) {
        delete students[i];
    }
}



void Semester::addCourse(Course course) {
    try {
        Course* ptr = new Course(course);
        courses.push_back(ptr);
    }
    catch(bad_alloc) {
        cerr << "Not enough space" << endl;
        exit(- 1);
    }
}

vector<Course> Semester::getCourses(void) {
    vector<Course> vec;
    for (int i = 0; i < courses.size(); i++) {
        vec.push_back(*courses[i]);
    }
    return vec;
}


int Semester::getSemester(void) {
    return semester;
}

vector<Student> Semester::getStudents(void) {
    vector<Student> vec;
    for (int i = 0; i < students.size(); i++) {
        vec.push_back(*students[i]);
    }
    return vec;
}

bool Semester::remove_course(Course course) {
    for(int i=0;i<courses.size();i++){
        if(course== (*courses[i])){
            Course* temp = courses[i];
            courses[i] = courses[courses.size() - 1];
            courses[courses.size() - 1] = temp; 
            courses.pop_back();
            return true;
        }    
    }
    return false;
}

Course Semester::findCourse(Course course) {
    for(int i=0;i<courses.size();i++){
        if(course== (*courses[i])){
            return *courses[i];
        }    
    }
    return Course(0,"",0,false);
}

void Semester::addStudent(Student student) {
    try {
        Student* std = new Student(student);
        students.push_back(std);
    }
    catch(bad_alloc) {
        cerr << "Not enough space" << endl;
        exit(-1);
    }
}

bool Semester::removeStudent(Student student) {
    for(int i=0;i<students.size();i++){
        if(student== (*students[i])){
            Student* temp = students[i];
            students[i] = students[students.size() - 1];
            students[students.size() - 1] = temp; 
            students.pop_back();
            return true;
        }    
    }
    return false;
}

bool Semester::findStudent(Student student) {
    for(int i=0;i<students.size();i++){
        if(student== (*students[i])){
            return true;
        }    
    }
    return false;
}
