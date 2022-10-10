#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void lab1(function<double(vector<double>)> operation, vector<double> numbers) {
    cout << operation(numbers) << endl;
}

int main(int argc, char **argv) {
    vector<double> argNumbers;
    map<string, map<string, function<double(vector<double>)>>> operations;

    operations["lab1"]["sin"] = [](vector<double> numbers) { return sin(numbers[0]); };
    operations["lab1"]["mod"] = [](vector<double> numbers) { return fmod(numbers[0], numbers[1]); };
    operations["lab1"]["add"] = [](vector<double> numbers) { return numbers[0] + numbers[1]; };

    try {
        char* funcName = argv[1];
        char* operationName = argv[2];
        for (int i = 3; i < argc; i++) {
            argNumbers.push_back(stod(argv[i]));
        }

        lab1(operations.at(funcName).at(operationName), argNumbers);
    } catch (std::out_of_range aor) {
        return 1;
    } catch (std::logic_error e) {
        return 1;
    }
    return 0;
}