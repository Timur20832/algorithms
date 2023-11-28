#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <set>
#include <algorithm>
using namespace std;

set<int> visited;

void mergeArr(vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);
    int i = 0;   
    int j = 0;
    int k = left;

    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[middle + 1 + j];
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        }
        else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    // Копирование оставшихся элементов leftArr[]
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    // Копирование оставшихся элементов rightArr[]
    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

void mergeSortArr(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Находим средний элемент
        int middle = left + (right - left) / 2;
        mergeSortArr(arr, left, middle);
        mergeSortArr(arr, middle + 1, right);
        mergeArr(arr, left, middle, right);
    }
}

void PrintToFile(unique_ptr<ofstream>& file, vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        *file << arr[i] << " ";
    }
}

vector<unique_ptr<ofstream>> CreateFile() {
    vector<unique_ptr<ofstream>> tapeFiles;
    tapeFiles.emplace_back(make_unique<ofstream>("tape1.txt", ofstream::out));
    tapeFiles.emplace_back(make_unique<ofstream>("tape2.txt", ofstream::out));
    tapeFiles.emplace_back(make_unique<ofstream>("tape3.txt", ofstream::out));
    tapeFiles.emplace_back(make_unique<ofstream>("tape4.txt", ofstream::out));
    return tapeFiles;
}

vector<unique_ptr<ofstream>> FileSplitter(string fileName) {
    vector<unique_ptr<ofstream>> Files = CreateFile();
    vector<int> forTape1, forTape2, forTape3, forTape4;
    ifstream file(fileName);
    int num, count = 1;
    while (file >> num) {
        if (count == 5) count = 1;
        if (visited.count(num) == 0) {
            switch (count)
            {
            case 1:
                forTape1.emplace_back(num);
                break;
            case 2:
                forTape2.emplace_back(num);
                break;
            case 3:
                forTape3.emplace_back(num);
                break;
            case 4:
                forTape4.emplace_back(num);
                break;
            default:
                break;
            }
            count++;
            visited.insert(num);
        }
    }
    mergeSortArr(forTape1, 0, forTape1.size() - 1);
    mergeSortArr(forTape2, 0, forTape2.size() - 1);
    mergeSortArr(forTape3, 0, forTape3.size() - 1);
    mergeSortArr(forTape4, 0, forTape4.size() - 1);
    PrintToFile(Files[0], forTape1);
    PrintToFile(Files[1], forTape2);
    PrintToFile(Files[2], forTape3);
    PrintToFile(Files[3], forTape4);
    file.close();
    return Files;
}

void MergeFile(const vector<unique_ptr<ofstream>>& Files, string outputName) {
    vector<unique_ptr<ifstream>> ReadFiles;
    for (int i = 0; i < Files.size(); i++) {
        Files[i]->close();
        unique_ptr<ifstream> inputFileStream = make_unique<ifstream>("tape" + to_string(i + 1) + ".txt");
        ReadFiles.push_back(move(inputFileStream));
    }
    int num1, num2, num3, num4, checking = 0, indexMinValue = 0;
    ofstream outputFile(outputName);
    while (checking != 3) {
        if (indexMinValue == 0) {
            if (*ReadFiles[0] >> num1);
            else {
                checking++;
                ReadFiles[0]->close();
                num1 = INT_MAX;
            }
            if (*ReadFiles[1] >> num2);
            else {
                checking++;
                ReadFiles[1]->close();
                num2 = INT_MAX;
            }
            if (*ReadFiles[2] >> num3);
            else {
                checking++;
                ReadFiles[2]->close();
                num3 = INT_MAX;
            }
            if (*ReadFiles[3] >> num4);
            else {
                checking++;
                ReadFiles[3]->close();
                num4 = INT_MAX;
            }
        }
        if (ReadFiles[0]->is_open() && indexMinValue == 1) {
            if (*ReadFiles[0] >> num1);
            else {
                checking++;
                ReadFiles[0]->close();
                num1 = INT_MAX;
            }
        }
        if (ReadFiles[1]->is_open() && indexMinValue == 2) {
            if (*ReadFiles[1] >> num2);
            else {
                checking++;
                ReadFiles[1]->close();
                num2 = INT_MAX;
            }
        }
        if (ReadFiles[2]->is_open() && indexMinValue == 3) {
            if (*ReadFiles[2] >> num3);
            else {
                checking++;
                ReadFiles[2]->close();
                num3 = INT_MAX;
            }
        }
        if (ReadFiles[3]->is_open() && indexMinValue == 4) {
            if (*ReadFiles[3] >> num4);
            else {
                checking++;
                ReadFiles[3]->close();
                num4 = INT_MAX;
            }
        }
        
        int minValue = min({ num1, num2, num3, num4 });
        if (minValue == num1) indexMinValue = 1;
        if (minValue == num2) indexMinValue = 2;
        if (minValue == num3) indexMinValue = 3;
        if (minValue == num4) indexMinValue = 4;
        outputFile << minValue << " ";

    }

}

void SplitFile(string fileNameInput, string fileNameOutput) {
    vector<unique_ptr<ofstream>> tapeFiles;
    tapeFiles = CreateFile();
    tapeFiles = FileSplitter(fileNameInput);
    MergeFile(tapeFiles, fileNameOutput);
}

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Инструкция программы:\n 1) Загрузите ваш файл для сортировки\n 2)Напишите exit для выхода из программы\n";
    const string output = "output.txt";
    string line;
    while (true) {
        cout << "Введите имя файла или exit\n";
        cin >> line;
        if (line == "exit") {
            break;
        }
        SplitFile(line, output);
    }
    return 0;
}