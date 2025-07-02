#pragma once
#include <string>
#include <iostream>
#include <iomanip>



class student{
    private:
    std::string name;
    std::string regristrationNumber;
    std::string major;
    bool isFreshman;
    int Politics;
    int Math;
    int ForignLanguage;
    int MajorSubject;
    int AllScore;
    public:
    student() : 
        name(""), regristrationNumber(""), major(""), 
        isFreshman(false), Politics(0), Math(0), 
        ForignLanguage(0), MajorSubject(0), AllScore(0) {};
    student(std::string name, std::string regristrationNumber, std::string major, bool isFreshman, int Politics, int Math, int ForignLanguage, int MajorSubject);
    student(std::string name, std::string regristrationNumber, std::string major, bool isFreshman, int Politics, int Math, int ForignLanguage, int MajorSubject, int AllScore) :
        name(name), regristrationNumber(regristrationNumber), major(major), 
        isFreshman(isFreshman), Politics(Politics), Math(Math), 
        ForignLanguage(ForignLanguage), MajorSubject(MajorSubject), AllScore(AllScore) {};
    std::string getName() const ;
    std::string getRegristrationNumber() const;
    std::string getMajor() const ;
    bool getIsFreshman() const;
    int getPolitics() const ;
    int getMath() const ;
    int getForignLanguage() const ;
    int getMajorSubject() const ;
    int getAllScore() const;
    void setName(const std::string& newName) ;
    void setRegristrationNumber(const std::string& newRegristrationNumber) ;
    void setMajor(const std::string& newMajor) ;
    void setIsFreshman(bool newIsFreshman) ;
    void setPolitics(int newPolitics) ;
    void setMath(int newMath) ;
    void setForignLanguage(int newForignLanguage) ;
    void setMajorSubject(int newMajorSubject) ;
    void setAllScore(int newAllScore);
    void calculateAllScore() {
        AllScore = Politics + Math + ForignLanguage + MajorSubject;
    }
};


