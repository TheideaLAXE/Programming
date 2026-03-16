#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Node {
    wchar_t ch;
    int freq;
    Node *l = nullptr, *r = nullptr;
};


/*
int main() {
    wifstream inFile("anna.txt");
    inFile.imbue(std::locale("en_US.UTF-8"));
    wstring word;
    map<wchar_t, int> m;
    while (inFile >> word) {
        for (auto e : word) m[e]++;
    }
    map<int, vector<wchar_t>> m2;
    for (auto e : m) {
        m2[e.second].push_back(e.first);
    }
    for (auto val : m2) {
        for (auto e : val.second) wcout << val.first << " " << e << "\n";
    }
    //for (auto e : m) wcout << e.first << " " << e.second << "\n";
    inFile.close();

    return 0;
}*/



int main() {
    ifstream inFile("anna.txt");
    inFile.imbue(std::locale("en_US.UTF-8"));
    string word;
    map<string, int> m;
    vector<char> chars = {',', '.', ';', '!', '?', '\"', '"'}; //“?
    while (inFile >> word) {
        if (!word.empty()) {
            char c = word.back();
            for (auto e : chars) {
                if (e == c) {
                    word.pop_back();
                    break;
                }
            }
            c = word.front();
            for (auto e : chars) {
                if (e == c) {
                    word.erase(0, 1);
                    break;
                }
            }
        }
        if (!word.empty()) m[word]++;
    }
    map<int, vector<string>> m2;
    for (auto e : m) {
        m2[e.second].push_back(e.first);
    }
    for (auto val : m2) {
        cout << val.first;
        for (auto e : val.second) cout << " " << e;
        cout << "\n";
    }

    return 0;
}



/*
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main() {
    wifstream inFile("anna.txt");
    inFile.imbue(std::locale("en_US.UTF-8"));
    wstring word;
    map<char, int> m;
    while (inFile >> word) {
        for (auto e : word) m[e]++;
    }
    for (auto e : m) wcout << e.first << " " << e.second << "\n";
    inFile.close();

    return 0;
}
https://gemini.google.com/app/3178754b6998e03f
*/