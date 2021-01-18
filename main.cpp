#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <algorithm>
#include "classes.h"

#define NUM_OF_PEOPLE 108
#define STUDENTS 90
#define TEACHERS 18
#define BIG_MOD 10001000

using namespace std;


Student* students[STUDENTS];
Teacher* teachers[TEACHERS];
int seeds[NUM_OF_PEOPLE];

void create_random_seedings(){
    //THIS FUNCTION CREATES A PERMUTATION OF {1,2, ... , N} TO RANDOMLY SEND STUDENTS/TEACHERS INSIDE THE SCHOOL.
    vector < pair<int,int> > order;
    for(int i=0; i<NUM_OF_PEOPLE; i++)
        order.push_back(make_pair((rand()%BIG_MOD), i));

    sort(order.begin(), order.end());

    for(int i=0; i<NUM_OF_PEOPLE; i++)
        seeds[i] = order[i].second;
}

int main(){
    ifstream fin("in.txt");
    
    int C_class, L_j=1, L_s=2, L_t=3, N = 5;
    
    // C_class = atoi(argv[0]);
    // L_j = atoi(argv[1]);
    // L_s = atoi(argv[2]);
    // L_t = atoi(argv[3]);
    // N = atoi(argv[4]);


    School* school = new School(C_class); // CREATE A NEW SCHOOL


    int student_cnt = 0, teacher_cnt = 0;
    for(int i=0; i<NUM_OF_PEOPLE; i++){
        string n;
        char t;
        int f,c;

        fin >> t >> n >> f >> c;

        if(t == 'S'){
            if(c < 4)
                students[student_cnt] = new Student(n, f, c, L_j);
            else
                students[student_cnt] = new Student(n, f, c, L_s);
            
            student_cnt++;
        }
        else
            teachers[teacher_cnt] = new Teacher(n, f, c, L_t), teacher_cnt ++;
    }

    srand(time(NULL));
    create_random_seedings();
    
    for(int i=0; i<NUM_OF_PEOPLE; i++){
        if(seeds[i] < STUDENTS) // We are processing a student
            school -> EnterSchool(students[seeds[i]]);
        else //We are processing a teacher
            school -> EnterSchool(teachers[seeds[i] - STUDENTS]);
    }


    school -> operate(N); //OPERATE SCHOOL FOR N HOURS

    school -> print(); // PRINT SCHOOL LIFE

    school -> ~School(); //DESTROY SCHOOL LIFE

    return 0;
}