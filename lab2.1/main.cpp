#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std::chrono;

std::random_device rd;
std::mt19937 mt_generator(rd());

auto brute_force = [](auto f, auto domain, int iterations, double r1, double r2) {
    auto current_p = domain(r1, r2);
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = domain(r1, r2);
    }

    return best_point;
};

auto coords_generator(double r1, double r2) {
    std::uniform_real_distribution<> coords(r1, r2);
    return std::pair<double, double>(coords(mt_generator), coords(mt_generator));
}

int main() {
    auto start = high_resolution_clock::now();

    auto bealeFunc = [](std::pair<double, double> pair) {
        return pow(1.5 - pair.first + pair.first * pair.second, 2) +
               pow(2.25 - pair.first + pair.first * pow(pair.second, 2), 2) +
               pow(2.625 - pair.first + pair.first * pow(pair.second, 3), 2);
    };

    auto boothFunc = [](std::pair<double, double> pair) {
        return pow((pair.first + 2 * pair.second - 7), 2) +
               pow((2 * pair.first + pair.second - 5), 2);
    };

    auto matyasFunc = [](std::pair<double, double> pair) {
        return 0.26 * (pow(pair.first, 2) +
                       pow(pair.second, 2) - 0.48 * pair.first * pair.second);
    };

    auto bestBeale = brute_force(bealeFunc, coords_generator, 1000000, -4.5, 4.5);
    std::cout << "Best Beale x = " << bestBeale.first << " y = " << bestBeale.second<< " | result: " << boothFunc(bestBeale)<< std::endl << std::endl;

    auto bestBooth = brute_force(boothFunc, coords_generator, 1000000, -10, 10);
    std::cout << "Best Booth x = " << bestBooth.first << " y = " << bestBooth.second<< " | result: " << boothFunc(bestBooth)<< std::endl << std::endl;

    auto bestMatyas = brute_force(matyasFunc, coords_generator, 1000000, -10, 10);
    std::cout << "Best Matyas x = " << bestMatyas.first << " y = " << bestMatyas.second<< " | result: " << matyasFunc(bestMatyas)<< std::endl << std::endl;

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << duration.count() << std::endl;

    return 0;
}