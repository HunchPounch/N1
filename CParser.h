#pragma once


class CListParseNode{

public:
    char name[256];
    char nothing;
    char meaning[256];

    CListParseNode *prev;
    CListParseNode *next;
    CListParseNode(){prev = next = NULL;}
};

class CListParse{

private:
    CListParseNode *cur;
    CListParseNode *Begin;
    CListParseNode *End;

public:
    CListParse();
    ~CListParse();
    CListParse(CListParse &b);

    void SetZero();
    void Clean();
    void CopyOnly(CListParse &b);
    void GoToBegin();
    void GoToEnd();
    int GetCur(char (&name)[256], char (&meaning)[256]);
    int GoToNext();
    int GoToPrev();
    int IsEmpty();
    void AddAfter(const char (&name)[256],const char (&meaning)[256]);
    int DelCur();
    int PlusMeaningWithSpace(const char name[256], const char meaning[256]);
    void PlusMeaningWithoutSpace(const char name[256], const char meaning[256]);
    int SearchName(const char name[256]);
    void Merge(char file_name[256]);

};


class CParser{

private:

    CListParse FileInClass;

public:

    CParser(const char file_name[256]);

    int GetMeaningForName(char (&name)[256], char (&meaning)[256]);

    void MergeParserLists(CParser &b);

};









