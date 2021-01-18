#include <iostream>
#include "classes.h"

using namespace std;

//PEOPLE ENTERING SCHOOL


void Area::enter(string person_name){
    cout << person_name << " enters " << place_name << '\n';
}

void Area::exit(string person_name){
    cout << person_name << " exits " << place_name << '\n';
}


//STUDENT ENTERING SCHOOL

void Class::enter_class(Student* st){
    Area::enter(st -> get_name());
    st -> toggle();

    students[this -> get_cur_students()] = st;
    this -> increase_students_counter();
}

void Floor::enter_floor(Student* st){
    Area::enter(st -> get_name());
    Area::exit(st -> get_name());
    
    corridor -> enter(st -> get_name());
    corridor -> exit(st -> get_name());
    
    classes[(st -> get_class()) - 1] -> enter_class(st);
}

void School::EnterSchool(Student* st){
    cout << st -> get_name() << " enters school" << '\n';
        
    yard -> enter(st -> get_name());
    yard -> exit(st -> get_name());

    stairs -> enter(st -> get_name());
    stairs -> exit(st -> get_name());

    floors[(st -> get_floor())-1] -> enter_floor(st);
}


//  PLACING TEACHER IN CLASS


void Class::place(Teacher* tc){
    tc -> toggle();
    teacher = tc;
}

void Floor::place(Teacher* tc){
    classes[(tc -> get_class())-1] -> place(tc);
}

void School::EnterSchool(Teacher* tc){
    floors[(tc -> get_floor())-1] -> place(tc);
}

//OPERATING SCHOOL

void Class::operate(int hours){
    teacher -> increase_tired(hours);
    for(int i=0; i<this-> get_cur_students(); i++)
        students[i] -> increase_tired(hours);
}

void Floor::operate(int hours){
    for(int i=0; i<NUM_OF_CLASSES; i++)
        classes[i] -> operate(hours);
}


void School::operate(int hours){
    for(int i=0; i<NUM_OF_FLOORS; i++)
        floors[i] -> operate(hours);
}

//PRINT SCHOOL

void Class::print(){
    cout << "People in class " << this -> get_class_num() << " are: " << '\n';
    cout << "The Teacher is: " << '\n';
    teacher -> print();
    cout << "The " << this -> get_cur_students() << " students are: " << '\n';
    for(int i=0; i<this -> get_cur_students(); i++)
        students[i] -> print();
    
}

void Floor::print(){
    cout << "Floor " << this -> get_floor_num() << " contains: " << '\n';
    for(int i=0; i<NUM_OF_CLASSES; i++)
        classes[i] -> print();
}

void School::print(){
    cout << "School life consists of: " << '\n';
    for(int i=0; i<NUM_OF_FLOORS; i++)
        floors[i] -> print();
}