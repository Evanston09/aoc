#include <iostream>
#include <cmath>
#include <ostream>
#include <fstream>
#include <string>
using namespace std;

int part1(string input) {
    int max1 = -1;
    int max2;
    for (int y = 0; y < input.length() - 1; ++y) {
        if (input[y] - '0' > max1) {
            max1 = input[y] - '0';
            max2 = -1;
            for (int z = y + 1; z < input.length(); ++z) {
                if (input[z] - '0' > max2) {
                    max2 = input[z] - '0';
                }
            }
        }
    }

    cout << max1 << max2 <<endl;

    return max1 * 10 + max2;
}

long long part2(string input, int num) {
    long long ans = 0;

    int idx = -1;
    for (int i = 0; i < num; ++i) {
        int max = 0;
        for (int y = idx + 1; y < input.length() - (num - i - 1); ++y) {
            if (input[y] - '0' > max) {
                max = input[y] - '0';
                idx = y;
            }
        }
        ans += (max * pow(10, num - i - 1));
    }

    return ans;
}

int main() {
    string input;
    ifstream input_file("input.txt");

    unsigned long long total = 0;
    while (getline(input_file, input)) {
        total += part2(input, 12);
    }

    cout << total <<endl;

    return 0;
}

