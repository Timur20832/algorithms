// test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

using namespace std;

struct tree {
    string name;
    tree* fath;
    int lvl;
    bool iscpp = false;
};

auto iscpp(string str) {
    return str.find(".cpp");
}

int main()
{
    string kek1 = "text.cpp", kek2 = "text.txt";
    cout << iscpp(kek1) << endl;
    cout << iscpp(kek2) << endl;
}


