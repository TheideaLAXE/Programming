#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Node {
    string word;
    Node * next;
    Node() {
        word = "";
        next=nullptr;
    }
};

int hF_WordLength(const string &s) { //0
    return s.size();
}

int hF_CharSum(const string &s) { //1
    int z=0;
    for (int i=0; i<s.size(); i++) {
        z+=tolower(s[i])-'a'+1; //a=1, b=2...
    }
    return z;
}

int hF_FirstChar(const string &s) { //2
    char a = tolower(s[0]);
    return (a-'a');
}

int hF_FirstTwoChar(const string &s) { //3
    char a = tolower(s[0]);
    char b='b';
    if (s.size()>1) b = tolower(s[1]);
    return (a-'a')*26+(b-'a');
}

void insert(map<int, Node> &m, string &word, const int i = 0) {
    /* i ==
     * 0 - word length
     * 1 - char sum
     * 2 - first char
     * 3 - first two char
    */
    int p=0;
    if (i==0) p = hF_WordLength(word);
    else if (i==1) p = hF_CharSum(word);
    else if (i ==2) p = hF_FirstChar(word);
    else p = hF_FirstTwoChar(word);

    Node *t = &m[p];
    while (t->word != "") {
        if (t->next) t=t->next;
        else {
            t->next = new Node;
        }
    }
    t->word = word;
}

void print(const map<int, Node> &m) {
    for (auto e : m) {
        Node *t = &e.second;
        while (t) {
            cout << t->word << " ";
            t=t->next;
        }
        cout << "\n\n";
    }
}
void print(const map<int, Node> &m, ostream& out) {
    for (auto e : m) {
        Node *t = &e.second;
        while (t) {
            out << t->word << " ";
            t=t->next;
        }
        out << "\n\n";
    }
}

int main(){

    string word;
    map<int, Node> m;
    ifstream file("words.txt");
    while (file>>word) {
        insert(m, word, 2);
    }
    print(m);

    /*
    string s2="output0.txt";
    for (int i=0; i<4; i++) {
        ifstream file("words.txt");
        map<int, Node> m;
        s2[6]='0'+i;
        ofstream out(s2);
        while (file>>word) {
            insert(m, word, i);
        }
        print(m, out);
    }*/


    return 0;
}