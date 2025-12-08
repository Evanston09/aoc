#include <algorithm>
#include <iostream>
#include <ostream>
#include <tuple>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

long long part1(string input) {
    vector<string> raw_boxes;
    istringstream index(input);
    vector<tuple<int, int, int>> boxes;
    vector<tuple<long long, int, int>> distances;

    for (string line; getline(index, line);) {
        raw_boxes.emplace_back(line);
    }

    
    for (auto raw_box : raw_boxes) {
        istringstream comma(raw_box);

        string chunk;
        int x, y, z;

        getline(comma, chunk, ',');
        x = stoi(chunk);

        getline(comma, chunk, ',');
        y = stoi(chunk);

        getline(comma, chunk, ',');
        z = stoi(chunk);


        boxes.push_back(make_tuple(x, y, z));
    }

    for (int x = 0; x < boxes.size(); ++x) {
        for (int y = x + 1; y < boxes.size(); ++y) {
            tuple<int, int, int> source = boxes[x];
            tuple<int, int, int> dest = boxes[y];

            long long dx = get<0>(dest) - get<0>(source);
            long long dy = get<1>(dest) - get<1>(source);
            long long dz = get<2>(dest) - get<2>(source);

            long long dist = dx*dx + dy*dy + dz*dz;

            distances.emplace_back(make_tuple(dist, x, y));
        }
    }

    sort(distances.begin(), distances.end(),
     [](const auto &a, const auto &b) {
         return get<0>(a) < get<0>(b);
     });

    // Assume everyone by themesles
    vector<vector<tuple<int, int, int>>> connected;
    for (const auto& box : boxes) {
        connected.emplace_back(vector<tuple<int,int,int>>{box});
    }

    // Starting connection
    int num_connections = 1000;
    for (int n = 0; n < num_connections; ++n) {
        bool found = false;

        tuple<int, int, int> src = boxes[get<1>(distances[n])];
        tuple<int, int, int> dest = boxes[get<2>(distances[n])];

        int src_group = -1;
        int dest_group = -1;


        for (size_t i = 0; i < connected.size(); ++i) {
            for (size_t j = 0; j < connected[i].size(); ++j) {
                if (connected[i][j] == src) {
                    src_group = i;
                }
                if (connected[i][j] == dest) {
                    dest_group = i;
                }
            }

        }
        
        if (src_group != dest_group && src_group != -1 && dest_group != -1) {
            // Make sure indexes dont get fucked
            int lower = min(src_group, dest_group);
            int higher = max(src_group, dest_group);

            for (const auto& box : connected[higher]) {
                connected[lower].push_back(box);
            }
            connected.erase(connected.begin() + higher);
        }
    }

    sort(connected.begin(), connected.end(), 
    [](const auto& a, const auto& b) { 
        return a.size() > b.size(); 
    });

    int ans = 1;
    for (int i = 0; i < 3; ++i) {
        ans *= connected[i].size();
    }

    return ans;
}

long long part2(string input) {
    vector<string> raw_boxes;
    istringstream index(input);
    vector<tuple<int, int, int>> boxes;
    vector<tuple<long long, int, int>> distances;

    for (string line; getline(index, line);) {
        raw_boxes.emplace_back(line);
    }

    
    for (auto raw_box : raw_boxes) {
        istringstream comma(raw_box);

        string chunk;
        int x, y, z;

        getline(comma, chunk, ',');
        x = stoi(chunk);

        getline(comma, chunk, ',');
        y = stoi(chunk);

        getline(comma, chunk, ',');
        z = stoi(chunk);


        boxes.push_back(make_tuple(x, y, z));
    }

    for (int x = 0; x < boxes.size(); ++x) {
        for (int y = x + 1; y < boxes.size(); ++y) {
            tuple<int, int, int> source = boxes[x];
            tuple<int, int, int> dest = boxes[y];

            long long dx = get<0>(dest) - get<0>(source);
            long long dy = get<1>(dest) - get<1>(source);
            long long dz = get<2>(dest) - get<2>(source);

            long long dist = dx*dx + dy*dy + dz*dz;

            distances.emplace_back(make_tuple(dist, x, y));
        }
    }

    sort(distances.begin(), distances.end(),
     [](const auto &a, const auto &b) {
         return get<0>(a) < get<0>(b);
     });


    // Assume everyone by themesles
    vector<vector<tuple<int, int, int>>> connected;
    for (const auto& box : boxes) {
        connected.emplace_back(vector<tuple<int,int,int>>{box});
    }

    // Starting connection
    int n = 0;
    tuple<int, int, int> src;
    tuple<int, int, int> dest;
    while (connected[0].size() != boxes.size()) {
        bool found = false;

        src = boxes[get<1>(distances[n])];
        dest = boxes[get<2>(distances[n])];

        int src_group = -1;
        int dest_group = -1;


        for (size_t i = 0; i < connected.size(); ++i) {
            for (size_t j = 0; j < connected[i].size(); ++j) {
                if (connected[i][j] == src) {
                    src_group = i;
                }
                if (connected[i][j] == dest) {
                    dest_group = i;
                }
            }

        }
        
        if (src_group != dest_group && src_group != -1 && dest_group != -1) {
            // Make sure indexes dont get fucked
            int lower = min(src_group, dest_group);
            int higher = max(src_group, dest_group);

            for (const auto& box : connected[higher]) {
                connected[lower].push_back(box);
            }
            connected.erase(connected.begin() + higher);
        }

        ++n;
    }

    return get<0>(src) * get<0>(dest);
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

