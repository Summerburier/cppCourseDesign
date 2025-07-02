#pragma once
#include "cppOut.h"  // 添加cppOut.h头文件
#include <conio.h>   // 添加_getch()支持
#include <string>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>
#include <string>

std::string cppIn(const std::string& prompt,const std::string& userName="");