#pragma once
#include <string>
#include <iostream>
#include "students.h"
#include "cppOut.h"
#include "cppIn.h"

// 修改 list.h 中的 node 结构体
struct node {
    student data;
    node* next;
    
    // 添加构造函数解决编译错误
    node(const student& s) : data(s), next(nullptr) {}
};

enum class searchType {
    name,
    regristrationNumber,
    major,
    isFreshman,
    Politics,
    Math,
    ForignLanguage,
    MajorSubject
 };
enum class level{
    accurate,
    fuzzy
};

class list { 
     friend void formOut(const list& studentList); // 添加友元声明
    private:
    node* head;
    node* standard;
    int size;
    public:
    list(int size=0) : size(size) {
        head = NULL;
        standard = new node(student());
    }
    void insert(const student& s);
    list Search(searchType type, const std::string& value,level le, const std::string& userName) const ;
    void setStandard(const std::string& userName) ;
    void changeInfo(const std::string& regristrationNumber, searchType type, const std::string& value, const std::string& userName) ;
    void displayAll(const std::string& userName) const ;
    void deleteInfo(const std::string& regristrationNumber, const std::string& userName) ;
    void loadFromFile();
    void saveToFile(const std::string& userName) const;
    node* getHead() const { return head; }
    list filterPassed() const;
    static list sortByTotalScore(const list& src);
    void Fout(const std::string& fileName, const std::string& userName) const;
};

