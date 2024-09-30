#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "classes.hpp"

class DIVISION_BY_ZERO{};

class FILE_DOESNT_EXIST{
    private:
        string name;
    public:
        FILE_DOESNT_EXIST(string name):name(name){}
        string getName() {
            return name;
        }
};

int main(void) {
    try {
        int option;
        Professor professor;
        Secretary sec(8,20);
        Student stu;
        int option_2;
        Course course;
        ifstream CoursesFile;
        ifstream StudentsFile;
        ifstream ProfessorsFile;
        CoursesFile.open("Courses.txt",ios::in);
        if (!CoursesFile) 
            throw FILE_DOESNT_EXIST("Courses.txt");
        StudentsFile.open("Students.txt",ios::in);
        if (!StudentsFile) 
            throw FILE_DOESNT_EXIST("Students.txt");
 
        ProfessorsFile.open("Professors.txt",ios::in);
        if (!ProfessorsFile) 
            throw FILE_DOESNT_EXIST("Professors.txt");
 
        while (!ProfessorsFile.eof()) {
            Professor prof("",0,"","");
            ProfessorsFile >> prof;
            if (prof.getName() != "")
                sec.addProfessor(prof); 
        }

        while (!CoursesFile.eof()) {
            Course crs(0,"",0,false);
            CoursesFile >> crs;
            if (crs.getName() != "")
                sec.addCourse(crs);
        }

        while (!StudentsFile.eof()) {
            Student std("",0,"","","",0);
            StudentsFile >> std;
            if (std.getName() != "")
                sec.addStudent(std);
        }
        
        do{
            cout << "Select one of the following options:" << endl;
            cout << "\t1) Add,change or remove a Professor" << endl;
            cout << "\t2) Add,change or remove a Student" << endl;
            cout << "\t3) Add,change,or remove a Course" << endl;
            cout << "\t4) Set the professors of a course" << endl;
            cout << "\t5) Sign a student to a course"  << endl;
            cout << "\t6) Print the students who passed a course" << endl;
            cout << "\t7) Print the statistics of your courses as a professor" << endl;
            cout << "\t8)Print your grades as a student" << endl; 
            cout << "\t9)Print the students that can get a degree" << endl;
            cout << "\t10) Add the grades for a course" << endl;
            cout << "\t11)Exit" << endl;


            cin>>option;
            if(option==1){
                cout << "Enter 1 to enter a new professor" << endl; 
                cout << "Enter 2 to change a professor" << endl;
                cout << "Enter 3 to remove a professor" << endl;
                cin>>option_2;
                if(option_2==1){
                    cin>>professor;
                    sec.addProfessor(professor);
                }
                if(option_2==2){
                        cout << "Enter professors name and surname" << endl;
                        string name;
                        string surname;
                        cin >> name;
                        cin >> surname;
                        Professor old_prof = sec.findProfessorByName(name,surname);
                        cout << "Enter the attributes of the professor" << endl;
                        Professor new_prof;
                        cin>>new_prof;
                        sec.changeProfessor(old_prof,new_prof);               
                }
                if(option_2==3){
                    cout << "Enter professors name and surname to remove" << endl;
                    string name,surname;
                    cin >> name;
                    cin >>surname;
                    Professor remove_professor = sec.findProfessorByName(name,surname);
                    sec.removeProfessor(remove_professor);
                }
                
            }
            else if(option==2){
                cout << "Enter 1 to enter a new student" << endl; 
                cout << "Enter 2 to change a student" << endl;
                cout << "Enter 3 to remove a student" << endl;
    
                cin>>option_2;
                if(option_2==1){
                    cin>>stu;
                    sec.addStudent(stu);
                }
                else if(option_2==2){
                    cout << "Enter students AM to change" << endl;
                    string am;
                    cin >> am;
                    Student old_stu = sec.findStudentBySerialNumber(am);
                    cout << "Enter the attributes of the new student" << endl;
                    Student new_stu;
                    cin >> new_stu;
                    sec.changeStudent(old_stu,new_stu);               
                }
                else if(option_2==3){
                    cout << "Enter students AM to remove" << endl;
                    string am;
                    cin >>am;
                    Student remove_student = sec.findStudentBySerialNumber(am);
                    sec.removeStudent(remove_student);
                }
                
            }
            else if(option==3){
                cout << "Enter 1 to enter a new course" << endl; 
                cout << "Enter 2 to change a course" << endl;
                cout << "Enter 3 to remove a course" << endl;
    
                cin>>option_2;
                if(option_2==1){
                    cin>>course;
                    sec.addCourse(course);
                }
                else if(option_2==2){
                    cout << "Enter course's name to change" << endl;
                    string name;
                    cin >> name;
                    Course old_course = sec.findCourseByName(name);
                    Course new_course;
                    cout << "Enter the attributes of the course" << endl;
                    cin >> new_course;
                    sec.changeCourse(old_course,new_course);               
                }
                else if(option_2==3){
                    cout << "Enter courses name to remove" << endl;
                    string name;
                    cin >> name;
                    Course remove_course = sec.findCourseByName(name);
                    sec.removeCourse(remove_course);
                }
                
            }
            else if (option==4){
                string name;
                cout << "Enter the courses name: " << endl;
                cin>>name;
                course = sec.findCourseByName(name);
                vector<Professor> vec;
                string ans;
                do {
                    cout << "Enter the professors name and surname: " << endl;
                    string name,surname;
                    cin >> name;
                    cin >> surname;
                    Professor prof = sec.findProfessorByName(name,surname);  
                    if (prof.getName() == "") {
                        cout << "Didn't find professor" << endl;
                    }
                    else {
                        vec.push_back(prof);
                    }
                    cout << "Do you want to continue (y/n): ";
                    cin >> ans;
                } while (ans == "y");
                sec.setProfessors(course,vec);
            }
            else if(option==5){
                cout << "Enter the students serial number: " << endl;
                string am; 
                cin>>am;
                stu = sec.findStudentBySerialNumber(am);
                if (stu.getName() == "") {
                    cout << "Didn't find student" << endl;
                }
                else {
                    cout << "Enter the courses name: " << endl;
                    string cname;
                    cin>>cname;
                    course = sec.findCourseByName(cname);
                    if (course.getName() == "") {
                        cout << "Didn't find course" << endl;
                    }
                    else {
                        Student temp=stu;
                        stu.add_course(course);
                        sec.changeStudent(temp,stu);
                    }
                }
            }

            else if (option==6){   
                ofstream Output;
                string courseName;
                cout << "Enter courses name: " << endl;
                cin >> courseName;
                Output.open("StudentsWhoPassed" + courseName + ".txt");
                course = sec.findCourseByName(courseName);
                vector<Student> passed = sec.PeoplePassedCourse(course);
                for (int i = 0; i < passed.size(); i++) {
                    Output << passed[i] << endl;
                }
                cout << "The students are saved in the file StudentsWhoPassed" + courseName + ".txt" << endl;
            }
            else if (option==7){
                cout<<"enter professors name and surname: " << endl;
                string name,surname;
                cin >> name;
                cin >> surname;
                professor = sec.findProfessorByName(name,surname);
                vector<Course> courses = professor.getCourses();
                for (int i = 0; i < courses.size(); i++) {
                    Course course = courses[i];
                    Semester sem = sec.getSemester(course.getSemester());
                    vector<Student> all  = sem.getStudents();
                    vector<Student> passed = sec.PeoplePassedCourse(course);

                    if (all.size() == 0)
                        throw(DIVISION_BY_ZERO());
                    double percentage = ((double)passed.size() / all.size()) * 100; //Διαιρεση με 0 exception
                    int passedCounter = passed.size(); //

                    int sum = 0;
                    for (int i = 0; i < all.size(); i++) {
                        sum += all[i].getGrade(course);
                    }

                    double gradePerc = (double)sum / all.size(); //
                    cout << "Students passed the course: " << passedCounter << endl;
                    cout << "Passed percentage: " << percentage  << "%" << endl;
                    cout << "Average grades: " << gradePerc << endl;
                }
            }
            else if(option==8){
                cout<<"enter semester"<<endl;
                int sem;
                cin>>sem;
                Semester currSemester(sem);
                cout<<"enter student's serial number: "<<endl;
                string am;
                cin>>am;
                stu = sec.findStudentBySerialNumber(am);
                if (stu.getName() == "") {
                    cout << "Didn't find student" << endl;
                }
                vector<Course> SemCourses = currSemester.getCourses(); 
                vector<Student> stds = sec.getStudents();
                for (int i = 0; i < stds.size(); i++) {
                    if (stds[i] == stu)  {
                        stu = stds[i];
                        break;
                    }
                }
                for (int i = 0; i < SemCourses.size(); i++) {
                    cout << SemCourses[i].getName() << ": " << stu.getGrade(SemCourses[i]) << endl;
                }
                //Για όλες τις χρονιες (ιδιες μεταβλητες σε σχόλιο)
                // Semester currSemester(3);
                // Student student;
                int option_2;
                cout << "Select one of the following options:" << endl;
                cout << "1) Get your yearly marks" << endl;
                cout << "2) Get your current semester's marks" << endl;
                cin >> option_2;
                if (option_2 == 1) {
                    vector<Course> YearCourses = sec.getCourses(); 
                    for (int i = 0; i < YearCourses.size(); i++) {
                        if (stu.getSemester() >= YearCourses[i].getSemester()) {
                            cout << YearCourses[i].getName() << ": " << stu.getGrade(YearCourses[i]);
                        }
                    }
                }
                else {
                    vector<Course> monthlyCourses = sec.getCourses(); 
                    for (int i = 0; i < monthlyCourses.size(); i++) {
                        if (stu.getSemester() == monthlyCourses[i].getSemester()) {
                            cout << monthlyCourses[i].getName() << ": " << stu.getGrade(monthlyCourses[i]);
                        }
                    }
                }
        }
            else if(option==9){
                vector<Student> students = sec.getStudents();
                for (int i = 0; i < students.size(); i++) {
                    if (students[i].allowed_degree(sec.getCourses(),sec.getRequiredEcts(),sec.getYears())) {
                        cout << students[i] << endl;
                    }
                }
            }
            else if (option == 10) {
                Course course;
                cout << "Enter courses name: " << endl;
                string cname;
                cin>>cname;
                course = sec.findCourseByName(cname);
                if (course.getName() == "") {
                    cout << "Didn't find course" << endl;
                }
                Semester sem = sec.getSemester(course.getSemester());
                vector<Student> studs = sem.getStudents();
                for (int i = 0; i < studs.size(); i++) {
                    int grade;
                    cout << "Enter the grade for the following student: " << endl;
                    cout << studs[i];
                    cin >> grade;
                    Student temp = studs[i];
                    studs[i].add_passed_course(course,grade);
                    sec.changeStudent(temp,studs[i]);
                }
            }

        }while(option!=11);
        ofstream output;
        output.open("Courses.txt",ios::out|ios::trunc);
        vector<Course> courses = sec.getCourses();
        for (int i = 0; i < courses.size(); i++) {
            output << courses[i];
        }

        output.close();
        output.open("Professors.txt",ios::out|ios::trunc);
        vector<Professor> professors = sec.getProfessors();
        for (int i = 0; i < professors.size(); i++) {
            output << professors[i];
        }

        output.close();
        output.open("Students.txt",ios::out|ios::trunc);
        vector<Student> students = sec.getStudents();
        for (int i = 0; i < students.size(); i++) {
            output << students[i]; 
        } 

        output.close();

    }
    catch(DIVISION_BY_ZERO) {
        cerr << "ERROR!!!Division by 0 detected" << endl;
    }
    catch(FILE_DOESNT_EXIST obj) {
        cerr << "ERROR!!! File " + obj.getName() + " doesn't exist" << endl;
    }
}
