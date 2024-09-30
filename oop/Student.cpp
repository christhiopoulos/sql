#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "classes.hpp"

using namespace std;

bool operator<(const Course& c1,const Course& c2) {
    Course temp1 = c1;
    Course temp2 = c2;
    return temp1.getName() < temp2.getName();
}


Student::~Student(void) {
    for (int i = 0; i < courses_taking.size(); i++) {
        delete courses_taking[i];
    }
}

Student::Student(const Student& obj) {
    this->surname = obj.surname;
    this->email = obj.email;
    this->name = obj.name;
    this->age = obj.age;
    // cout << "Creating a Person" << endl;
    this->size++;
    for (int i = 0; i < obj.courses_taking.size(); i++) {
        this->courses_taking.push_back(new Course(*courses_taking[i]));
    }
    this->A_M = obj.A_M;
    this->semester = obj.semester;
    this->grades = obj.grades;

}

Student::Student(void):Person() {
        }

        Student::Student(string name,int age,string email,string surname,string A_M,int semester):A_M(A_M),semester(semester),Person(name,age,email,surname){
            
        }

        void Student::set_semester(int sem){
            semester=sem;
        }

       
        void Student:: set_A_M(string a_m){
            A_M=a_m;
        }

        // void set_semester(int sem){
        //     semester=sem;
        // }

        //Increases it's semester by 1
        void Student::increaseSemester(void) {
            semester++;
        }

        string Student::get_A_M(){
            return A_M;
        }

        int Student:: getSemester(){
            return semester;
        }

        void Student:: add_course(Course course){
            try {
                Course* course_ptr=new Course(course); 
                courses_taking.push_back(course_ptr);
            }
            catch(bad_alloc) {
                cerr << "Not enough space" << endl;
            }
        }

        void Student:: add_passed_course(Course course,int grade){
            grades.erase(course);
            grades.insert(pair<Course,int>(course,grade));
        }

        void Student:: remove_course(Course course){
            for(int i=0;i<courses_taking.size();i++){
                if(course== (*courses_taking[i])){
                    Course* temp = courses_taking[i];
                    courses_taking[i] = courses_taking[courses_taking.size() - 1];
                    courses_taking[courses_taking.size() - 1] = temp; 
                    courses_taking.pop_back();
                    return;
                }    
            }
        
        }

        bool Student:: has_passed(Course course){
            return grades[course] >= 5;
        }

        bool Student:: is_taking(Course course){
            for(int i=0;i<courses_taking.size();i++){
                if(course==*courses_taking[i]){
                    return true;
                }    
            } 
            return false;       
        }

        bool Student:: allowed_degree(vector<Course> courses,int ects,int years) { 
            int totalECTS = 0;
            for (int i = 0; i < courses.size(); i++) {
                Course x = courses[i];
                if (x.is_mandatory() && grades[x] < 5) 
                    return false;
                // Και τα προαιρετικά μετράνε στα συνολικά ECTS
                else if (grades[x] >= 5)
                    totalECTS += x.get_ects();
            } 
            return  (totalECTS >= ects && semester / 2 >= years);
        }

        int Student:: getGrade(Course course) {
            //Τσεκαρε αν υπάρχει
            // Αν δεν υπάρχει γύρισε -1
            int x = grades[course];
            return x;
        }
        istream& operator>>(istream& str,Student& obj){
        cout << "Enter person's name: ";
        str >> obj.name;
        cout << "Enter his surname: ";
        str >> obj.surname;
        cout << "Enter his age: ";
        str >> obj.age;
        cout << "Enter his email: ";
        str >> obj.email; 
        cout<<"enter student's AM"<<endl;
        str>>obj.A_M;
        cout<<"enter students's semester"<<endl;
        str>>obj.semester;
        return str;

    }
    ostream& operator<<(ostream& str, Student& obj) {
    str << obj.name << " ";
    str << obj.surname << " ";
    str << obj.age << " ";
    str << obj.email << " ";
    str << obj.A_M << " ";
    str << obj.semester<< endl;

    return str;
}

    bool Student:: operator==(Student std2) {
        return A_M == std2.A_M;
    }
