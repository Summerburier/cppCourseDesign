#include "list.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;



void list::insert(const student& s) {
    node* newNode = new node(s); // 调用新构造函数
    newNode->next = head;
    head = newNode;
    size++;
}


void list::displayAll(const std::string& userName) const {
    if (head == NULL) {
        cppOut("学生列表为空", outputType::info, userName);
        return;
    }


    cppOut("学生列表:", outputType::info, userName);
    formOut(*this);
    cppOut("学生列表显示完毕", outputType::success, userName);
}
void list::Search(searchType type, const string& value, level le, const string& userName) const {
    node* current = head;
    list resultList;
    while (current != NULL) {
        switch (type) {
            case searchType::name:
                if (le == level::accurate) {
                    if (current->data.getName() == value) {
                        resultList.insert(current->data);
                    }
                } else { // 模糊查询
                    if (current->data.getName().find(value) != string::npos) {
                        resultList.insert(current->data);
                    }
                }
                break;
            case searchType::regristrationNumber:
                if (current->data.getRegristrationNumber() == value) {
                    resultList.insert(current->data);
                }
                break;
           
        }
        current = current->next;
    }
    if (resultList.size == 0) {
        cppOut("没有找到符合条件的学生", outputType::error, userName);
    } else {
        formOut(resultList);
    }
}
void list::changeInfo(const std::string& regristrationNumber, searchType type, const std::string& value, const std::string& userName) {
    node* current = head;
    while (current != NULL) {
        if (current->data.getRegristrationNumber() == regristrationNumber) {
            switch (type) {
                case searchType::name:
                    current->data.setName(value);
                    break;
                case searchType::major:
                    current->data.setMajor(value);
                    break;
                case searchType::isFreshman:
                    current->data.setIsFreshman(value == "是");
                    break;
                case searchType::Politics:
                    current->data.setPolitics(stoi(value));
                    break;
                case searchType::Math:
                    current->data.setMath(stoi(value));
                    break;
                case searchType::ForignLanguage:
                    current->data.setForignLanguage(stoi(value));
                    break;
                case searchType::MajorSubject:
                    current->data.setMajorSubject(stoi(value));
                    break;
            }
            cppOut("学生信息已更新", outputType::success, userName);
            return;
        }
        current = current->next;
    }
    cppOut("未找到对应的学生", outputType::error, userName);
}

void list::deleteInfo(const std::string& regristrationNumber, const std::string& userName)
{
    node* current = head;
    node* previous = NULL;
    while (current != NULL) {
        if (current->data.getRegristrationNumber() == regristrationNumber) {
            if (previous == NULL) {
                head = current->next; // 删除头节点
            } else {
                previous->next = current->next; // 删除非头节点
            }
            delete current; // 释放内存
            size--;
            cppOut("学生信息已删除", outputType::success, userName);
            return;
        }
        previous = current;
        current = current->next;
    }
    cppOut("未找到对应的学生", outputType::error, userName); 
}
void list::setStandard(const std::string& userName) {

    int minPolitics = std::stoi(cppIn("请输入政治分数线"));
    int minMath = std::stoi(cppIn("请输入数学分数线"));
    int minForeign = std::stoi(cppIn("请输入外语分数线"));
    int minMajor = std::stoi(cppIn("请输入专业分数线"));
    int minTotal = std::stoi(cppIn("请输入总分线"));

    // 这里只能存储单科分数线，minTotal你可以作为成员变量单独保存
    standard->data.setPolitics(minPolitics);
    standard->data.setMath(minMath);
    standard->data.setForignLanguage(minForeign);
    standard->data.setMajorSubject(minMajor);
    standard->data.setAllScore(minTotal);

    cppOut("分数线已设置", outputType::success, userName);
}
void list::loadFromFile() {
    std::string filename = "data.txt";
    cppOut("正在加载学生数据...", outputType::info);

    std::ifstream fin(filename);
    if (!fin) {
        // 文件不存在，创建空文件
        std::ofstream fout(filename);
        fout.close();
        cppOut("未找到学生数据文件，已新建空文件", outputType::warning);
        head = nullptr;
        size = 0;
        return;
    }


    std::string line;
    // 读取第一行（分数线），可选
    if (std::getline(fin, line)) {
        std::istringstream iss(line);
        int totalLine, minPolitics, minMath, minForeign, minMajor;
        iss >> totalLine >> minPolitics >> minMath >> minForeign >> minMajor;
        this->standard = new node(student("", "", "", false, minPolitics, minMath, minForeign, minMajor));
        cppOut("分数线已设置", outputType::info);
        // 可保存到成员变量
    }

    // 读取学生信息
    bool hasStudent = false;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string name, regNum, isFreshmanStr;
        int politics, math, foreign, major, total;
        iss >> name >> regNum >> isFreshmanStr >> politics >> math >> foreign >> major >> total;
        bool isFreshman = (isFreshmanStr == "是" || isFreshmanStr == "1" || isFreshmanStr == "true");
        student s(name, regNum, "", isFreshman, politics, math, foreign, major);
        insert(s);
        hasStudent = true;
    }
    if (hasStudent) {
        cppOut("学生数据加载完成", outputType::success);
    } else {
        cppOut("学生数据文件为空", outputType::warning);
    }
}

void list::saveToFile(const std::string& userName) const {
    cppOut("正在保存学生数据...", outputType::info, userName);
    std::ofstream fout("data.txt");
    if (!fout) {
        cppOut("无法打开文件进行写入", outputType::error, userName);
        return;
    }
    // 写入分数线
    if (this->standard != nullptr) {
        const student& stdStu = this->standard->data;
        fout << stdStu.getAllScore() << " "
             << stdStu.getPolitics() << " "
             << stdStu.getMath() << " "
             << stdStu.getForignLanguage() << " "
             << stdStu.getMajorSubject() << "\n";
    }
    // 写入学生信息
    node* current = this->head;
    while (current != nullptr) {
        fout << current->data.getName() << " "
             << current->data.getRegristrationNumber() << " "
             << (current->data.getIsFreshman() ? "是" : "否") << " "
             << current->data.getPolitics() << " "
             << current->data.getMath() << " "
             << current->data.getForignLanguage() << " "
             << current->data.getMajorSubject() << " "
             << current->data.getAllScore() << "\n";
        current = current->next;
    }
    fout.close();
    cppOut("学生数据已保存", outputType::success, userName);
}
list list::filterPassed() const {
    list result;
    if (standard == nullptr) {
        cppOut("请先设置分数线", outputType::error);
        return result;
    }
    // 获取分数线
    const student& stdStu = standard->data;
    int minPolitics = stdStu.getPolitics();
    int minMath = stdStu.getMath();
    int minForeign = stdStu.getForignLanguage();
    int minMajor = stdStu.getMajorSubject();
    int minTotal = stdStu.getAllScore();

    node* current = head;
    while (current) {
        const student& s = current->data;
        //int total = s.getPolitics() + s.getMath() + s.getForignLanguage() + s.getMajorSubject();
        if (s.getPolitics() >= minPolitics &&
            s.getMath() >= minMath &&
            s.getForignLanguage() >= minForeign &&
            s.getMajorSubject() >= minMajor &&
            s.getAllScore() >= minTotal) {
            result.insert(s); // 深拷贝插入
        }
        current = current->next;
    }
    return result;
}

static list mergeList(const list& l1, const list& l2) {
    list result;
    node* p1 = l1.getHead();
    node* p2 = l2.getHead();

    // 先收集所有节点
    vector<student> students;
    while (p1 && p2) {
        int score1 = p1->data.getAllScore();  // 假设有getTotalScore()
        int score2 = p2->data.getAllScore();
        
        if (score1 > score2) {
            students.push_back(p1->data);
            p1 = p1->next;
        } else {
            students.push_back(p2->data);
            p2 = p2->next;
        }
    }
    // 处理剩余节点
    while (p1) {
        students.push_back(p1->data);
        p1 = p1->next;
    }
    while (p2) {
        students.push_back(p2->data);
        p2 = p2->next;
    }
    
    // 反向插入以保持降序
    for (auto it = students.rbegin(); it != students.rend(); ++it) {
        result.insert(*it);
    }
    
    return result;
}

// 归并排序递归函数
static list mergeSort(node* head) {
    if (!head || !head->next) {
        list single;
        if (head) single.insert(head->data);
        return single;
    }
    node* slow = head;
    node* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    node* mid = slow->next;
    slow->next = nullptr;
    list left = mergeSort(head);
    list right = mergeSort(mid);
    return mergeList(left, right);
}

// 归并排序主函数，返回新list（深拷贝）
list list::sortByTotalScore(const list& src) {
    return mergeSort(src.getHead());
}

void list::Fout(const std::string& fileName, const std::string& userName) const {
    if (head == nullptr) {
        cppOut("学生列表为空", outputType::error, userName);
        
    }
    std::ofstream fout(fileName);
    if (!fout) {
        cppOut("无法打开文件进行写入", outputType::error, userName);

    }
    node* current = head;
    while (current != nullptr) {
        fout << current->data.getName() << " "
             << current->data.getRegristrationNumber() << " "
             << (current->data.getIsFreshman() ? "是" : "否") << " "
             << current->data.getPolitics() << " "
             << current->data.getMath() << " "
             << current->data.getForignLanguage() << " "
             << current->data.getMajorSubject() << " "
             << current->data.getAllScore() << "\n";
        current = current->next;
    }
    fout.close();
    cppOut("学生数据已输出到文件", outputType::success, userName);
    return ;
}
