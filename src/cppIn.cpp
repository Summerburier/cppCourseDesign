#include "cppIn.h"
#include <windows.h>
#include <iostream>

using namespace std;

std::string cppIn(const std::string& prompt,const std::string& userName)  {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    SHORT input_start = csbi.dwCursorPosition.Y;
    std::string input;
    
    // 初始提示
    SetConsoleTextAttribute(hConsole, 15);
    cout << " ? " << prompt << ": " << flush;

    // 获取输入
    getline(cin, input);

    // 清除整个行（包括提示符）
    COORD cleanPos = {0, input_start};
    DWORD written;
    FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, cleanPos, &written);
    
    // 重置光标并输出最终结果（单次操作）
    SetConsoleCursorPosition(hConsole, cleanPos);
    cout << " ? " << prompt << ": " << flush;


    // 如果需要调用cppOut，使用以下方式：

    // SetConsoleCursorPosition(hConsole, cleanPos);
    // cout << "❔ " << prompt << ": ";
    // COORD outputPos = {static_cast<SHORT>(prompt.length()-1), input_start};
    // SetConsoleCursorPosition(hConsole, outputPos);
    cppOut(input, outputType::message, userName);
    

    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    SetConsoleTextAttribute(hConsole, 15);

    return input;
}