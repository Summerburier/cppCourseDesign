#include "cppOut.h"
#include "list.h"

using namespace std;


void timeOut() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct timeb tb;
    ftime(&tb);
    struct tm tm_info;
    localtime_s(&tm_info, &tb.time);
    
    // 格式化日期时间部分
    char date_time[20];
    strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", &tm_info);
    
    // 组合完整时间字符串
    std::ostringstream oss;
    oss << date_time << "." << std::setfill('0') << std::setw(3) << tb.millitm;
    
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << oss.str();
    SetConsoleTextAttribute(hConsole, 15);
}
void typeOut(outputType type) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.width(8);
    cout.setf(ios::left); // 设置左对齐
    switch (type) {
        case outputType::info:
            SetConsoleTextAttribute(hConsole, 15); // 白色
            cout<<"INFO";
            break;
        case outputType::error:
            SetConsoleTextAttribute(hConsole, 12); // 红色
            cout<<"ERROR";
            break;
        case outputType::warning:
            SetConsoleTextAttribute(hConsole, 14); // 黄色
            cout<<"WARNING";
            break;
        case outputType::success:
            SetConsoleTextAttribute(hConsole, 10); // 绿色
            cout<<"SUCCESS";
            break;
        

    }
    SetConsoleTextAttribute(hConsole, 15);
}

void userOut(string userName) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3); // 青色
    cout << userName;
    SetConsoleTextAttribute(hConsole, 15); // 重置颜色
    cout<<" | ";
}

void infoOut(string info, outputType type){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(type){
        case outputType::success:
        SetConsoleTextAttribute(hConsole, 10);
        cout<<info<<newline;
        break;
        case outputType::error:
        SetConsoleTextAttribute(hConsole, 12);
        cout<<info<<newline;
        break;
        case outputType::warning:
        SetConsoleTextAttribute(hConsole, 14);
        cout<<info<<newline;
        break;
        default:
        SetConsoleTextAttribute(hConsole, 15);
        cout<<info<<newline;
        break;
        case outputType::message:
        SetConsoleTextAttribute(hConsole, 6);
        cout<<info<<newline;
        break;
        case outputType::hidden:
        SetConsoleTextAttribute(hConsole, 8);
        cout<<info<<newline;
        break;
    }
     SetConsoleTextAttribute(hConsole, 15);
}
void cppOut(std::string info,outputType type,std::string userName){
    if(type==outputType::message||type==outputType::hidden){
        infoOut(info, type);
        return;
    }
    timeOut();
    cout<<" | ";
    if(userName!=""){
        userOut(userName);}
    typeOut(type);
    cout<<" | ";
    infoOut(info, type);
    
}
int getDisplayWidth(const std::string& str) {
    int width = 0;
    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if (c < 128) {
            width += 1; // ASCII字符
            i += 1;
        } 
        // 处理UTF-8多字节字符（中文等）
        else if ((c & 0xE0) == 0xC0) { // 2字节字符
            width += 1; // 通常不是中文，宽度为1
            i += 2;
        } 
        else if ((c & 0xF0) == 0xE0) { // 3字节字符（中文字符）
            width += 2;
            i += 3;
        } 
        else if ((c & 0xF8) == 0xF0) { // 4字节字符
            width += 2; // 通常按2宽度处理
            i += 4;
        } 
        else {
            width += 1; // 无效UTF-8，按1宽度处理
            i += 1;
        }
    }
    return width;
}

// 右侧填充空格使字符串达到指定显示宽度
std::string padRight(const std::string& str, int totalWidth) {
    int currentWidth = getDisplayWidth(str);
    if (currentWidth >= totalWidth) {
        return str;
    }
    return str + std::string(totalWidth - currentWidth, ' ');
}

// 计算字符串在控制台的显示宽度（中文=2，英文=1）

void formOut(const list& studentList) {
    if (studentList.head == NULL) {
        cppOut("学生列表为空", outputType::error);
        cppOut("请先添加学生信息", outputType::info);
        return;
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // 列宽设置（按显示宽度）
    const int nameWidth = 15;     // 姓名列显示宽度
    const int idWidth = 20;       // 准考证号列显示宽度
    const int majorWidth = 22;    // 专业列显示宽度
    const int freshmanWidth = 13; // 是否应届生列显示宽度
    const int scoreWidth = 8;     // 成绩列显示宽度
    
    // 表头输出
    SetConsoleTextAttribute(hConsole, 3);
    cout << padRight("姓名", nameWidth)
         << padRight("准考证号", idWidth)
         << padRight("专业", majorWidth)
         << padRight("是否应届生", freshmanWidth)
         << padRight("政治", scoreWidth)
         << padRight("数学", scoreWidth)
         << padRight("外语", scoreWidth)
         << padRight("主修", scoreWidth)
         << padRight("总分", scoreWidth)
         << newline;
    
    SetConsoleTextAttribute(hConsole, 15);
    node* current = studentList.head;
    while (current != NULL) {
        // 获取学生数据
        string name = current->data.getName();
        string regNumber = current->data.getRegristrationNumber();
        string major = current->data.getMajor();
        bool isFreshman = current->data.getIsFreshman();
        int politics = current->data.getPolitics();
        int math = current->data.getMath();
        int foreignLang = current->data.getForignLanguage();
        int majorSubject = current->data.getMajorSubject();
        int allScore = current->data.getAllScore();
        
        // 输出格式化行
        cout << padRight(name, nameWidth)
             << padRight(regNumber, idWidth)
             << padRight(major, majorWidth)
             << padRight(isFreshman ? "是" : "否", freshmanWidth)
             << padRight(to_string(politics), scoreWidth)
             << padRight(to_string(math), scoreWidth)
             << padRight(to_string(foreignLang), scoreWidth)
             << padRight(to_string(majorSubject), scoreWidth)
             << padRight(to_string(allScore), scoreWidth)
             << newline;

        current = current->next;
    }
}
