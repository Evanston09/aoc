#include <cctype>
#include <cmath>
#include <iostream>
#include <ostream>
#include <fstream>
#include <ratio>
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

    string operators = lines[lines.size() - 1];
    lines.erase(lines.end() - 1);

    istringstream iss(operators);
    char op;

    vector<bool> ops;
    while (iss >> op) {
        bool isAdd = op == '+' ? true : false;
        ops.emplace_back(isAdd);
    }

    long long gt = 0;
    for (int i = 0; i < ops.size(); ++i) {
        long long total = ops[i] ? 0 : 1;
        for (auto line : lines) {
            istringstream it(line);
            int num;
            // Get x num in column;
            for (int y = 0; y <= i; ++y) {
                it >> num;
            }

            total = ops[i] ? (total + num) : (total * num);
            cout << total << endl;
        }
        gt += total;
    }

    return gt;
}

long long part2(string input) {
    vector<string> lines;
    istringstream index(input);

    for (string line; getline(index, line);) {
        lines.emplace_back(line);
    }

    string operators = lines[lines.size() - 1];
    lines.erase(lines.end() - 1);

    istringstream iss(operators);
    char op;

    vector<bool> ops;
    while (iss >> op) {
        bool isAdd = op == '+' ? true : false;
        ops.emplace_back(isAdd);
    }

    long long gt = 0;

    int num_found = -1;
    int length = lines[1].length();
    vector<long long> nums;

    for (int i = length - 1; i >= 0; --i) {
        vector<int> digits;

        for (int x = 0; x < lines.size(); ++x) {
            if(isdigit(lines[x].at(i))) {
                digits.emplace_back(lines[x].at(i) - '0');
            }
        }

        if (digits.empty()) {
            bool op = ops.back();
            long long total = op ? 0 : 1;
            
            for (auto n : nums) {
               total = op ? (total + n) : (total * n);
            }

            gt += total;

            nums.clear();
            ops.pop_back();
            continue;
        }

        long long num = 0;
        for (int y = 0; y < digits.size(); ++y) {
            num += digits[y] * pow(10, digits.size() - y - 1);
        }
        nums.emplace_back(num);
    }
    // at the end run again;
    if (!nums.empty()) {
        bool op = ops.back();
        long long total = op ? 0 : 1;

        for (auto n : nums) {
            total = op ? (total + n) : (total * n);
        }

        gt += total;

        nums.clear();
        ops.pop_back();
    }

    return gt;
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

