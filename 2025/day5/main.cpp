#include <algorithm>
#include <utility>
#include <iostream>
#include <set>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int part1(string input) {
    vector<pair<long long, long long>> fresh;
    
    int split = input.find("\n\n");
    string raw_indexes = input.substr(0, split);
    string raw_foods = input.substr(split + 2);

    istringstream iss_index(raw_indexes);

    for (string index_line; getline(iss_index, index_line);) {
        int dash = index_line.find("-");
        long long start = stoll(index_line.substr(0, dash));
        long long end = stoll(index_line.substr(dash+1));

        fresh.emplace_back(make_pair(start, end));
    }


    istringstream iss_food(raw_foods);

    int total = 0;
    for (string food_line; getline(iss_food, food_line);) {
        long long food = stoll(food_line);

            for (auto indexes : fresh) {
                if (indexes.first <= food && food <= indexes.second) {
                    total++;
                    break;
                }
            }

    }

    return total;
}

long long part2(string input) {
    vector<pair<long long, long long>> fresh;
    
    int split = input.find("\n\n");
    string raw_indexes = input.substr(0, split);
    string raw_foods = input.substr(split + 2);

    istringstream iss_index(raw_indexes);

    for (string index_line; getline(iss_index, index_line);) {
        int dash = index_line.find("-");
        long long start = stoll(index_line.substr(0, dash));
        long long end = stoll(index_line.substr(dash+1));

        if (fresh.empty()) {
            fresh.emplace_back(make_pair(start, end));
            continue;
        }

        bool adjusted = false;
        for (auto& range : fresh) {
            if (range.first <= start && end <= range.second) {
                adjusted = true;
                break;
            }

            else if (start <= range.first && range.second <= end) {
                range.first = start;
                range.second = end;
                adjusted = true;
            }

            else if (range.first <= start && start <= range.second) {
                range.second = max(range.second, end);
                start = range.first;
                end = range.second;
                adjusted = true;
            }
            else if (range.first <= end && end <= range.second) {
                range.first = min(range.first, start);
                start = range.first;
                end = range.second;
                adjusted = true;
            }
        }


        if (!adjusted) {
            fresh.emplace_back(make_pair(start, end));
        }
    }

    long long total = 0;
    for (auto range: fresh) {
        total += (range.second - range.first );
        cout <<range.first <<  range.second << endl;
    }
    
    return total;
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

