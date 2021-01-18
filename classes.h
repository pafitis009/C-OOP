#include <iostream>
#define NUM_OF_CLASSES 6
#define MAX_STUDENTS 25
#define NUM_OF_FLOORS 3

using namespace std;


class Person{
    int kourasi, L; //koiurasi-> sunoliki kourasi, L -> poso kourazete 1 ora
    string name, type;
    int f_num, c_num;
    bool inClass;

    public:
        string get_name(){return name;}
        int get_floor(){return f_num;}
        int get_class(){return c_num;}
        void toggle(){inClass = !inClass;};
        void increase_tired(int hours){kourasi += (L*hours);};
        void print(){cout << name << " " << kourasi << '\n';};

        Person(string nme, int f, int c, int l, string t): name(nme), f_num(f), c_num(c), inClass(0), kourasi(0), L(l), type(t){
            cout << "A new " << type << " has been created!" << '\n';
        };
        ~Person(){
            cout << "A " << type << " to be destroyed" << '\n';
        };
};


class Teacher:public Person{
    public:
        Teacher(string nme, int f_num, int c_num, int l): Person(nme, f_num, c_num, l, "Teacher"){};
};

class Student:public Person{
    bool isJunior; //1 if is Junior, 0 if is Senior
    public:
        Student(string nme, int f_num, int c_num, int l): Person(nme, f_num, c_num, l, "Student"){
            if(c_num < 4)
                isJunior = 1;
            else
                isJunior = 0;
        };
};  

class Area{
    Student* cur_stud;


    public:
        void enter(string person_name);
        void exit(string person_name);
        string place_name;
        
        Area(string str){
            place_name = str;
            cout << "A new " << place_name << " has been created" << '\n';
        }

        ~Area(){
            cout << "A " << place_name << " to be destroyed" << '\n';
        }
};



class Class: public Area{
    Student* students[MAX_STUDENTS];
    Teacher* teacher;
    int C_class, class_num, floor_num, cur_students;

    public:
        // void enter(string person_name){Area::enter(person_name);};
        int get_cur_students(){return cur_students;};
        int get_class_num(){return class_num;};
        void increase_students_counter(){cur_students++;};

        void enter_class(Student* st);
        void place(Teacher* tc);
        void operate(int hours);
        void print();


        Class(int C, int c_num, int f_num):C_class(C), class_num(c_num), floor_num(f_num), cur_students(0), Area("Class"){};

        ~Class(){
            delete teacher;
            teacher -> print();
            for(int i=0; i<this->get_cur_students(); i++){
                delete students[i]; 
                students[i] -> print();
            }
        }
};

class Corridor:public Area{
    public:
        Corridor() : Area("Corridor"){};
};



class Stairs:public Area{
    public:
        Stairs() : Area("Stairs"){};
};

class Yard:public Area{
    public:
        Yard() : Area("Schoolyard"){};
};


class Floor: Area{
    int f_num;
    Corridor* corridor;
    Class* classes[NUM_OF_CLASSES];
    public:
        int get_floor_num(){return f_num;};
        void enter_floor(Student* st);
        void place(Teacher* st);
        void operate(int hours);
        void print();


        Floor(int id, int C_class): Area("Floor"), f_num(id){
            corridor = new Corridor();
            for(int i=0; i<NUM_OF_CLASSES; i++)
                classes[i] = new Class(C_class, i+1, f_num);
        }

        ~Floor(){
            for(int i=0; i<NUM_OF_CLASSES; i++)
                delete classes[i];
        }
};



class School{
    Yard* yard;
    Stairs* stairs;
    Floor* floors[NUM_OF_FLOORS];


    public:
        void EnterSchool(Student* st);
        void EnterSchool(Teacher* tc);
        void operate(int N);
        void print();

        School(int C_class){
            cout << "A new school has been created!" << '\n';
            yard = new Yard();
            stairs = new Stairs();
            for(int i=0; i<NUM_OF_FLOORS; i++)
                floors[i] = new Floor(i+1, C_class);
        }

        ~School(){
            cout << "A School to be destroyed" << '\n';
            delete yard;
            delete stairs;
            for(int i=0; i<NUM_OF_FLOORS; i++)
                delete floors[i];
        }
};


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