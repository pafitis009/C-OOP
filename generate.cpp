/// TO RANDOMLY GENERATE INPUT
/// 1 school has a schoolyard, a building with 3 floors, 1 staircase, and each floor has 1 corridor and 6 classrooms

#include <iostream>
#include <fstream>
#include <time.h>
#define STUDENTS 5
#define FLOORS 3
#define CLASSES 6

using namespace std;

string names[20] = {"Marios", "Constantinos", "Giorgos" ,"Sofronis" ,"Angelos" ,"Sokratis","Maria","Eleni","Georgia","Persifoni","Nefeli","Louiza","Petros","Nikolas","Nikoletta","Marietta","Andreas","Andrea","Savvas","Stephany"}; //Random names to sample from

int main(){
    ofstream fout("in.txt");
    srand(time(NULL));
    for(int flr=1; flr<=FLOORS; flr++)
        for(int classs=1; classs <= CLASSES; classs++){
            for(int student=0; student<STUDENTS; student++)
                fout << "S " <<  names[rand()%20] << " " << flr << " " << classs << '\n';
            fout << "T " << names[rand()%20] << " " << flr  << " " << classs << '\n';
        }

    return 0;
}