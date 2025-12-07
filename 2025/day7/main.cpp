#include <algorithm>
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

long long part1(string input) {
    vector<string> lines;
    istringstream index(input);

    for (string line; getline(index, line);) {
        lines.emplace_back(line);
    }

    int r = lines[0].length();
    // Get S
    vector<int> check = {r / 2};

    int ans = 0;
    for (int i = 1; i < lines.size(); ++i) {
        cout << "Line" << i << endl;
        vector<int> next_check;
        for (auto c : check) {
            // cout << c << endl;
            if (lines[i].at(c) == '^') {
                next_check.push_back(c - 1);
                next_check.push_back(c + 1);
                ans++;
            } else {
                next_check.push_back(c);
            }
        }
        next_check.erase(unique(next_check.begin(), next_check.end()), next_check.end());
        check = next_check;
        // cout << "ans" << ans << endl;
    }
    return ans;


}
long long part2(string input) {
    vector<string> lines;
    istringstream index(input);

    for (string line; getline(index, line);) {
        lines.emplace_back(line);
    }

    int r = lines[0].length();
    // Get S

    vector<long long> check(r, 0);
    check[r / 2] = 1;

    for (int i = 1; i < lines.size(); ++i) {
        cout << "Line" << i << endl;
        vector<long long> next_check(r, 0);

        for (int c = 0; c < r; c++) {
            if (check[c] == 0) continue;

            if (lines[i].at(c) == '^') {
                next_check[c + 1] += check[c];
                next_check[c - 1] += check[c];
            } else {
                next_check[c] += check[c];
            }
        }
        check = next_check;
    }

    long long ans = 0;
    for (auto count : check) {
        ans += count;
    }
    return ans;
}

int main() {
    string i;
    ifstream input_file("input.txt");

    string input;
    while (getline(input_file, i)) {
        input += i + "\n";
    }

    cout << part2(input) << endl;

    return 0;
}

