#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>


using namespace std;

#pragma once

class Course {
    private:
        int semester;
        string name;
        int ects;
        bool mandatory;
    public:
        
        Course(); //Constructor without arguments

        //Constructor with arguments
        Course(int semester,string name,int ects,bool mandatory); 

        Course(const Course& obj); //Copy constructor

        void move_semesters(int sem2); //Changes the semester of the course

        // Accessors
        int getSemester();

        string getName();

        int get_ects();

        bool is_mandatory();

        bool is_choice();

        //Equality operator
        bool operator==(Course course2); 

        // Input/Output operators   
        friend istream& operator>>(istream& str,Course& obj); 

        friend ostream& operator<<(ostream& str,Course obj); 
};

class Person {
    protected:
        //Personal data of each person
        string name,email,surname,phone;
        int age;

        //The counter of created objects
        static int size;
    public:
        Person(string name = "",int age = 0,string email = "",string surname = ""); //Constructor
        Person(const Person& obj); //Copy constructor
        ~Person(void); //Destructor
        /* Accessors */
        static int getCounter(void); //Returns the number of created objects
        string getName(void); //Returns the name of the person
        string getEmail(void); //Returns the email of the person
        string getSurname(void); //Returns the surname of the person
         int getAge(void);  //Returns the phone of the person
        /* Mutators */
        void setEmail(string email); //Changes the email of the person
        void setAge(int age); //Changes the phone of the person
        void setSurname(string surname); //Changes the surname of the person
        void setName(string name); //Changes the name of the person
        /* Operators */
        friend istream& operator>>(istream& str,Person& obj); //Input operator
        friend ostream& operator<<(ostream& str,Person& obj); //Output operator
        bool operator==(const Person& person2); //Equality operator
};


class Student : public Person {
    string A_M;
    vector<Course*> courses_taking;
    int semester;
    map<Course,int> grades;

    public:
        
        Student(void); //Constructor without arguments

        Student(const Student& obj); //

        ~Student(void);

        Student(string name,int age,string email,string surname,string A_M,int semester);   
       
        void set_A_M(string a_m);

        void set_semester(int sem);

        //Increases it's semester by 1
        void increaseSemester(void);

        string get_A_M();

        int getSemester();

        void add_course(Course course);

        void add_passed_course(Course course,int grade);

        void remove_course(Course course);

        bool has_passed(Course course);

        bool is_taking(Course course);

        bool allowed_degree(vector<Course> courses,int ects,int years);

        int getGrade(Course course);

        friend istream& operator>>(istream& str,Student& obj);

        friend ostream& operator<<(ostream& str, Student& obj);

        bool operator==(Student std2);


};


 class Professor: public Person{
    private:
        vector<Course*> courses_teaching;

    public:

        //Constructor
        Professor(string name = "",int age = 0,string email = "",string surname = "");

        Professor(string name,int age,string email,string surname ,vector<Course*> vec);

        //Destructor
        ~Professor(void);

        //Copy constructor
        Professor(const Professor& obj);

        // Adds a new course for the professor to teach 
        void add_course(Course course);

        // Removes a course that the professor is teaching
        bool remove_course(Course course);

        // Adds grades to a course for the students
        void addGrades(Course course,vector<pair<Student,int>> Grades);

        //Accessors

        vector<Course> getCourses(void);

        //Returns true if the professor is teaching that course, false otherwise
        bool is_teaching(Course course);

        // Operators 
        friend istream& operator>>(istream& str,Professor& obj);
        friend ostream& operator<<(ostream& str, Professor& obj);
        bool operator==(Professor std2);
 };


// This class repressents an academic semester
class Semester {
    private:
        int semester;
        vector<Course*> courses;
        vector<Student*> students;
    public:
        // Constructor
        Semester(int semester);

        // Copy constructor
        Semester(const Semester& obj);

        //Destructor
        ~Semester(void);

        // Inserts a course to the semesters
        void addCourse(Course course);

        //Accessors
        vector<Course> getCourses(void);

        int getSemester(void);

        vector<Student> getStudents(void);

        //Removes the course from the semester
        bool remove_course(Course course);
        
        //Returns true if the course belongs to the semester
        Course findCourse(Course course);

        // Adds a student to the semester and signs him to the courses 
        // of the semester
        void addStudent(Student student);

        // Removes a student from the semester
        bool removeStudent(Student student);

        //Returns true if the student is signed to this semester
        bool findStudent(Student student);

};

class Secretary{
    private:
        vector<Student*> students;
        vector<Professor*> professors; 
        vector<Semester*> semesters; //Τα σεμεστερ από το [0,3]
        int requiredECTS; //The amount of ECTS a student needs to acquire a degree
        
    public:     
        Secretary();

        Secretary(int semester,int requiredECTS);
        ~Secretary(void); //Destructor

        Secretary(const vector<Professor>& professors,const vector<Student>& students,const vector<Semester*>& semesters,int requiredECTS);

        // Secretary(const Secretary& secretary); //Copy constructor

        Professor findProfessorByName(string name,string surname);

        Course findCourseByName(string name);



        Student findStudentBySerialNumber(const string& AM);

        /*Operators*/
        friend istream& operator>>(istream& str,Secretary& secretary); //Input operator
        friend ostream& operator<<(ostream& str,Secretary secretary);  //Output operator

        void addProfessor(Professor person);
        
        
        void addCourse(Course course);    

        void addStudent(Student person);



        void removeProfessor(Professor professor);

        void removeCourse(Course course);

        void removeStudent(Student student);

        void changeStudent(Student old,Student newStudent);

        void changeProfessor(Professor old,Professor newProf);

        void changeCourse(Course old,Course newCourse);

        Secretary operator+(Semester semester);

        Secretary operator+=(Semester semester);

        
        void moveSemester(Course course,int newSemester);

        void setProfessors(Course course,vector<Professor> profs);

        vector<Student> PeoplePassedCourse(Course course); 

        Semester getSemester(int semester);

        //Αν το semester είναι 0 επιστρέφει όλα τα μαθήματα
        // αλλιώς τα μαθήματα του συγκεκριμένου εξαμήνου
        vector<Course> getCourses(void);

        vector<Course> getSemesterCourses(int semester);

        int getRequiredEcts();

        int getYears();

        vector<Student> getStudents();
        vector<Professor> getProfessors();

};
