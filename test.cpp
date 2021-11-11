#include <iostream>
#include "CParser.h"
using namespace std;
#include <cstring>

int test1(){
    char test1[256] = "test1.txt";
    CParser t1(test1);
    char answer[256] = "00 888";
    char value[256];
    char name[256] = "bbb";
    t1.GetMeaningForName(name, value);

    if(strcmp(value, answer)==0){
        cout << "test1 passed" << endl;
        return 0;
	}
	else {
        cout << "test1 not passed" << endl;
        return 1;
	}

}

int test2(){
    char test2[256] = "test2.txt";
    CParser t2(test2);
    char answer1[256]= "io";
    char answer2[256] = "hk";
    char value1[256];
    char value2[256];
    char name1[256] = "ccc";
    char name2[256] = "ddd";
    t2.GetMeaningForName(name1, value1);
    t2.GetMeaningForName(name2, value2);

    if(strcmp(value1, answer1)==0 && strcmp(value2, answer2)==0){
        cout << "test1 passed" << endl;
        return 0;
	}
	else {
        cout << "test1 not passed" << endl;
        return 1;
	}

}

int main_test(){
    if(test1() + test2() == 0){
        return 0;
    }
    else return 1;
}
