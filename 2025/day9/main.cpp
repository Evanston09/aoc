#include <algorithm>
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

    vector<pair<int, int>> coordinate;
    istringstream index(input);

    for (string line; getline(index, line);) {
        istringstream ss(line);
        int x, y;
        char comma;

        ss >> x >> comma >> y;
        coordinate.emplace_back(x, y);
    }
    
    
    long long best = -1;

    for (int i = 0; i < coordinate.size(); ++i) {
        for (int j = i + 1; j < coordinate.size(); ++j) {

            long long width  = abs(coordinate[i].first  - coordinate[j].first + 1);
            long long height = abs(coordinate[i].second - coordinate[j].second + 1);
            long long area   = width * height;

            if (area > best) best = area;
        }
    }

    return best;
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

    cout << part2(input) << endl;
    return 0;
}

