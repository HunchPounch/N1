#include <iostream>
#include "CParser.h"
using namespace std;
#include "test.h"

void ClearNameAndValue(char (&name)[256], char (&value)[256]){
    for(int i=0; i<255; i++){
        name[i] = '\0';
    }
    for(int i=0; i<255; i++){
        value[i] = '\0';
    }
}

void Merge(CParser &Head, char file_name[256]){
    CParser NewFile(file_name);
    Head.MergeParserLists(NewFile);
}


int main()
{
    if(main_test() == 1){
        cout << "tests not passed" << endl << endl;
        return 1;
    }

    char file_name[256] = "";
    char name[256]= "";
    char value[256]= "";
    int mode = -1;
    cout << endl << "Please enter the name of the config-file" << endl;
    cin >> file_name;
    CParser Head(file_name);

    while(1){
        cout << endl << "Select next number:" << endl;
        cout << "1 -- Get value by name in the current file" << endl;
        cout << "2 -- Load another file and merge it with the current one to parse a common file" << endl;
        cout << "3 --- exit" << endl << endl;
        cin >> mode;

        if(mode == 1){
           ClearNameAndValue(name, value);
           cout << "Enter name" << endl;
           cin >> name;
           if(Head.GetMeaningForName(name, value)!=0){
              cout <<"The value of "<< name<<" is: " << value <<endl << endl;
           }
        }

        if(mode == 2){
            cout << "Please enter the name of the config-file" << endl;
            ClearNameAndValue(file_name, value);
            cin >> file_name;
            Merge(Head,file_name);
            cout << "Now you can parse the merged file" << endl << endl;

        }

        if(mode == 3){
            break;
        }

        if(mode != 1 && mode != 2 && mode != 3){
            cout << "incorrect input" << endl;
            break;
        }
    }

    return 0;
}
