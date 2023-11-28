//14. Информация  о  файлах  на  жестких  дисках   компьютера
//записана с помощью дерева.Внешнюю память компьютера увеличили
//путем подключения нового жесткого диска.Решено  перенести  на
//него все папки, в которых содержатся только файлы* .cpp вместе
//с папками до корня дерева.Сформировать и показать  на  экране
//получившееся дерево папок(11). vs 2022 Тимур Сахабутдинов пс-23
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct tree {
    string name;
    vector<tree*> children;
    tree* fath;
    int lvl;
    bool full_check = true;
    bool any_check = false;
};

tree* readtree(string name) {
    ifstream infile(name);
    if (!infile) {
        cout << "fail with open file" << endl;
        return nullptr;
    }

    string line;
    tree* p = nullptr;
    tree* top = nullptr;
    tree* lastbranch = nullptr;
    int level, lastlevel = 0;

    while (getline(infile, line)) {
        level = 0;
        for (int i = 0; line[i] == '.'; i++) {
            level++;
            if (line[i] != '.') {
                break;
            }
        }
        tree* ptr = new tree;
        ptr->name = line.substr(level, line.length());
        ptr->lvl = level;

        if (level == 0) {
            top = ptr;
            lastlevel = 0;
            ptr->fath = nullptr;
            lastbranch = ptr;
        }
        else if (level - lastlevel == 1) {
            lastbranch->children.push_back(ptr);
            ptr->fath = lastbranch;
        }

        else { // level < lastlevel
            p = lastbranch;
            for (int i = 0; i < lastlevel - level; i++) {
                p = p->fath;
            }
            ptr->fath = p->fath;
            p->fath->children.push_back(ptr);
        }
        lastlevel = level;
        lastbranch = ptr;
    }
    return top;
}

auto iscpp(string str) {
    return str.find(".cpp");
}

auto isfolder(string str) {
    return str.find(".");
}

void cleartree(tree* top) {
    if (!top->children.empty()) {
        for (int i = 0; i < top->children.size(); i++) {
            cleartree(top->children[i]);
        }
    }
    
    if (top->fath != nullptr) {
        if (iscpp(top->name) == string::npos && top->children.empty()) top->fath->full_check = false;
        else if (isfolder(top->name) == string::npos && top->children.size() != 0) {
            if (top->full_check == false) {
                if (top->any_check == true) top->fath->any_check = true;
                else top->fath->full_check = false;
                top->fath->full_check = false;
            }
            else top->fath->any_check = true;
        }
        else if (isfolder(top->name) == string::npos && top->children.size() == 0) top->full_check = false;
    }

}

void fullprinttree(tree* top) {
    for (int i = 0; i < top->lvl; i++) {
        cout << ".";
    }
    cout << top->name << " " << top->any_check << top->full_check << endl;
    if (!top->children.empty()) {
        for (int i = 0; i < top->children.size(); i++) {
            fullprinttree(top->children[i]);
        }
    }
    
}

void anyprinttree(tree* top) {
    for (int i = 0; i < top->lvl; i++) {
        cout << ".";
    }
    cout << top->name << endl;
    if (!top->children.empty()) {
        for (int i = 0; i < top->children.size(); i++) {
            tree* child = top->children[i];
            if (isfolder(child->name) == string::npos) {
                if (child->full_check == 1) anyprinttree(child);
                else if (child->any_check == 1) anyprinttree(child);
            }
            else {
                if (child->fath->any_check == 1 and child->fath->full_check == 0) {
                    continue;
                }
                if (child->fath->full_check == 1) {
                    anyprinttree(child);
                }
            }
        }
    }
}

void printtree(tree* top) {
    if (top->full_check == 1) {
        fullprinttree(top);
    }
    else if (top->any_check == 1) {
        anyprinttree(top);
        //fullprinttree(top);
    }
    else {
        cout << "Ничего хорошего\n";
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    string input;
    tree* top;
    while (true) {
        cout << "введи новый файл или exit\n";
        cin >> input;
        if (input == "exit") {
            break;
        }
        else {
            top = readtree(input);
            cleartree(top);
            printtree(top);
        }
    }
    return 0;
}

