#include "select.h"
using namespace std;

void show(const std::string* quiz, int num, int line) {
    for (int i = 0; i < num; i++) {
        cout << (i == line ? " > " : "    ") << quiz[i] << endl;
    }
}

int selectquiz(const std::string& s, int num, const std::string* quiz,const string& userName="") {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);
    // 动态扩展缓冲区高度，确保菜单区有空间
    SHORT menu_start = csbi.dwCursorPosition.Y; // 确保菜单区有足够空间
    SetConsoleCursorPosition(h, {0, menu_start});
   
    

    // 菜单区输出和清理
    int i = 0;
    while (1) {
        SetConsoleCursorPosition(h, {0, menu_start});
        for (int k = 0; k < num + 3; k++) {
            cout << string(100, ' ') << endl;
        }
        SetConsoleCursorPosition(h, {0, menu_start});
        cout <<" ? " << s << " (Use arrow keys)" << endl;
        show(quiz, num, i);

        int key = _getch();
        if (key == 224) {
            key = _getch();
            if (key == 72) {
                i = (i - 1 + num) % num;
            } else if (key == 80) {
                i = (i + 1) % num;
            }
        } else if (key == 13) {
            break;
        } else if (key == 27) {
            break;
        }
    }
    SetConsoleCursorPosition(h, {0, menu_start});
    for (int k = 0; k < num + 3; k++) {
        cout << string(100, ' ') << endl;
    }
    // 关键：将光标移到菜单区下方第一行
    SetConsoleCursorPosition(h, {0, menu_start});
    cout <<" ? " << s << " ";
    cppOut(quiz[i], outputType::message, userName);
    return i;
}


