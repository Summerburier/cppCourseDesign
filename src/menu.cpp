#include "menu.h"
using namespace std;

// 定义选项数组
const std::string mainTaskPrompt[11] = {
    "添加学生信息",
    "查询学生信息",
    "删除学生信息",
    "修改学生信息",
    "设置分数线",
    "显示所有学生信息",
    "查找录取学生",
    "修改用户名",
    "修改密码",
    "注销用户",
    "退出登录"
};

int maintask(list& studentList, const std::string& userName);

void menu() {
    title();
    loginpart:
    std::string userName = "";
    while(userName == "") {
        userName = login();
        if (userName == "\n") {
            goto ending;
        }
    }
    list studentList;
    studentList.loadFromFile(); // 加载学生数据
    int ans=maintask(studentList, userName);
    if (ans == 1) {
        goto loginpart;
    }
    ending:
    cppOut("退出系统", outputType::info);
}

int maintask(list& studentList, const std::string& userName) {
    int num = 0;
    std::string currentUser = userName;
    while(num != 9 && num != 10) {
        num = selectquiz("请选择操作", 11, mainTaskPrompt, currentUser);
        switch (num) {
        case 0: {
            std::string name = cppIn("请输入学生姓名");
            std::string regNum = cppIn("请输入学生注册号");
            std::string major = cppIn("请输入学生专业");
            std::string ifFreshmanStr = cppIn("是否为应届生（是/否）");
            bool isFreshman = (ifFreshmanStr == "是" || ifFreshmanStr == "1" || ifFreshmanStr == "true");
            int politics = stoi(cppIn("请输入政治分数"));
            int math = stoi(cppIn("请输入数学分数"));
            int foreign = stoi(cppIn("请输入外语分数"));
            int majorScore = stoi(cppIn("请输入专业分数"));
            student s(name, regNum, major, isFreshman, politics, math, foreign, majorScore);
            studentList.insert(s);
            cppOut("添加成功", outputType::success, currentUser);
            studentList.saveToFile(currentUser);
            cppOut("学生信息已保存到文件", outputType::success, currentUser);
            break;
        }
        case 1: {
            const std::string queryModes[2] = {"按姓名查询", "按准考证查询"};
            int mode = selectquiz("请选择查询方式", 2, queryModes, currentUser);

            list resultList;
            if (mode == 0) {
                const std::string queryLevels[2] = {"精确查询", "模糊查询"};
                int level = selectquiz("请选择查询级别", 2, queryLevels, currentUser);

                if (level == 0) {
                    std::string name = cppIn("请输入学生姓名");
                    studentList.Search(searchType::name, name, level::accurate, currentUser);
                } else {
                    std::string name = cppIn("请输入学生姓氏");
                    studentList.Search(searchType::name, name, level::fuzzy, currentUser);
                }

            } else {
                std::string regNum = cppIn("请输入学生注册号");
                studentList.Search(searchType::regristrationNumber, regNum, level::accurate, currentUser);
            }
            std::string out = cppIn("是否导出查询结果（是/否）");
            if (out == "是" || out == "1" || out == "true") {
                resultList.Fout("query_result.txt", currentUser);
            }
            break;
        }
        case 2: {
            std::string regNum = cppIn("请输入学生注册号");
            studentList.deleteInfo(regNum, currentUser);
            break;
        }
        case 3: {
            std::string regNum = cppIn("请输入学生注册号");
            std::string typeStr = cppIn("请选择修改内容(姓名/专业/是否为应届生/政治/数学/外语/专业课)", currentUser);
            std::string newValue = cppIn("请输入新的值", currentUser);
            // 这里需要将typeStr映射到searchType
            searchType type;
            if (typeStr == "姓名") type = searchType::name;
            else if (typeStr == "专业") type = searchType::major;
            else if (typeStr == "是否为应届生") type = searchType::isFreshman;
            else if (typeStr == "政治") type = searchType::Politics;
            else if (typeStr == "数学") type = searchType::Math;
            else if (typeStr == "外语") type = searchType::ForignLanguage;
            else if (typeStr == "专业课") type = searchType::MajorSubject;
            else {
                cppOut("未知修改类型", outputType::error, currentUser);
                break;
            }
            studentList.changeInfo(regNum, type, newValue, currentUser);
            cppOut("修改成功", outputType::success, currentUser);
            studentList.saveToFile(currentUser);
            cppOut("学生信息已保存到文件", outputType::success, currentUser);
            break;
        }
        case 4: {
            studentList.setStandard(currentUser); // 先设置分数线
            list passedList = studentList.filterPassed();
            passedList.displayAll(currentUser); // 输出过滤后的
            studentList.saveToFile(currentUser);
            cppOut("学生信息已保存到文件", outputType::success, currentUser);

            break;
        }
        case 5: {
            studentList.displayAll(currentUser);
            break;
        }
        case 6: {
            list passedList = studentList.filterPassed();
            if (passedList.getHead() != nullptr) {
                passedList = list::sortByTotalScore(passedList);
            }
            passedList.displayAll(currentUser);

            std::string out = cppIn("是否导出录取结果（是/否）");
            if (out == "是" || out == "1" || out == "true") {
                passedList.Fout("passed_result.txt", currentUser);
            }
            break;
        }
        case 7: {
            std::string newUserName = cppIn("请输入新的用户名", currentUser);
            changeUsername(currentUser, newUserName);
            currentUser = newUserName;
            break;
        }
        case 8: {
            std::string newPassword = cppIn("请输入新的密码", currentUser);
            changePassword(currentUser, newPassword);
            break;
        }
        case 9: {
            deleteUser(currentUser);
            cppOut("用户已删除", outputType::success, currentUser);
            return 1;
            
        }
        case 10: {
            cppOut("退出登录", outputType::success, currentUser);
            return 1;
        }
        }
    }
    return 0;
}
