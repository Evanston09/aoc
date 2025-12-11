#include <algorithm>
#include "dbg.h"
#include <climits>
#include <iterator>
#include <map>
#include <set>
#include <iostream>
#include <ostream>
#include <tuple>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
using namespace std;

long long part1(string input) {
    istringstream index(input);
    long long total = 0;

    for (string line; getline(index, line);) {
        int bracket_start = line.find('[');
        int bracket_end = line.find(']');
        string pattern = line.substr(bracket_start + 1, bracket_end - bracket_start - 1);

        int target = 0;
        for (int i = 0; i < pattern.length(); i++) {
            if (pattern[i] == '#') {
                target |= (1 << i);
            }
        }

        vector<int> all_buttons;
        int pos = bracket_end + 1;
        while (pos < line.length()) {
            int paren_start = line.find('(', pos);
            if (paren_start == string::npos) break;

            int paren_end = line.find(')', paren_start);
            string button_str = line.substr(paren_start + 1, paren_end - paren_start - 1);

            int button_mask = 0;
            istringstream button_iss(button_str);
            for (string num; getline(button_iss, num, ',');) {
                int light = stoi(num);
                button_mask |= (1 << light);
            }
            all_buttons.push_back(button_mask);

            pos = paren_end + 1;
        }

        long long minPresses = LLONG_MAX;
        for (int i = 0; i < 1 << all_buttons.size(); i++) {
            int result = 0;
            for (int j = 0; j < all_buttons.size(); j++) {
                if (i & (1 << j)) {
                    result ^= all_buttons[j];
                }
            }
            if (result == target) {
                minPresses = min(minPresses, (long long)__builtin_popcount(i));
            }
        }

        if (minPresses != LLONG_MAX)
            total += minPresses;
    }

    return total;
}

long long part2(string input) {
    vector<pair<int, int>> coordinate;
    set<pair<int, int>> edges;
    istringstream index(input);


    for (string line; getline(index, line);) {
        istringstream ss(line);
        int x, y;
        char comma;

        ss >> x >> comma >> y;
        coordinate.emplace_back(x, y);
    }

    int n = coordinate.size();
    vector<long long> xs, ys;
    for (auto& [x, y] : coordinate) {
        xs.push_back(x);
        ys.push_back(y);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    map<long long, int> xmap;
    map<long long, int> ymap;

    for (int i = 0; i < xs.size(); i++) xmap[xs[i]] = i;
    for (int i = 0; i < ys.size(); i++) ymap[ys[i]] = i;

    vector<vector<bool>> valid(ys.size(), vector<bool>(xs.size(), false));

    // Define boundary
    for (int i = 0; i < n; i++){
        int cx1 = xmap[coordinate[i].first];
        int cy1 = ymap[coordinate[i].second];
        int cx2 = xmap[coordinate[(i + 1) % n].first];
        int cy2 = ymap[coordinate[(i + 1) % n].second];

        // Vertical edge
        if (cx1 == cx2) {
            for (int cy = min(cy1, cy2); cy <= max(cy1, cy2); cy++)
                valid[cy][cx1] = true;
        }
        else {
            for (int cx = min(cx1, cx2); cx <= max(cx1, cx2); cx++)
                valid[cy1][cx] = true;
        }
    }

    // Fill polygon
    for (int cx = 0; cx < xs.size(); cx++) {
        for (int cy = 0; cy < ys.size(); cy++) {
            if (valid[cy][cx]) continue;

            int crossings = 0;
            for (int i = 0; i < n; i++) {
                int cx1 = xmap[coordinate[i].first];
                int cy1 = ymap[coordinate[i].second];
                int cx2 = xmap[coordinate[(i+1) % n].first];
                int cy2 = ymap[coordinate[(i+1) % n].second];

                // Check if vertical
                if (cx1 != cx2) continue;

                int edge_cx = cx1;
                int minCy = min(cy1, cy2);
                int maxCy = max(cy1, cy2);

                if (edge_cx > cx && cy >= minCy && cy < maxCy) {
                    crossings++;
                }
            }

            // If odd number of crossings https://www.youtube.com/watch?v=RSXM9bgqxJM
            if (crossings % 2 == 1) {
                valid[cy][cx] = true;
            }
        }
    }

    long long best = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int cx1 = xmap[coordinate[i].first];
            int cy1 = ymap[coordinate[i].second];

            int cx2 = xmap[coordinate[j].first];
            int cy2 = ymap[coordinate[j].second];

            int cxMin = min(cx1, cx2);
            int cxMax = max(cx1, cx2);

            int cyMin = min(cy1, cy2);
            int cyMax = max(cy1, cy2);

            bool ok = true;
            for (int cy = cyMin; cy <= cyMax; ++cy) {
                for (int cx = cxMin; cx <= cxMax; ++cx) {
                    if (!valid[cy][cx]) {
                        ok = false;
                        break;
                    }
                }

                if (!ok) {
                    break;
                }
            }

            if (ok) {
                long long w = abs(coordinate[i].first - coordinate[j].first) + 1;
                long long h = abs(coordinate[i].second - coordinate[j].second) + 1;
                best = max(best, w * h);
            }
        }
    }

    return best;
}
int main() {
    string i;
    ifstream input_file("input.txt");

    string input;
    while (getline(input_file, i)) {
        input += i + "\n";
    }

    cout << part1(input) << endl;
    return 0;
}

