#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
//20. Реализовать алгоритм нахождения остовного дерева  Прима
//и проиллюстрировать в таблице по шагам этапы его выполнения(10).
// Сахабутдинов Тимур ПС-23
using namespace std;
set<int> visited;
typedef pair<int, int> pairM;
int count;
void printRemainderGraph(vector<vector<pairM>> graph) {
    vector<pairM> discarded;
    vector<int> position;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].size() == 0) continue;
        cout << i;
        for (int j = 0; j < graph[i].size(); j++) {
            if (visited.count(graph[i][j].first) > 0) { 
                position.push_back(i);
                discarded.push_back({graph[i][j].first, graph[i][j].second});
                continue; 
            };
            cout << " соединен с - " << graph[i][j].first << " длина - " << graph[i][j].second << "; ";
        }
        cout << endl;
    }
    if (discarded.size() != 0) {
        cout << "Не берем (уже пройден): " << endl;
        for (int i = 0; i < discarded.size(); i++) {
            cout << position[i] << " соединен с - " << discarded[i].first << " длина - " << discarded[i].second << endl;
        }
    }
    cout << endl;
}

void printGraph(vector<vector<pairM>> graph) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].size() == 0) {
            continue;
        }
        cout << i;
        for (int j = 0; j < graph[i].size(); j++) {
            cout << " соединен с - " << graph[i][j].first << " длина - " << graph[i][j].second << "; ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<pairM>> CreateGraph(ifstream& file, vector<vector<pairM>>& graph, int count) {
    vector<vector<pairM>> emptyGraph;
    string line1;
    graph.resize(count);
    int fathId, childId, widthM;
    bool flag = true;
    while (getline(file, line1)) {
        bool inGraph = false;
        istringstream iss(line1);
        if (!(iss >> fathId >> childId >> widthM) || widthM < 0) {
            cout << "Ошибка формата: в файле не 3 переменные или отрицательная ширина";
            flag = false;
            break;
        }
        for (int i = 0; i < graph[fathId].size(); i++) {
            if (graph[fathId][i].first == childId) inGraph = true;
        }
        if (!inGraph) {
            graph[fathId].push_back({ childId, widthM });
            graph[childId].push_back({ fathId, widthM });
        }
    }
    if (flag) return graph;
    else return emptyGraph;
}

vector<vector<pairM>> logicGraph(vector<vector<pairM>>& oldGraph, int count) {
    vector<vector<pairM>> newGraph, reminderGraph;
    vector<pairM> temp;
    int minWidth = oldGraph[1][0].second;
    int positionFirst = 0, positionSecond = 1;
    newGraph.resize(count);
    reminderGraph.resize(count);
    reminderGraph[1] = oldGraph[1];
    temp.push_back({ oldGraph[1][0].first, minWidth });
    for (int index = 1; index < oldGraph.size(); index++) {
        if (visited.size() != count - 1){
            cout << "Берем минимальное ребро из представленных: " << endl;
            printRemainderGraph(reminderGraph);
        }
        for (int i = 1; i < reminderGraph.size(); i++) { 
            for (int k = 0; k < reminderGraph[i].size(); k++) {
                if (visited.count(reminderGraph[i][k].first) > 0) {
                    continue;
                }
                if (reminderGraph[i][k].second < minWidth) {
                    minWidth = reminderGraph[i][k].second;
                    temp.clear();
                    temp.push_back({ reminderGraph[i][k].first, minWidth });
                    positionFirst = i;
                    positionSecond = k;
                }
            }
        }

        if (temp.size() != 0) {
            newGraph[positionFirst].push_back({ temp[0].first, temp[0].second });
            cout << "Взяли " << positionFirst << " соединен с - " << temp[0].first << " с длиной " << temp[0].second << endl << endl;
            cout << "Остовное дерево теперь такое: " << endl;
            printGraph(newGraph);
            visited.insert(temp[0].first);
            reminderGraph[temp[0].first] = oldGraph[temp[0].first];
            temp.clear();
        }
        minWidth = INT_MAX;

    }

    return newGraph;
}
int main()
{
    setlocale(LC_ALL, "RU");
    //чтение файла
    string file_name, line;
    vector<vector<pairM>> graph, resultgraph, check;
    visited.insert(1);
    cout << "Загрузите ваш файл\n";
    cin >> file_name;
    ifstream file(file_name);
    //получаем количество вершин в count
    getline(file, line);
    int count = stoi(line) + 1;
    //реализуем граф
    check = CreateGraph(file, graph, count);
    if (check.size() == 0) return 0;
    cout << "Представленный граф:" << endl;
    printGraph(graph);
    cout << "-------------------------------------------------------------------------------" << endl;
    resultgraph = logicGraph(graph, count);
    cout << "Итоговый граф" << endl;
    printGraph(resultgraph);
    return 0;
}

