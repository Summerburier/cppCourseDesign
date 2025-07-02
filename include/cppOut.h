#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <sys/timeb.h>
#include <time.h>
#include <windows.h>
#include <ctime>
#include <sstream>

class list;

enum class outputType {
    info,
    error,
    warning,
    success,
    message,
    hidden
};
const std::string newline = "\n\r"; 
void cppOut(std::string info,outputType type,std::string userName="");
void formOut(const list& studentList);




