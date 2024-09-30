#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "classes.hpp"

using namespace std;

Course::Course(){
}

//We are using an initialiser list
Course::Course(int semester,string name,int ects,bool mandatory):
    semester(semester),name(name),ects(ects),mandatory(mandatory){

} 

Course::Course(const Course& obj) {
    this->semester = obj.semester;
    this->name = obj.name;
    this->ects = obj.ects;
    this->mandatory = obj.mandatory;
}

void Course::move_semesters(int sem2){
    semester=sem2;
}

int Course::getSemester(){
    return semester;
}

string Course::getName(){
    return name;
}

int Course::get_ects(){
    return ects;
}

bool Course::is_mandatory(){
    return mandatory;
}

bool Course::is_choice(){
    return !mandatory;
}

bool Course::operator==(Course course2) {
    return this->name == course2.name;
} 


istream& operator>>(istream& str,Course& obj){
    cout<<"enter courses's name"<<endl;
    str>>obj.name;
    cout<<"enter course's semester"<<endl;
    str>>obj.semester;
    cout<<"enter courses's ects"<<endl;
    str>>obj.ects;
    cout<<"is the course mandatory (y/n)"<<endl;
    string ans;
    str>> ans; 
    obj.mandatory = (ans == "y") ? true : false;
    return str;

} 

ostream& operator<<(ostream& str,Course obj){
    str<< obj.name<<" ";
    str<< obj.semester<<" ";
    str<< obj.ects<<" ";
    str<< ((obj.mandatory == true) ? "y" : "n" ) << endl;
    return str;
} 
