#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "CParser.h"
#include <iostream>
#include <fstream>
using namespace std;

CListParse::CListParse(){
    this->SetZero();
}

void CListParse::SetZero(){
    this->cur = NULL;
    this->Begin = NULL;
    this->End = NULL;
}

CListParse::~CListParse(){
    this->Clean();
}

void CListParse::Clean(){
    this->GoToBegin();
    while(this->DelCur()==0);
    this->SetZero();
}

CListParse::CListParse(CListParse &b){
    this->CopyOnly(b);
}

void CListParse::GoToBegin(){
    this->cur = this->Begin;

}

void CListParse::GoToEnd(){
    this->cur = this->End;
}
/////////////////////////////////////
/////////////////////////////////////////////////
////////////////////////////////////////////////////
///
//
 //   /    /         /  ////////////
void CListParse::CopyOnly(CListParse &b){
    char name[256];
    char meaning[256];
    if(b.IsEmpty()==0){
        b.GoToBegin();
        do{
            b.GetCur(name, meaning);
            if(this->SearchName(name)==0){
                this->GoToEnd();
                this->AddAfter(name, meaning);
            }
            if(this->SearchName(name)!=0 && strcmp(this->cur->meaning, meaning)==0){
                ////
            }

        }
        while(b.GoToNext()==0);
    }
}

int CListParse::GetCur(char (&name)[256], char (&meaning)[256]){
    if(this->IsEmpty())return -1;
    strcpy(name, this->cur->name);
    strcpy(meaning, this->cur->meaning);

    return 0;
}

int CListParse::GoToNext(){

    if(this->IsEmpty())return -1;
    if(this->cur->next==NULL)return -2;
    this->cur= this->cur->next;
    return 0;
}

int CListParse::GoToPrev(){
    if(this->IsEmpty())return -1;
    if(this->cur->prev==NULL)return -2;
    this->cur= this->cur->prev;
    return 0;
}

int CListParse::IsEmpty() {
    return this->cur==NULL;
}

void CListParse::AddAfter(const char (&name)[256],const char (&meaning)[256]){
    CListParseNode *n = new CListParseNode();
    strcpy(n->name, name);
    strcpy(n->meaning, meaning);


    if(this->IsEmpty()){
        this->cur=n;
        this->Begin=n;
        this->End=n;

    }
    else{

        n->next=this->cur->next;
        n->prev=this->cur;
        this->cur->next=n;
        if(n->next){
            n->next->prev=n;
        }
        else{
            this->End=n;
        }

    }

}

int CListParse::DelCur(){
    if(this->IsEmpty())return -1;

    if(this->cur->prev){
        this->cur->prev->next=this->cur->next;
    }
    else{
        this->Begin = this->cur->next;
    }

    if(this->cur->next){
        this->cur->next->prev=this->cur->prev;
    }
    else{
        this->End = this->cur->prev;
    }

    if(this->cur->prev){
        this->cur=this->cur->prev;
    }
    else{
        this->cur=this->cur->next;
    }
    return 0;

}

int CListParse::PlusMeaningWithSpace(const char name[256], const char meaning[256]){
    int stop = 0;
    this->GoToBegin();
    if(this->IsEmpty())return -1;
    do{
        if(strcmp(this->cur->name, name)==0){
            strcat(this->cur->meaning, " ");
            strcat(this->cur->meaning, meaning);
            stop = 1;
            break;
        }
    }
    while(this->GoToNext()==0);
    if(stop==0){
       // cout << "There is no such name" << endl;
    }
    return stop;
}

void CListParse::PlusMeaningWithoutSpace(const char name[256], const char meaning[256]){
    int stop = 0;
    this->GoToBegin();
    if(this->IsEmpty())return;
    do{
        if(strcmp(this->cur->name, name)==0){
            strcat(this->cur->meaning, meaning);
            stop = 1;
            break;
        }
    }
    while(this->GoToNext()==0);
    if(stop==0){
        cout << "There is no such name " << endl;
    }

}

int CListParse::SearchName(const char name[256]){
    int stop = 0;
    this->GoToBegin();
    if(this->IsEmpty())return 0;
    do{
        if(strcmp(this->cur->name, name)==0){
            stop = 1;
            break;
        }
    }
    while(this->GoToNext()==0);
    if(stop==0){
        cout << "There is no such name" << endl<< endl;
    }
    return stop;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CParser::CParser(const char file_name[256]){

    ifstream fin(file_name);
    if(!(fin.is_open())){
        cout << "File not find\n";
        exit(-1);
    }
    int NumOfString = 1;
    int check =-1;
    int CHECK = -1;
    char buffer[256] = "&";
    char FirstTemplate[256] = "";
    char SecondTemplate[256] = "";
    while(!fin.eof()){

    for(int i=0; i<255; i++){
        buffer[i] = '\0';
    }
    for(int i=0; i<255; i++){
        FirstTemplate[i] = '\0';
    }
    for(int i=0; i<255; i++){
        SecondTemplate[i] = '\0';
    }

    fin.getline(buffer,256);
    int i =0;
    while(buffer[i] == ' '){
        i++;
    }
    for(int k=0; buffer[i] != ' '; i++, k++){
        if(buffer[i]== '#' || buffer[i] == '\0'){
            cout << "incorrect input in " << NumOfString <<"st line" << endl;
            NumOfString++;
            CHECK = 1;
            break;
        }
        FirstTemplate[k]=buffer[i];

    }

    if(CHECK == 1){
        CHECK = -1;
        continue;
    }

    if(buffer[0] == '&'){
        cout << "The "<< NumOfString <<"st line in file is empty" << endl;
        NumOfString++;
        continue;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    check = i + 1;
    i = i + 3;

    if(buffer[i-1] == '\0' || buffer[i] == '\0' || buffer[i-2] == '\0'){
        cout << "incorrect input in " << NumOfString <<"st line" << endl;
        NumOfString++;
        continue;
    }
    if(buffer[i-1] != ' '){
        cout << "incorrect input in " << NumOfString <<"st line" << endl;
        NumOfString++;
        continue;
    }
    if(buffer[i] == '#'){
        cout << "incorrect input in " << NumOfString <<"st line" << endl;
        NumOfString++;
        continue;
    }
    if(buffer[i] == ' '){
        cout << "incorrect input in " << NumOfString <<"st line" << endl;
        NumOfString++;
        continue;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    for(int j=0; buffer[i]!= '#' && buffer[i] != '\0'; i++, j++){

        SecondTemplate[j] = buffer[i];
    }

    if(buffer[check] != '='){
        if(buffer[check] == '+'){
            if(FileInClass.PlusMeaningWithSpace(FirstTemplate, SecondTemplate)==0){
                check = 1;

            }
            else{
                check = -1;
                continue;
            }
        }
        else{
            cout << "incorrect input in " << NumOfString <<"st line" << endl;
            NumOfString++;
            continue;
        }

    }
    FileInClass.AddAfter(FirstTemplate, SecondTemplate);

    NumOfString++;
    }

    fin.close();
}

int CParser::GetMeaningForName(char (&name)[256], char (&meaning)[256]){
    int stop = 0;
    char fake[256];
    if(FileInClass.SearchName(name)!=0){
        FileInClass.GetCur(fake, meaning);
        stop = 1;
    }
    if(FileInClass.IsEmpty()){
        cout <<"No meaningful lines in the file or the file is empty" << endl;
    }
    return stop;
}

void CParser::MergeParserLists(CParser &b){
    this->FileInClass.CopyOnly(b.FileInClass);
}
