#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "classes.hpp"

using namespace std;


Secretary::Secretary(){ //Constructor without parameters

        }

        Secretary ::Secretary(int semester,int requiredECTS): requiredECTS(requiredECTS){
            try {
                for (int i = 0; i < semester; i++) {
                    Semester* sem = new Semester(i + 1);
                    semesters.push_back(sem);
                }
            }
            catch(bad_alloc) {
                cerr << "Not enough space" << endl;
            }
        }

        Secretary ::~Secretary(void){
            for (int i = 0; i < semesters.size(); i++) {
                delete semesters[i];
            }
            for (int i = 0; i < students.size(); i++) {
                delete students[i];
            }
            for (int i = 0; i < professors.size(); i++) {
                delete professors[i];
            }
        } //Destructor

        // Secretary(const vector<Professor>& professors,const vector<Student>& students,const vector<Course>& courses,int requiredECTS)
        // :requiredECTS(requiredECTS){ //Constructor with a Vector that contains persons as parameter
        //     for (int i = 0; i < professors.size(); i++) {
        //         this->addProfessor(professors[i]);
        //     }
        //     for (int i = 0; i < students.size(); i++) {
        //         this->addStudent(students[i]);
        //     }
        //     for (int i = 0; i < courses.size(); i++) {
        //         this->addCourse(courses[i]);
        //     }
        // }

        Secretary ::Secretary(const vector<Professor>& professors,const vector<Student>& students,const vector<Semester*>& semesters,int requiredECTS)
        :requiredECTS(requiredECTS){ //Constructor with a Vector that contains persons as parameter
            for (int i = 0; i < professors.size(); i++) {
                this->addProfessor(professors[i]);
            }
            for (int i = 0; i < students.size(); i++) {
                this->addStudent(students[i]);
            }
            for (int i = 0; i < semesters.size(); i++) {
                vector<Course> courses = semesters[i]->getCourses(); 
                for (int j = 0; j < courses.size(); j++) {
                    this->addCourse(courses[j]);
                }
            }
        }



        // Secretary(const Secretary& secretary); //Copy constructor

        Professor Secretary :: findProfessorByName(string name,string surname){ //Returns true if a person exist in the secretary
            Professor person(name,0,"",surname);
            for(int i = 0; i < professors.size();i++){
                if(*professors[i] == person){
                    return *professors[i];
                }
            }
            return Professor("");
        }

        Course Secretary ::findCourseByName(string name){ //Returns true if a person exist in the secretary
            Course course(0,name,0,false); 
            for (int i = 0; i < semesters.size(); i++) {
                Semester sem = *semesters[i];
                Course temp = sem.findCourse(course); 
                if (temp.getName() == name)
                    return temp;
            }
            return Course(0,"",0,false);
        }



        Student Secretary :: findStudentBySerialNumber(const string& AM){ //Returns true if a person exist in the secretary
            Student person("",0,"","",AM,0);
            for(int i = 0; i < students.size();i++){
                if(*students[i] == person){
                    return *students[i];
                }
            }
            return Student("",0,"","","",0);
        }



        void Secretary ::addProfessor(Professor person) { //Returns a new secretary with all the persons
                                            // of the previous secretary + the new one
            try {
                Professor* person_ptr = new Professor(person);
                this->professors.push_back(person_ptr);
            }
            catch(bad_alloc) {
                cerr << "Not enough space" << endl;
            }
        }   
        
        
        void Secretary ::addCourse(Course course) { //Returns a new secretary with all the persons
                                            // of the previous secretary + the new one
            this->semesters[course.getSemester() - 1]->addCourse(course); 
        }    

        void Secretary :: addStudent(Student person) { //Returns a new secretary with all the persons
                                            // of the previous secretary + the new one
            try {
                Student* person_ptr = new Student(person);
                // Secretary temp = *this;
                this->students.push_back(person_ptr); 
                /* Να τον γραψουμε στα εξάμηνα που δηλώνει */
                for (int i = 0; i < person.getSemester(); i++) {
                    if (person.getSemester() - 1 < i) 
                        break;
                    this->semesters[i]->addStudent(person);
                }
            }
            catch(bad_alloc) {
                cerr << "Not enough space" << endl;
            }
        }



        void Secretary ::removeProfessor(Professor professor) {
            for(int i=0;i<professors.size();i++){
                if(professor == (*professors[i])){
                    Professor* temp = professors[i];
                    professors[i] = professors[professors.size() - 1];
                    professors[professors.size() - 1] = temp; 
                    professors.pop_back();
                    return;
                }    
            }
        }

        void Secretary :: removeCourse(Course course) {
            semesters[course.getSemester() - 1]->remove_course(course);
            for (int i = 0; i < students.size(); i++) {
                students[i]->remove_course(course);
            }
            for (int i = 0; i < professors.size(); i++) {
                professors[i]->remove_course(course);
            }
        }

        void Secretary :: removeStudent(Student student) {
            for(int i=0;i<students.size();i++){
                if(student== (*students[i])){
                    Student* temp = students[i];
                    students[i] = students[students.size() - 1];
                    students[students.size() - 1] = temp; 
                    students.pop_back();
                    break;
                }    
            }
            for (int i = 0; i < semesters.size(); i++) {
                semesters[i]->removeStudent(student);
            }
        }

        void Secretary ::changeStudent(Student old,Student newStudent) {
            //Τον βγάζουμε και τον ξαναβάζουμε
            this->removeStudent(old);
            this->addStudent(newStudent); //!!!!!!!!!!! kane add student
        }

        void Secretary ::changeProfessor(Professor old,Professor newProf) {
            this->removeProfessor(old);
            // this->removeProfessor(newProf);
            this->addProfessor(newProf); //!!!!!!!!!!! kane add student
        }

        void Secretary :: changeCourse(Course old,Course newCourse) {
            this->removeCourse(old);
            this->addCourse(newCourse); //!!!!!!!!!!! kane add student
        }



        
        void Secretary :: moveSemester(Course course,int newSemester) {
            semesters[course.getSemester() - 1]->remove_course(course);
            course.move_semesters(newSemester);
            semesters[newSemester - 1]->addCourse(course);
        }

        void Secretary ::setProfessors(Course course,vector<Professor> profs) {
            for (int k = 0; k < profs.size(); k++) {
                for(int i=0;i<this->professors.size();i++){
                    if(profs[k] == (*professors[i])){
                        professors[i]->add_course(course);
                        break;
                    }    
                }           
            }
        }

        vector<Student> Secretary ::PeoplePassedCourse(Course course) {
            Semester semester = *semesters[course.getSemester() - 1];
            vector<Student> students = semester.getStudents();
            vector<Student> passed;
            for (int i = 0; i < students.size(); i++) {
                if (students[i].has_passed(course)) {
                    passed.push_back(students[i]);
                }
            }
            return passed;
        }

        Semester Secretary ::getSemester(int semester) {
            return *semesters[semester - 1];
        }

        //Αν το semester είναι 0 επιστρέφει όλα τα μαθήματα
        // αλλιώς τα μαθήματα του συγκεκριμένου εξαμήνου
        vector<Course> Secretary ::getCourses(void) {
            vector<Course> courses;
            for (int i = 0; i < semesters.size(); i++) {
                vector<Course> semCourses = semesters[i]->getCourses();
                for (int j = 0; j < semCourses.size(); j++) {
                    courses.push_back(semCourses[j]);
                }
            }
            return courses;
        }

        vector<Course> Secretary ::getSemesterCourses(int semester) {
            vector<Course> courses;
            vector<Course> semCourses = semesters[semester - 1]->getCourses();
            for (int j = 0; j < semCourses.size(); j++) {
                courses.push_back(semCourses[j]);
            }
            return courses;
        }

        int Secretary ::getRequiredEcts() {
            return requiredECTS;
        }

        int Secretary ::getYears() {
            return semesters.size() / 2; 

        }

        vector<Student> Secretary :: getStudents() {
            vector<Student> vec;
            for (int i = 0; i < students.size(); i++) {
                vec.push_back(*students[i]);
            }
            return vec;           
        }

        vector<Professor> Secretary ::getProfessors() {
            vector<Professor> vec;
            for (int i = 0; i < professors.size(); i++) {
                vec.push_back(*professors[i]);
            }
            return vec;           
        }