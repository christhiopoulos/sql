#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "classes.hpp"

using namespace std;

Professor::~Professor(void) {
    //Deleting all the memory we have 
    // allocated from the heap
    for (int i = 0; i < courses_teaching.size(); i++) {
        delete courses_teaching[i];
    }
}

Professor::Professor(const Professor& obj) {
    this->surname = obj.surname;
    this->email = obj.email;
    this->name = obj.name;
    this->age = obj.age;
    this->size++; //We are creating a new person
    for (int i = 0; i < obj.courses_teaching.size(); i++) {
        this->courses_teaching.push_back(new Course(*courses_teaching[i]));
    }

}

Professor::Professor(string name,int age,string email,string surname):
    //Initializer list for the super class
    Person(name,age,email,surname) {
}

Professor::Professor(string name,int age,string email,string surname ,vector<Course*> vec):courses_teaching(vec),Person(name,age,email,surname){
    
}

void Professor::add_course(Course course){ 
    try {
        //Allocates the new course dynamicly
        Course* course_ptr=new Course(course); 
        courses_teaching.push_back(course_ptr);
    }
    catch(bad_alloc) {
        cerr << "Not enough space" << endl;
        exit(-1);
    }
}

bool Professor::remove_course(Course course){ 
    for(int i=0;i<courses_teaching.size();i++){
        if(course==*courses_teaching[i]){
            Course* temp = courses_teaching[i];
            courses_teaching[i] = courses_teaching[courses_teaching.size() - 1];
            courses_teaching[courses_teaching.size() - 1] = temp; 
            courses_teaching.pop_back();
            return true;
        }    
    }
    return false;
    
}

vector<Course> Professor::getCourses(void) {
    vector<Course> vec;
    for (int i = 0; i < courses_teaching.size(); i++) {
        vec.push_back(*courses_teaching[i]); //We are returning the values not the pointers
    }
    return vec;
}

bool Professor::is_teaching(Course course){
    // Simple sequental search
    for(int i=0;i<courses_teaching.size();i++){
        if(course==*courses_teaching[i]){
            return true;
        }    
    } 
    return false;       
}

void Professor::addGrades(Course course,vector<pair<Student,int>> Grades) {
    for (auto temp: Grades) {
        //temp.first is a student
        // temp.second is their grade in the course 
        temp.first.add_passed_course(course,temp.second);
    }
}

istream& operator>>(istream& str,Professor& obj){
    cout << "Enter person's name: ";
    str >> obj.name;
    cout << "Enter his surname: ";
    str >> obj.surname;
    cout << "Enter his age: ";
    str >> obj.age;
    cout << "Enter his email: ";
    str >> obj.email; 
    return str;

}

ostream& operator<<(ostream& str, Professor& obj) {
str << obj.name << " ";
str << obj.surname << " ";
str << obj.age << " ";
str << obj.email << endl;
return str;

}

bool  Professor::operator==(Professor std2) {
    return name == std2.name && surname == std2.surname;
}

