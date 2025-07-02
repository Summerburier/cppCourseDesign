#include"menu.h" 
#include<windows.h>  
using namespace std;



int main() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci = {1,0};
    SetConsoleCursorInfo(h, &ci);
    SetConsoleScreenBufferSize(h, {100, 300}); // 设置缓冲区大小
    Sleep(1000);

    menu();
    cout<<"输入任意键结束程序..."<<endl;
    getchar();
    return 0;
}