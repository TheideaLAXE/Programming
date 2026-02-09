#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    float x, y, z;
    bool operator<(const Point& o) const { return this->x<o.x; }
};

float CalcDist(const Point& a, const Point& b) {
    return sqrtf((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}

void Funk(const vector<Point>& p, float& distance) {
    if (p.size()<4) { //BF
        float D = 1e9;
        for (auto i{0u}; i<p.size(); i++) {
            for (auto j=i+1; j<p.size(); j++) {
                D=min(D, CalcDist(p[i], p[j]));
            }
        }
        distance = min(distance, D);
    }
    else {
        vector<Point> p1, p2;
        for (auto i{0u}; i<p.size()/2; i++) p1.push_back(p[i]);
        for (auto i{p.size()/2}; i<p.size(); i++) p2.push_back(p[i]);

        //vector<Point> p1(p.begin(), p.begin() + p.size()/2);
        //vector<Point> p2(p.begin() + p.size()/2, p.end());

        Funk(p1, distance);
        Funk(p2, distance);

        vector<Point> Brute;
        if (!p1.empty()) {
            for (int i=p1.size()-1; i>=0; i--) {
                if (fabs(p1[i].x-p1.back().x)>=distance) break;
                Brute.push_back(p1[i]);
            }
        }
        for (auto i{0ull}; i<p2.size(); i++) {
            if (fabs(p2[i].x-p2.front().x)>=distance) break;
            Brute.push_back(p2[i]);
        }


        float D = 1e9;
        for (auto i{0u}; i<Brute.size(); i++) {
            for (auto j=i+1; j<Brute.size(); j++) {
                D=min(D, CalcDist(Brute[i], Brute[j]));
            }
        }
        distance = min(distance, D);
    }
}

int main() {
    auto n{0ull};
    cin >> n;
    vector<Point> p;
    for (auto i{0ull}; i<n; i++) {
        Point t{};
        cin >> t.x >> t.y >> t.z;
        p.push_back(t);
    }
    sort(p.begin(), p.end());

    float MinDist=1e9f;
    Funk(p, MinDist);
    cout << MinDist;

    return 0;
}