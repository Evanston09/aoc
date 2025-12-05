#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string input;
    ifstream input_file("input.txt");
    int position = 50;
    int zero = 0;

    while (getline(input_file, input)) {
        char dir = input[0];
        int dis = stoi(input.substr(1));

        
        int spins = dis / 100;
        zero += spins;

        dis = dis % 100;

        if (dir == 'R') {
            if (position + dis > 100) {
                zero++;
            }
            position = (position + dis) % 100;
        } else {
            if (abs(position - dis) != dis && position - dis < 0) {
                zero++;
            };
            position = (position - dis) % 100;
            if (position < 0) position += 100;
        }

        if (position == 0) {
            zero++;
        }
    }

    cout << zero << endl;
}
