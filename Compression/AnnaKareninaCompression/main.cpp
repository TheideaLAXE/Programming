#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <filesystem>
using namespace std;

struct Node {
    string symbol;
    int freq;
    Node *left, *right;
    bool isLeaf;

    Node(string s, int f, bool leaf = true) : symbol(s), freq(f), left(nullptr), right(nullptr), isLeaf(leaf) {}
};

struct compare {
    bool operator()(Node* l, Node* r) { return l->freq > r->freq; }
};

map<string, string> encoderMap;
Node* huffmanRoot = nullptr;
vector<string> dictionary;

void buildMap(Node* root, string str) {
    if (!root) return;
    if (root->isLeaf) {
        encoderMap[root->symbol] = str;
        dictionary.push_back(root->symbol);
    }
    buildMap(root->left, str + "0");
    buildMap(root->right, str + "1");
}

void compressFile(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    // Sort dictionary longest-to-shortest so we match "thing" before "th"
    sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b) {
        return a.length() > b.length();
    });

    ofstream out(outputFile, ios::binary);
    unsigned char buffer = 0;
    int bitCount = 0;

    for (size_t i = 0; i < content.length(); ) {
        string matchedToken = "";

        // GREEDY MATCH: Find the longest token in our map that starts at current index
        for (const string& token : dictionary) {
            if (content.compare(i, token.length(), token) == 0) {
                matchedToken = token;
                break;
            }
        }

        // Fallback: If no token matches, treat as a single char (shouldn't happen if all chars are in freq file)
        if (matchedToken == "") matchedToken = string(1, content[i]);

        string code = encoderMap[matchedToken];
        for (char bit : code) {
            buffer = (buffer << 1) | (bit - '0');
            if (++bitCount == 8) {
                out.put(buffer);
                buffer = 0;
                bitCount = 0;
            }
        }
        i += matchedToken.length();
    }

    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        out.put(buffer);
    }
    out.put((unsigned char)bitCount);
    out.close();
}

void decompressFile(string inputFile, string outputFile) {
    ifstream in(inputFile, ios::binary);
    vector<unsigned char> bytes((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();
    if (bytes.size() < 2) return;

    int lastBitsValid = bytes.back();
    bytes.pop_back();

    ofstream out(outputFile, ios::binary);
    Node* curr = huffmanRoot;

    for (size_t i = 0; i < bytes.size(); ++i) {
        int limit = (i == bytes.size() - 1 && lastBitsValid != 0) ? lastBitsValid : 8;

        for (int j = 7; j >= (8 - limit); --j) {
            curr = ((bytes[i] >> j) & 1) ? curr->right : curr->left;

            if (curr->isLeaf) {
                // Now writes the whole string (e.g., "wh") instead of just one char
                out.write(curr->symbol.c_str(), curr->symbol.length());
                curr = huffmanRoot;
            }
        }
    }
    out.close();
}

int main() {
    bool NoCs; //0 if you don't want to change c's into k's, morse code
    priority_queue<Node*, vector<Node*>, compare> minHeap;
    int N;
    cout << "1: with C's and no combinations\n";
    cout << "2: with C's and combinations\n";
    cout << "3: no C's and no combinations\n";
    cout << "4: no  C's and combinations\n";
    ifstream freqFile;
    cin >> N;
    if (N==1) {
        freqFile.open("FreqNN.txt");
        NoCs=0;
    }
    else if (N==2) {
        freqFile.open("FreqCN.txt");
        NoCs=0;
    }
    else if (N==3) {
        freqFile.open("FreqNN.txt");
        NoCs=1;
    }
    else if (N==4) {
        freqFile.open("FreqNC.txt");
        NoCs=1;
    }


    if (!freqFile) {
        return 12;
    }
    string line;
    while (getline(freqFile, line)) {
        if (line.empty()) continue;


        if (NoCs) {
            for (auto &e : line) {
                if (e=='c') e='k';
                else if (e=='C') e='K';
            }
        }


        size_t firstSpace = line.find(' ');
        if (firstSpace == string::npos) continue;

        int f = stoi(line.substr(0, firstSpace));
        string s = line.substr(firstSpace + 1);

        string token;
        if (s == "\\n") token = "\n";
        else if (s == "\\s") token = " ";
        else token = s; // Keeps "wh" as "wh"

        minHeap.push(new Node(token, f));
    }
    freqFile.close();

    if (minHeap.empty()) return 1;

    while (minHeap.size() > 1) {
        Node *l = minHeap.top(); minHeap.pop();
        Node *r = minHeap.top(); minHeap.pop();
        Node *parent = new Node("", l->freq + r->freq, false);
        parent->left = l;
        parent->right = r;
        minHeap.push(parent);
    }

    huffmanRoot = minHeap.top();
    buildMap(huffmanRoot, "");
    cout << "compressing" << "\n";
    compressFile("anna.txt", "codeanna.bin");
    cout << "compressed" << "\n";
    decompressFile("codeanna.bin", "decodedanna.txt");
    cout << "decompressed" << "\n";
    cout << filesystem::file_size("codeanna.bin") << " bites";

    return 0;
}

//1324519
//1296978
//1096293 1098953
//1096293 1096293
//1064452 1056288
//1056051

//1057972 1057952
//1051529
//1051361
//1050760 1049046
//1045529
//1037481 1033499
//1033499 1026436

//1026436 1024334
//1020011 1018432
//1017845 1016127
//1012176 1008428
//1007476 1004963 1035879
//1006299 1004944 1004262
//1003244 1002902

//1003244 1002902
//1002507 1001237

// 999784 LETS GOOO
// 998304 1064430
//1029484
//1001229 997715


//1064430 no combs with C's
//1036742 with combs and C's
//1064430 only char, no C's
//997715 with combinations, no C's