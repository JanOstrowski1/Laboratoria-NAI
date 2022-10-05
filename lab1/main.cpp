#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#define PI 3.14159265
int main(int argc, char **argv) {
    using namespace std;
    vector<string> argumenty(argv, argv + argc);

    string func_name= argumenty.at(2);

    if(func_name=="sin"){
        float first_arg= stof(argumenty.at(3));
        cout<< sin (first_arg*PI/180);
    }else if(func_name=="add"){
        float first_arg= stof(argumenty.at(3));
        float second_arg= stof(argumenty.at(4));
        cout<< (first_arg+ second_arg);
    }else if(func_name=="mod"){
        int first_arg= stoi(argumenty.at(3));
        int second_arg= stoi(argumenty.at(4));
        cout<< (first_arg % second_arg);
    }else{
        return 1;
    }

    return 0;
}
