#include "menu.h"
#include "select.h"
#include "cppIn.h"
#include "cppOut.h"
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// 定义用户结构体
struct User {
    string username;
    string password;
};

vector<User> users; // 存储用户数据的全局变量

// 读取用户数据到vector
bool loadUsers() {
    cppOut("正在加载用户数据...", outputType::info);
    users.clear(); // 清空现有数据
    ifstream file("user.txt");
    if (!file) {
        cppOut("用户文件不存在，将创建新文件", outputType::info);
        ofstream newFile("user.txt"); // 创建新文件
        cppOut("用户文件已创建", outputType::success);
        return false;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find(' ');
        if (pos != string::npos) {
            User user;
            user.username = line.substr(0, pos);
            user.password = line.substr(pos + 1);
            users.push_back(user);
        }
    }
    file.close();
    return !users.empty();
}
bool deleteUser(const string& username) {
    // 重新加载用户数据确保最新
    loadUsers();
    
    // 查找用户是否存在
    auto it = find_if(users.begin(), users.end(), 
        [&](const User& u) { return u.username == username; });
    
    if (it == users.end()) {
        cppOut("用户不存在", outputType::error);
        return false;
    }

    // 第一次密码确认
    string password1 = cppIn("请输入密码");
    if (password1 != it->password) {
        cppOut("密码错误", outputType::error);
        return false;
    }

    // 第二次密码确认
    string password2 = cppIn("请再次输入密码");
    if (password2 != it->password) {
        cppOut("密码错误", outputType::error);
        return false;
    }

    // 检查两次输入是否一致
    if (password1 != password2) {
        cppOut("两次输入的密码不一致", outputType::error);
        return false;
    }

    // 创建临时文件
    ofstream tempFile("user_temp.txt");
    if (!tempFile) {
        cppOut("无法创建临时文件", outputType::error);
        return false;
    }

    // 写入除要删除用户外的所有用户
    for (const auto& user : users) {
        if (user.username != username) {
            tempFile << user.username << " " << user.password << endl;
        }
    }
    tempFile.close();

    // 删除原文件并重命名临时文件
    remove("user.txt");
    if (rename("user_temp.txt", "user.txt") != 0) {
        cppOut("删除用户失败", outputType::error);
        return false;
    }

    cppOut("用户删除成功", outputType::success);
    return true;
}
// 注册新用户
void registerUser(const string& username, const string& password) {
    ofstream file("user.txt", ios::app);
    if (file) {
        file << username << " " << password << endl;
        users.push_back({username, password});
        cppOut("注册成功", outputType::success);
    } else {
        cppOut("无法打开用户文件", outputType::error);
    }
    file.close();
}
void changeUsername(const string& username, const string& newUsername) {
    // 创建临时文件
    ofstream tempFile("user_temp.txt");
    if (!tempFile) {
        cppOut("无法创建临时文件", outputType::error);
        return;
    }

    // 写入所有用户，但将旧用户名替换为新用户名
    for (const auto& user : users) {
        if (user.username == username) {
            tempFile << newUsername << " " << user.password << endl;
        } else {
            tempFile << user.username << " " << user.password << endl;
        }
    }
    tempFile.close();

    // 删除原文件并重命名临时文件
    remove("user.txt");
    if (rename("user_temp.txt", "user.txt") != 0) {
        cppOut("修改用户名失败", outputType::error);
        return;
    }

    cppOut("用户名修改成功", outputType::success);
}
void changePassword(const string& username, const string& newPassword) {
    // 创建临时文件
    ofstream tempFile("user_temp.txt");
    if (!tempFile) {
        cppOut("无法创建临时文件", outputType::error);
        return;
    }

    // 写入所有用户，但将旧密码替换为新密码
    for (const auto& user : users) {
        if (user.username == username) {
            tempFile << user.username << " " << newPassword << endl;
        } else {
            tempFile << user.username << " " << user.password << endl;
        }
    }
    tempFile.close();

    // 删除原文件并重命名临时文件
    remove("user.txt");
    if (rename("user_temp.txt", "user.txt") != 0) {
        cppOut("修改密码失败", outputType::error);
        return;
    }

    cppOut("密码修改成功", outputType::success);
}
// 修改后的login函数，返回用户名或空字符串
string login() {
    // 加载用户数据
    loadUsers();

    // 操作选项
    string options[] = {"登录", "注册","退出"};
    int choice = selectquiz("请选择操作", 3, options, ""); // 补齐第四个参数

    if (choice == 0) { // 登录
        string username = cppIn("请输入用户名");
        string password = cppIn("请输入密码");

        if (users.empty()) {
            cppOut("没有用户信息，请先注册", outputType::warning);
            return "";
        }

        // 查找用户
        auto it = find_if(users.begin(), users.end(), [&](const User& u) {
            return u.username == username;
        });
        
        if (it != users.end()) {
            if (it->password == password) {
                cppOut("登录成功", outputType::success);
                return username; // 返回登录成功的用户名
            } else {
                cppOut("密码错误", outputType::error);
            }
        } else {
            cppOut("用户不存在", outputType::error);
        }
        return ""; // 登录失败返回空字符串

    } else if (choice == 1) { // 注册
        string username = cppIn("请输入用户名");
        string password = cppIn("请输入密码");
        
        // 检查用户名是否已存在
        auto it = find_if(users.begin(), users.end(), [&](const User& u) {
            return u.username == username;
        });
        
        if (it != users.end()) {
            cppOut("用户名已存在", outputType::error);
        } else {
            registerUser(username, password);
        }
        return ""; // 注册流程不返回用户名
    }
    else if (choice == 2) { // 退出
        return "\n"; // 退出登录返回空字符串
    }

    return ""; // 默认返回空字符串
}