#include <iostream>
#include <string>
using namespace std;
double opera_res(char operand, double op1, double op2) {
    if (operand == '+') { return (op1 + op2); }
    else if (operand == '-') { return (op1 - op2); }
    else if (operand == '*') { return (op1 * op2); }
    else if (operand == '/') { return (op1 / op2); }
}
int choose_type(char c) {
    if (c == '+') { return 1; }
    else if (c == '-') { return 1; }
    else if (c == '*') { return 2; }
    else if (c == '/') { return 2; }
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int main()
{
    //сложение символов в строку
    /*string str = "LOXisyouLOX";
    int temp = 0;
    for (int i = 0; i < str.length(); i++) {    
        if (temp != 0 && temp != 3) {
            temp++;
            cout << "kek" << endl;
            continue;
        }
        else if (temp == 3) {
            temp = 0;
        }
        if (isupper(str[i])) {
            temp = 1;
            cout << str[i] << str[i + 1] << str[i + 2] << endl;
        }
        else if (islower(str[i])) {
            cout << "da";
        }
    }*/
    
    

    return 0;
}
