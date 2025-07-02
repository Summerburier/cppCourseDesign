#include "students.h"
#include <stdexcept>

// 分数范围检查
static void checkScore(int score, const std::string& subject) {
    if (score < 0 || score > 100) {
        throw std::invalid_argument(subject + " 分数必须在0~100之间");
    }
}

// 构造函数实现
student::student(std::string name, std::string regNum, std::string major, bool isFreshman,
                 int Politics, int Math, int ForignLanguage, int MajorSubject)
    : name(name), regristrationNumber(regNum), major(major), isFreshman(isFreshman)
{
    checkScore(Politics, "政治");
    checkScore(Math, "数学");
    checkScore(ForignLanguage, "外语");
    checkScore(MajorSubject, "专业课");
    this->Politics = Politics;
    this->Math = Math;
    this->ForignLanguage = ForignLanguage;
    this->MajorSubject = MajorSubject;
     calculateAllScore();
    this->AllScore = Politics + Math + ForignLanguage + MajorSubject;
}

std::string student::getName() const {
    return name;
}
std::string student::getRegristrationNumber() const {
    return regristrationNumber;
}
std::string student::getMajor() const {
    return major;
}
bool student::getIsFreshman() const {
    return isFreshman;
}
int student::getPolitics() const {
    return Politics;
}
int student::getMath() const {
    return Math;
}
int student::getForignLanguage() const {
    return ForignLanguage;
}
int student::getMajorSubject() const {
    return MajorSubject;
}
int student::getAllScore() const {
    return AllScore;
}
void student::setName(const std::string& newName) {
    name = newName;
}
void student::setRegristrationNumber(const std::string& newRegristrationNumber) {
    regristrationNumber = newRegristrationNumber;
}
void student::setMajor(const std::string& newMajor) {
    major = newMajor;
}
void student::setIsFreshman(bool newIsFreshman) {
    isFreshman = newIsFreshman;
}
void student::setPolitics(int newPolitics) {
    checkScore(newPolitics, "政治");
    Politics = newPolitics;
}
void student::setMath(int newMath) {
    checkScore(newMath, "数学");
    Math = newMath;
}
void student::setForignLanguage(int newForignLanguage) {
    checkScore(newForignLanguage, "外语");
    ForignLanguage = newForignLanguage;
}
void student::setMajorSubject(int newMajorSubject) {
    checkScore(newMajorSubject, "专业课");
    MajorSubject = newMajorSubject;
}
void student::setAllScore(int newAllScore) {
    if (newAllScore < 0 || newAllScore > 400) {
        throw std::invalid_argument("总分必须在0~400之间");
    }
    AllScore = newAllScore;
}