#include <iostream>
#include <cmath>
#include <ostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

long long part1(string input) {

    long long total = 0; 

    stringstream ss(input);

    while (ss.good()) {
        string substr1;
        getline(ss, substr1, ',');

        long pos[2];
        stringstream ss_dash(substr1);

        for (int i = 0; i < 2; i++) {
            string temp;
            getline(ss_dash, temp, '-');
            pos[i] = stoll(temp);
        }

        // Really really inefficient solution
        // for (int i = pos[0]; i <= pos[1]; i++) {
        //     string num = to_string(i);
        //
        //     if (num.length() % 2 != 0) continue;
        //
        //     string part1 = num.substr(0, num.length() / 2);
        //     string part2 = num.substr(num.length() / 2, num.length());
        //
        //     if (part1 == part2) {
        //         total += i;
        //     }
        // }
        //
        // Slightly less inefficient solution but still bad
        for (int len = 2; len <= 14; len+=2) {
            int half_len = len / 2;

            long min = (half_len == 1) ? 1 : pow(10, half_len - 1);
            long max = pow(10, half_len) - 1;

            for (long i = min; i <= max; i++) {
                long num = (i * pow(10, half_len)) + i;
                if (num >= pos[0] && num <= pos[1]) {
                    total += num;
                }

            }
        }
    }

    return total;
}

long long part2(string input) {

    long long total = 0; 

    stringstream ss(input);

    while (ss.good()) {
        string substr1;
        getline(ss, substr1, ',');

        long pos[2];
        stringstream ss_dash(substr1);

        for (int i = 0; i < 2; i++) {
            string temp;
            getline(ss_dash, temp, '-');
            pos[i] = stoll(temp);
        }

        for (long long x = pos[0]; x <= pos[1]; x++) {
            string num = to_string(x);

            bool found = false;
            int len = num.size();

            for (int i = 1; i <= len / 2; i++) {
                // Wont fit right
                if (len % i != 0)
                    continue;

                string pattern = num.substr(0, i);

                string repeated;

                for (int k = 0; k < len / i; k++)
                    repeated += pattern;

                if (repeated == num) {
                    total += x;
                    break;
                }
            }
        }
    }

    return total;
}

int main() {
    string input;
    ifstream input_file("input.txt");

    while (getline(input_file, input)) {
        cout << part2(input) << endl;
    }

    return 0;
}

