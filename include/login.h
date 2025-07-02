#pragma once
#include <string>

std::string login(); // 修改为返回string
bool deleteUser(const std::string& username);
void changeUsername(const std::string& username, const std::string& newUsername);
void changePassword(const std::string& username, const std::string& newPassword);
std::string login();
