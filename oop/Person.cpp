#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "classes.hpp"


using namespace std;


int Person::size = 0;

//We are using an initialiser list
Person::Person(string name,int age,string email,string surname):
    name(name),email(email),surname(surname),age(age) {
    // cout << "Creating a Person" << endl;
    size++; //We created a new person
}

Person::Person(const Person& obj) {
    this->surname = obj.surname;
    this->email = obj.email;
    this->name = obj.name;
    this->age = obj.age;
    // cout << "Creating a Person" << endl;
    this->size++; //We created a new person
}


Person::~Person(void) {
    // cout << "Destroying person" << endl;
}

string Person::getName(void) {
    return name;
}

int Person::getCounter(void) {
    return size;
}

string Person::getSurname(void) {
    return surname;
}

string Person::getEmail(void) {
    return email;
}

int Person::getAge(void) {
    return age;
}

void Person::setSurname(string surname) {
    this->surname = surname;
}

void Person::setEmail(string email) {
    this->email = email;
}

void Person::setAge(int age) {
    this->age = age;
}

void Person::setName(string name) {
    this->name = name;
}

istream& operator>>(istream& str,Person& obj) {
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

ostream& operator<<(ostream& str,Person& obj) {
    str << "Name: " << obj.name << endl;
    str << "Surname: " << obj.surname << endl;
    str << "Age: " << obj.age << endl;
    str << "Email: " << obj.email << endl;
    return str;
}
