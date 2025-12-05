#include <algorithm>
#include <iostream>
#include <cmath>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int part1(string input) {
    vector<string> lines;
    stringstream ss(input);
    string line;

    while (getline(ss, line)) {
        lines.push_back(line);
    }
    int valid = 0;

    for (int x = 0; x < lines.size(); ++x) {
        string l = lines[x];
        for (int y = 0; y < l.size(); ++y) {
            if (l[y] == '@') {
                int total = 0;
                cout << "One detected" <<endl ;
                for (int i = max(0, x - 1);
                i <= min<int>(x + 1, lines.size() - 1);
                ++i)
                {
                    for (int o = max(0, y - 1);
                    o <= min<int>(y + 1, l.size() - 1);
                    ++o)
                    {
                        cout << lines[i][o] << endl;
                        if (lines[i][o] == '@') {
                            total++;
                        }
                    }
                }

                // Account for itself
                if (total < 4 + 1) valid++;
            }
        }
    }
    return valid;
}

long long part2(string input) {
    vector<string> lines;
    stringstream ss(input);
    string line;

    while (getline(ss, line)) {
        lines.push_back(line);
    }
    int valid = 0;
    bool changed = true;

    while (changed) {
        changed = false;
        for (int x = 0; x < lines.size(); ++x) {
            string l = lines[x];
            for (int y = 0; y < l.size(); ++y) {
                if (l[y] == '@') {
                    int total = 0;
                    for (int i = max(0, x - 1);
                    i <= min<int>(x + 1, lines.size() - 1);
                    ++i)
                    {
                        for (int o = max(0, y - 1);
                        o <= min<int>(y + 1, l.size() - 1);
                        ++o)
                        {
                            if (lines[i][o] == '@') {
                                total++;
                            }
                        }
                    }

                    // Account for itself
                    if (total < 4 + 1) {
                        valid++;
                        lines[x][y] = '.';
                        changed = true;
                    }
                }
            }
        }

    }
    // for (string line : lines ) {
    //     cout << line << endl;
    // }
    return valid;
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

