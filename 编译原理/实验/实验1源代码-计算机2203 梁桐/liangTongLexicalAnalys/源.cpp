#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <cstdlib>
using namespace std;

// ANSI 颜色代码，用于红色错误信息显示
#define RED_TEXT "\033[31m"
#define RESET_TEXT "\033[0m"

// 关键字表：关键字 -> 种别码
static map<string, int> keywordMap = {
    {"void", 101},
    {"main", 102},
    {"int",  103},
    {"char", 104},
    {"if",   105},
    {"else", 106},
    {"for",  107},
    {"while",108}
};

// 运算符表（支持多字符运算符优先匹配）
static map<string, int> opMap = {
    {"==", 206}, {"<=", 209}, {">=", 210},
    {"++", 211}, {"--", 212},
    {"+", 201},  {"-", 202},  {"*", 203},  {"/", 204},
    {"=", 205},  {"<", 207},  {">", 208}
};

// 界符表（单字符）
static map<char, int> delimiterMap = {
    {';', 301}, {'(', 302}, {')', 303},
    {'{', 304}, {'}', 305}, {'[', 306}, {']', 307}
};

// Token结构，用于存储识别结果
struct Token {
    int code;       // 种别码
    string lexeme;  // 单词字符串
    Token() : code(0), lexeme("") {}
};

// 判断是否为字母或下划线
bool isLetterOrUnderscore(char c) {
    return (isalpha(c) || c == '_');
}

// 判断是否为数字字符
bool isDigitChar(char c) {
    return isdigit(c);
}

// 判断字符是否可能构成运算符或界符的组成部分
bool isOpDelimChar(char c) {
    string opDelim = "+-*/=<>(){}[];"; // 运算符和界符中可能出现的字符
    return (opDelim.find(c) != string::npos);
}

// 分析单个单词，返回对应的 Token
// 识别顺序：关键字 → 运算符 → 界符 → 标识符 → 数字常量 → 无法识别
Token analyzeToken(const string& word) {
    Token token;
    // 1) 判断是否为关键字
    if (keywordMap.find(word) != keywordMap.end()) {
        token.code = keywordMap[word];
        token.lexeme = word;
        return token;
    }
    // 2) 判断是否为运算符
    if (opMap.find(word) != opMap.end()) {
        token.code = opMap[word];
        token.lexeme = word;
        return token;
    }
    // 3) 判断是否为界符（只考虑单字符界符）
    if (word.size() == 1 && delimiterMap.find(word[0]) != delimiterMap.end()) {
        token.code = delimiterMap[word[0]];
        token.lexeme = word;
        return token;
    }
    // 4) 判断是否为标识符
    // 标识符要求：首字符为字母或下划线，后续字符只能为字母或下划线（不允许数字）
    bool isIdentifier = true;
    if (!word.empty() && isLetterOrUnderscore(word[0])) {
        for (size_t i = 1; i < word.size(); i++) {
            // 修改：允许标识符后续可以包含数字
            if (!isLetterOrUnderscore(word[i]) && !isdigit(word[i])) {
                isIdentifier = false;
                break;
            }
        }
    }
    else {
        isIdentifier = false;
    }
    if (isIdentifier) {
        token.code = 400;  // 400 表示标识符
        token.lexeme = word;
        return token;
    }
    // 5) 判断是否为数字常量（整数、小数、科学计数法）
    bool isNumber = true;
    int dotCount = 0;
    int eCount = 0;
    bool afterE = false;
    if (word.empty()) isNumber = false;
    for (size_t i = 0; i < word.size(); i++) {
        char c = word[i];
        if (isdigit(c)) {
            // 数字正常
        }
        // 增加判断：若遇到字母（除e/E之外），则退出数字判断
        else if (isLetterOrUnderscore(c) && (c != 'e' && c != 'E')) {
            isNumber = false;
            break;
        }
        else if (c == '.') {
            dotCount++;
            if (dotCount > 1 || eCount > 0) {
                isNumber = false;
                break;
            }
        }
        else if (c == 'e' || c == 'E') {
            eCount++;
            if (eCount > 1 || i == 0) {
                isNumber = false;
                break;
            }
            afterE = true;
        }
        else if ((c == '+' || c == '-') && afterE) {
            afterE = false;
        }
        else {
            isNumber = false;
            break;
        }
    }
    if (isNumber) {
        token.code = 500; // 500 表示数字常量
        token.lexeme = word;
        return token;
    }
    // 6) 如果均不匹配，则无法识别
    token.code = 0;
    token.lexeme = word;
    return token;
}

// 对一行内容进行分词处理：
// 1. 逐字符扫描
// 2. 遇到连续空白符或制表符时，统计并输出提示信息
// 3. 根据字符类型自动切分单词
vector<string> tokenizeLine(const string& line) {
    vector<string> tokens;
    size_t pos = 0;
    while (pos < line.size()) {
        // 如果遇到空白符或制表符，统计并输出提示，然后跳过
        if (line[pos] == ' ' || line[pos] == '\t') {
            int count = 0;
            while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t')) {
                count++;
                pos++;
            }
            cout << "[跳过 " << count << " 个空白符]" << endl;
            continue;
        }
        // 根据当前字符决定分词规则
        char cur = line[pos];
        string tokenStr = "";
        // 如果是字母或下划线，则扫描标识符（只允许字母和下划线，后续可含数字）
        if (isLetterOrUnderscore(cur)) {
            while (pos < line.size() && (isLetterOrUnderscore(line[pos]) || isdigit(line[pos]))) {
                tokenStr.push_back(line[pos]);
                pos++;
            }
        }
        // 如果是数字，则扫描数字（包括小数及科学计数法部分）
        else if (isdigit(cur)) {
            while (pos < line.size() && (isdigit(line[pos]) || line[pos] == '.' ||
                line[pos] == 'e' || line[pos] == 'E' ||
                ((line[pos] == '+' || line[pos] == '-') && pos > 0 &&
                    (line[pos - 1] == 'e' || line[pos - 1] == 'E'))))
            {
                tokenStr.push_back(line[pos]);
                pos++;
            }
        }
        // 如果是可能的运算符或界符，则先尝试两字符匹配（如 "==", "<=", "++", "--"）
        else if (isOpDelimChar(cur)) {
            if (pos + 1 < line.size()) {
                string twoChars;
                twoChars.push_back(line[pos]);
                twoChars.push_back(line[pos + 1]);
                if (opMap.find(twoChars) != opMap.end()) {
                    tokenStr = twoChars;
                    pos += 2;
                }
                else {
                    tokenStr.push_back(cur);
                    pos++;
                }
            }
            else {
                tokenStr.push_back(cur);
                pos++;
            }
        }
        // 否则将当前字符作为单独的 token
        else {
            tokenStr.push_back(cur);
            pos++;
        }
        tokens.push_back(tokenStr);
    }
    return tokens;
}

// 对一行进行处理，分词后每个 token 进行词法识别输出
// 这里增加了行号参数，在文件输入模式下用于报错显示
void processLine(const string& line, int lineNum) {
    vector<string> tokens = tokenizeLine(line);
    bool hasError = false;  // 标志本行是否有错误
    for (size_t i = 0; i < tokens.size(); i++) {
        Token tk = analyzeToken(tokens[i]);
        // 如果种别码为 0，则认为无法识别
        if (tk.code == 0) {
            cout << RED_TEXT << "[错误] 第 " << lineNum << " 行: 无法识别的词素 '" << tk.lexeme << "'" << RESET_TEXT << endl;
            hasError = true;
        }
        else {
            cout << "种别码：" << tk.code << ", 单词：" << tk.lexeme << endl;
        }
    }
    if (hasError)
        cout << endl;
}

int main() {
    while (true) {
        cout << "请选择输入模式：\n1. 文件输入\n2. 控制台输入\n3. 退出程序" << endl;
        char mode = 0;
        cin >> mode;
        cin.ignore(); // 清除换行符

        if (mode == '1') {
            // 文件输入模式
            cout << "请输入包含C语言代码的.c文件名（例如 code.c）:" << endl;
            string filename;
            getline(cin, filename);

            ifstream infile(filename);
            if (!infile.is_open()) {
                cerr << RED_TEXT << "无法打开文件 " << filename << RESET_TEXT << endl;
                continue; // 返回模式选择界面
            }

            cout << "读取文件内容并进行词法分析：" << endl;
            string line;
            int lineNum = 0;
            while (getline(infile, line)) {
                lineNum++;
                processLine(line, lineNum);
            }
            infile.close();
            cout << "文件词法分析完成！" << endl;
        }
        else if (mode == '2') {
            // 控制台输入模式
            cout << "请输入包含单词的句子进行词法分析（输入 'quit' 退出该模式）:" << endl;
            int lineNum = 0;
            while (true) {
                lineNum++;
                cout << "> ";
                string input;
                getline(cin, input);
                if (input == "quit")
                    break;
                processLine(input, lineNum);
            }
        }
        else if (mode == '3') {
            cout << "程序退出！" << endl;
            break;
        }
        else {
            cout << RED_TEXT<< "输入模式错误，请重新选择！" << RESET_TEXT << endl;
        }
    }
    return 0;
}
