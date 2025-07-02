#pragma once
#include <string>
#include "cppOut.h"
#include <conio.h>
#include <windows.h>

// 正确的声明：参数类型为指针
int selectquiz(const std::string& s, int num, const std::string* quiz,const std::string& userName);