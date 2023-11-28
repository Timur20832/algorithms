/*26. Имеется  выражение  в  постфиксной  форме,   включающее 
обращение к функциям SIN, COS, EXP.  Переменные  заданы  одной 
строчной латинской буквой.  Запросить  значения  переменных  и 
вычислить выражение. Представить  его  в  инфиксной  форме  со 
скобками. Лишние скобки присутствовать не должны (11). Visual Studio 2022 Сахабутдинов Тимур ПС-23 одинаковые переменные и обработка 
a*(b/c) без скобок abc//  */
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

struct Node {
    string data;
    char type;
    Node* next;
};

struct Nodeint {
    double data;
    Nodeint* next;
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}


bool isFunction(string s) {
    return (s == "SIN" || s == "COS" || s == "EXP");
}

double opera_res(char operand, double op1, double op2){
    if      (operand == '+') { return (op1 + op2); }
    else if (operand == '-') { return (op1 - op2); }
    else if (operand == '*') { return (op1 * op2); }
    else if (operand == '/') { return (op1 / op2); }
}

double opera_func(string func, double op1) {
    if (func == "SIN") { return sin(op1); }
    else if (func == "COS") { return cos(op1); }
    else if (func == "EXP") { return exp(op1); }
}

string toInfix(string postfix) {
    Node* top = nullptr;
    Node* del = nullptr;
    int temp = 0;
    string result = "", checking = "";
    for (int i = 0; i < postfix.length(); i++) {
        if (temp != 0 && temp != 3) {
            temp++;
            if (temp == 3) {
                temp = 0;
            }
            continue;
        }
        if (islower(postfix[i]) and isalpha(postfix[i])) {
            string varible;
            if (checking.find(postfix[i]) == string::npos) {
                cout << "введите значение пременной " << postfix[i] << endl;
                cin >> varible;
                checking = checking + postfix[i] + varible;
            }
            else {
                varible = checking[checking.find(postfix[i]) + 1];
            }
            result = result + varible + 'c';

            Node* ptr = new Node;
            ptr->data = postfix[i];
            ptr->type = '0';
            ptr->next = top;
            top = ptr;
        }
        else if (isupper(postfix[i]) and isalpha(postfix[i])) {
            string str{ postfix[i], postfix[i + 1], postfix[i + 2] };
            temp = 1;
            if (isFunction(str)) {
                result = result + str;
                string operand = top->data;
                char typeF = top->type;
                del = top;
                top = top->next;
                delete top;

                string expression;
                if (typeF != '0') {
                    expression = str + "(" + operand + ")";
                }
                else {
                    expression = str + operand;
                }
                Node* ptr = new Node;
                ptr->data = expression;
                ptr->next = top;
                top = ptr;
            }
        }
        else if (isOperator(postfix[i])) {
            result = result + postfix[i];
            string operand2 = top->data;
            char type;
            char type2 = top->type;
            del = top;
            top = top->next;
            delete del;

            string operand1 = top->data;
            char type1 = top->type;
            del = top;
            top = top->next;
            delete del;

            string expression;
            type = postfix[i];
            //AB+C*   (A+B)*(C+D) (A+B)*(C+D)/E+K AB* = a*b 
            if (type == '*' || type == '/') {
                if ((type1 == '+' || type1 == '-') && (type2 == '-' || type2 == '+') && (type == '*' || type == '/')) {
                    expression = "(" + operand1 + ")" + postfix[i] + "(" + operand2 + ")";
                }
                else if ((type2 == '0')  && type1 != '*' && type1 != '/' && type1 != '0') {
                    expression = "(" + operand1 + ")" + postfix[i] + operand2;
                }
                else if ((type2 == '+' || type2 == '-') && (type == '*' || type == '/')) {
                    expression = operand1 + postfix[i] + "(" + operand2 + ")";
                }
                //условие для (a*b)/(e*k) 
                else if (((type2 == '*' && type == '/') || (type2 == '/' && type == '*')) && type1 != '0') {
                    expression = operand1 + postfix[i] + "(" + operand2 + ")";
                }
                else if ((type2 == '*' && type == '/' && type1 == '0')) {
                    expression = operand1 + postfix[i] + "(" + operand2 + ")";
                }
                else if ((type2 == '/') && (type == '/') && (type1 == '0')) {
                    expression = operand1 + postfix[i] + "(" + operand2 + ")";
                }
                else {
                    expression = operand1 + postfix[i] + operand2;
                }
            } 
            else if (type == '-') {
                if (type2 == '0' || type2 == '*' || type2 == '/') {
                    expression = operand1 + postfix[i] + operand2;
                }
                else {
                    expression = operand1 + postfix[i] + "(" + operand2 + ")";
                }
            }
            else {
                expression = operand1 + postfix[i] + operand2;
            }

            Node* ptr = new Node;
            ptr->data = expression;
            ptr->type = type;
            ptr->next = top;
            top = ptr;
        }
        else {
            cout << "неккореткный ввод символа: " << postfix[i];
            return "";
        }
    }
    result = result + " " + top->data;
    return result;
}

double calculation_res(string postfix) {
    double value_res = 0;
    Nodeint* top = nullptr;
    int temp = 0, tempd = 0;
    for (int i = 0; i < postfix.length(); i++) {
        if (temp != 0 && temp != 3) {
            temp++;
            if (temp == 3) {
                temp = 0;
            }
            continue;
        }
        if (tempd != 0) {
            tempd--;
            continue;
        }
        if (isdigit(postfix[i])) {
            int j = i;
            string result = "";
            while (isdigit(postfix[j])) {
                result += postfix[j];
                j++;
                tempd++;
            };
            Nodeint* ptr = new Nodeint;
            ptr->data = stod(result);
            ptr->next = top;
            top = ptr;
        }

        else if (isOperator(postfix[i])) {
            double op2 = top->data;
            top = top->next;
            if (top != nullptr) {
                double op1 = top->data;
                top->data = opera_res(postfix[i], op1, op2);
            }
        }
        else if (isupper(postfix[i]) and isalpha(postfix[i])) {
            string str{ postfix[i], postfix[i + 1], postfix[i + 2] };
            if (isFunction(str)) {
                double operand = top->data;
                top->data = opera_func(str, operand);
                temp = 1;
            }
        }
    }
    return top->data;
}

int main() {
    setlocale(LC_ALL, "RU");

    string postfixExpression;
    cout << "Введите выражение в постфиксной форме: ";
    cin >> postfixExpression;
    string somedata = toInfix(postfixExpression);
    
    if (somedata != "") {
        int i = 0; double result = 0;
        string infix = "", postfix_value = "";

        while (somedata[i] != ' ') {
            postfix_value = postfix_value + somedata[i];
            i++;
        };
        i++;
        while (i < somedata.length()) {
            infix = infix + somedata[i];
            i++;
        }

        result = calculation_res(postfix_value);
        cout << "Выражение в инфиксной форме: " << infix << endl;
        cout << "Результат: " << result;
    }
    return 0;
}
