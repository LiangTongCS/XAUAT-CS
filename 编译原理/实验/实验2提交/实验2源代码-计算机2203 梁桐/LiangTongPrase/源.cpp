#include <iostream>   // 提供输入输出功能
#include <fstream>    // 文件流处理
#include <string>     // 字符串类型
#include <vector>     // 动态数组
#include <map>        // 映射容器
#include <set>        // 集合容器
#include <stack>      // 栈容器
#include <iomanip>    // 控制输出格式
#include <cctype>     // 字符分类函数（isdigit, islower）
using namespace std;

// ANSI 颜色代码，用于在终端中高亮显示错误信息
const string RED_TEXT = "\033[31m";  // 红色文本
const string RESET_TEXT = "\033[0m";   // 重置文本样式

// 判断是否为非终结符（非终结符以大写字母开头）
inline bool isNonTerminal(const string& s) {
    return !s.empty() && isupper(static_cast<unsigned char>(s[0]));
}

// 判断字符是否为数字，使用 unsigned char 避免负值断言失败
inline bool isDigitChar(char c) {
    return isdigit(static_cast<unsigned char>(c)) != 0;
}

// 判断字符是否为小写字母
inline bool isLowerChar(char c) {
    return islower(static_cast<unsigned char>(c)) != 0;
}

// 判断字符是否为空白字符（空格、制表符、换行等）
inline bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// 文法存储结构：
// G[A] 保存非终结符 A 的所有产生式，每条产生式由一系列符号（终结符或非终结符）组成
map<string, vector<vector<string>>> G;

// FIRST 和 FOLLOW 集中存放每个非终结符对应的符号集合
map<string, set<string>> FIRST, FOLLOW;

// 预测分析表：PREDICT[A][a] = 产生式 α，表示在栈顶为 A，当前输入符号为 a 时，选用 A -> α
map<string, map<string, vector<string>>> PREDICT;

// 计算 FIRST 集的函数
void computeFirst() {
    bool changed = true;
    // 迭代直到不再有新的符号加入任何 FIRST 集
    while (changed) {
        changed = false;
        // 遍历文法中每个非终结符 A
        for (auto& entry : G) {
            const string& A = entry.first;
            // 遍历 A 的每条产生式 prod
            for (auto& prod : entry.second) {
                bool canEps = true;  // 标记当前产生式是否能推 ε
                // 遍历产生式右部的每个符号 X
                for (auto& X : prod) {
                    if (isNonTerminal(X)) {
                        // 若 X 是非终结符，将 FIRST[X] 中除 ε 外的所有符号加入 FIRST[A]
                        for (auto& a : FIRST[X]) {
                            if (a != "ε" && FIRST[A].insert(a).second) {
                                changed = true;
                            }
                        }
                        // 若 X 的 FIRST 中不含 ε，则该产生式不能再继续推 ε
                        if (!FIRST[X].count("ε")) {
                            canEps = false;
                            break;
                        }
                    }
                    else {
                        // X 是终结符或 ε，将其加入 FIRST[A]（ε 也需加入时在后面处理）
                        if (X != "ε" && FIRST[A].insert(X).second) {
                            changed = true;
                        }
                        canEps = false;  // 遇到终结符或 ε，不再继续查看后续符号
                        break;
                    }
                }
                // 若整条产生式都能推 ε，则将 ε 加入 FIRST[A]
                if (canEps) {
                    if (FIRST[A].insert("ε").second) {
                        changed = true;
                    }
                }
            }
        }
    }
}

// 计算 FOLLOW 集的函数
void computeFollow() {
    // 起始符号 E 的 FOLLOW 集包含 '$'
    FOLLOW["E"].insert("$");
    bool changed = true;
    // 迭代直到不再有新的符号加入任何 FOLLOW 集
    while (changed) {
        changed = false;
        // 遍历每个产生式 A -> prod
        for (auto& entry : G) {
            const string& A = entry.first;
            for (auto& prod : entry.second) {
                // 遍历产生式右部中的每个位置 i
                for (size_t i = 0; i < prod.size(); ++i) {
                    const string& B = prod[i];
                    if (!isNonTerminal(B)) continue;  // 只处理非终结符 B

                    bool canEps = true;  // 标记后续符号是否都能推 ε
                    // 检查 B 之后的符号 β
                    for (size_t j = i + 1; j < prod.size(); ++j) {
                        const string& beta = prod[j];
                        if (isNonTerminal(beta)) {
                            // 将 FIRST[beta]（去 ε）加入 FOLLOW[B]
                            for (auto& a : FIRST[beta]) {
                                if (a != "ε" && FOLLOW[B].insert(a).second) {
                                    changed = true;
                                }
                            }
                            // 若 beta 的 FIRST 中不含 ε，则停止传播
                            if (!FIRST[beta].count("ε")) {
                                canEps = false;
                                break;
                            }
                        }
                        else {
                            // beta 为终结符，直接加入 FOLLOW[B]
                            if (FOLLOW[B].insert(beta).second) {
                                changed = true;
                            }
                            canEps = false;
                            break;
                        }
                    }
                    // 若 B 后续符号都可推 ε，则将 FOLLOW[A] 全部加入 FOLLOW[B]
                    if (canEps) {
                        for (auto& f : FOLLOW[A]) {
                            if (FOLLOW[B].insert(f).second) {
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

// 构建 LL(1) 预测分析表 PREDICT
void buildPredictTable() {
    for (auto& entry : G) {
        const string& A = entry.first;
        PREDICT[A].clear();  // 清空旧表项
        for (auto& prod : entry.second) {
            bool prodEps = (prod.size() == 1 && prod[0] == "ε");
            set<string> firstAlpha;
            bool canEps = true;
            // 计算 FIRST(prod)
            if (!prodEps) {
                for (auto& X : prod) {
                    if (isNonTerminal(X)) {
                        for (auto& a : FIRST[X]) {
                            if (a != "ε") firstAlpha.insert(a);
                        }
                        if (!FIRST[X].count("ε")) { canEps = false; break; }
                    }
                    else {
                        firstAlpha.insert(X);
                        canEps = false;
                        break;
                    }
                }
            }
            // 将 FIRST(prod) 中的符号作为预测符号，填表
            for (auto& a : firstAlpha) {
                PREDICT[A][a] = prod;
            }
            // 若产生式可推 ε，则对 FOLLOW[A] 中的每个 b 也填 ε 产生式
            if (prodEps || canEps) {
                for (auto& b : FOLLOW[A]) {
                    PREDICT[A][b] = prod;
                }
            }
        }
    }
}

// 打印 FIRST 集和 FOLLOW 集，便于调试
void printFirstFollow() {
    cout << "\n== FIRST 集 ==\n";
    for (auto& entry : FIRST) {
        cout << entry.first << ": { ";
        for (auto& a : entry.second) cout << a << ' ';
        cout << "}\n";
    }
    cout << "\n== FOLLOW 集 ==\n";
    for (auto& entry : FOLLOW) {
        cout << entry.first << ": { ";
        for (auto& a : entry.second) cout << a << ' ';
        cout << "}\n";
    }
}

// 对给定输入串执行 LL(1) 最左推导，并打印每次栈和输入的状态
// 对给定输入串执行 LL(1) 最左推导，并打印每次栈和输入的状态
void parse(const string& input) {
    stack<string> st;
    st.push("$");  // 底部符号
    st.push("E");  // 起始符号

    // 将输入串转换为 token 序列：num, id 或单字符符号
    vector<string> tokens;
    for (size_t i = 0; i < input.size();) {
        if (isWhitespace(input[i])) { ++i; continue; }
        if (isDigitChar(input[i])) {
            tokens.push_back("num");
            while (i < input.size() && isDigitChar(input[i])) ++i;
        }
        else if (isLowerChar(input[i])) {
            tokens.push_back("id");
            ++i;
        }
        else {
            tokens.push_back(string(1, input[i]));
            ++i;
        }
    }
    if (tokens.empty() || tokens.back() != "$") tokens.push_back("$");

    // 打印表格头
    cout << left << setw(10) << "栈顶" << " | "
        << right << setw(20) << "剩余输入" << " | "
        << right << setw(10) << "动作" << '\n';
    cout << string(10, '-') << "-+-" << string(20, '-') << "-+-" << string(10, '-') << '\n';

    size_t idx = 0;
    bool hasError = false; // 标记是否发生错误
    // 当栈不为空时，重复预测分析过程
    while (!st.empty()) {
        string X = st.top(); st.pop();
        // 构造剩余输入字符串用于打印
        string rem;
        for (size_t j = idx; j < tokens.size(); ++j) rem += tokens[j];

        cout << left << setw(10) << X << " | " << right << setw(20) << rem << " | ";

        // 若栈顶为终结符或 '$'
        if (!isNonTerminal(X)) {
            if (idx < tokens.size() && tokens[idx] == X) {
                cout << right << setw(10) << "匹配" << '\n';
                ++idx;
            }
            else {
                cout << RED_TEXT << right << setw(10) << "错误" << RESET_TEXT << '\n';
                string current_token = (idx < tokens.size()) ? tokens[idx] : "$";
                cerr << RED_TEXT << "语法错误: 期望 '" << X << "'，但找到 '" << current_token << "'" << RESET_TEXT << '\n';
                hasError = true;
                // 错误恢复：跳过当前输入符号
                if (idx < tokens.size()) ++idx;
                // 不压回X，继续处理栈顶的下一个符号
            }
            continue;
        }

        // 栈顶为非终结符，取当前输入符号 a
        string a = (idx < tokens.size() ? tokens[idx] : "$");
        // 查预测表表项
        if (PREDICT[X].count(a)) {
            auto prod = PREDICT[X][a];
            // 打印产生式动作 X->prod
            string act = X + "->";
            for (auto& s : prod) act += s;
            cout << right << setw(10) << act << '\n';
            // 将产生式右部符号逆序入栈（忽略 ε）
            for (auto it = prod.rbegin(); it != prod.rend(); ++it) {
                if (*it != "ε") st.push(*it);
            }
        }
        else {
            cout << RED_TEXT << right << setw(10) << "错误" << RESET_TEXT << '\n';
            cerr << RED_TEXT << "语法错误: 在 " << X << " 处遇到意外的符号 '" << a << "'" << RESET_TEXT << '\n';
            hasError = true;

            // 错误恢复：跳过输入直到遇到 FOLLOW[X] 中的符号
            const auto& follow = FOLLOW[X];
            while (idx < tokens.size()) {
                if (follow.count(tokens[idx])) break;
                ++idx;
            }
            // X 已被弹出，继续处理栈中的下一个符号
        }
    }

    // 最终检查输入是否完全处理
    if (idx < tokens.size() && tokens[idx] != "$") {
        cout << RED_TEXT << left << setw(10) << "" << " | " << right << setw(20) << ""
            << " | " << RED_TEXT << right << setw(10) << "错误" << RESET_TEXT << '\n';
        cerr << RED_TEXT << "语法错误: 输入未完全处理，剩余符号 '";
        for (size_t j = idx; j < tokens.size(); ++j) cerr << tokens[j];
        cerr << "'" << RESET_TEXT << '\n';
    }
    else if (!hasError) {
        cout << left << setw(10) << "" << " | " << right << setw(20) << ""
            << " | " << right << setw(10) << "接受" << '\n';
    }
}

int main() {
    // 文法定义：
    G["E"] = { {"T","E'"} };
    G["E'"] = { {"+","T","E'"},{"ε"} };
    G["T"] = { {"F","T'"} };
    G["T'"] = { {"*","F","T'"},{"ε"} };
    G["F"] = { {"(","E",")"},{"num"},{"id"} };

    // 计算 FIRST 和 FOLLOW 集
    computeFirst();
    computeFollow();
    // 手动将 ')' 和 '$' 加入 T' 的 FOLLOW，保证括号归约
    FOLLOW["T'"].insert(")");
    FOLLOW["T'"].insert("$");

    // 构建预测分析表并打印 FIRST/FOLLOW
    buildPredictTable();
    printFirstFollow();

    // 用户交互提示
    cout << "输入模式说明:\n"
        << "1. 命令行模式: 表达式可包含 +,*,(),num,id,$; 示例 a+num*(b+c)$\n"
        << "2. 文件模式: 指定 txt 文件，每行一个表达式，自动补全 $。\n";
    cout << "请选择模式(1-命令行, 2-文件): ";
    int mode; cin >> mode;

    if (mode == 1) {
        int cont = 1;
        string inp;
        while (cont == 1) {
            cout << "\n输入要求：+ * ( ) num id 以及 $; 示例 a+num*(b+3)$\n";
            cout << "请输入表达式: ";
            cin >> ws;
            getline(cin, inp);
            if (!inp.empty() && inp.back() != '$') inp.push_back('$');
            parse(inp);
            cout << "是否继续? (1-继续,0-退出): ";
            cin >> cont;
        }
    }
    else {
        int cont = 1;
        while (cont == 1) {
            cout << "\n请输入文件名: ";
            string fname; cin >> fname;
            ifstream ifs(fname);
            if (!ifs) {
                cerr << RED_TEXT << "无法打开文件: " << fname << RESET_TEXT << endl;
                return 1;
            }
            string line;
            int lineno = 1;
            while (getline(ifs, line)) {
                if (line.empty()) { ++lineno; continue; }
                if (line.back() != '$') line.push_back('$');
                cout << "\n-- 第 " << lineno << " 行分析 --\n";
                parse(line);
                ++lineno;
            }
            cout << "是否继续? (1-继续,0-退出): ";
            cin >> cont;
        }
    }
    return 0;
}
