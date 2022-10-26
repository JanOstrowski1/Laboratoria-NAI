#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std::chrono;

std::random_device rd;
std::mt19937 mt_generator(rd());

auto coords_generator(double r1, double r2) {
    std::uniform_real_distribution<> coords(r1, r2);
    return std::pair<double, double>(coords(mt_generator), coords(mt_generator));
}
auto random_probe = [](auto f,  int iterations, double r1, double r2) {
    auto current_p = coords_generator(r1, r2);
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        auto stop = high_resolution_clock::now();
        current_p = coords_generator(r1, r2);
    }

    return best_point;
};


int main() {

    auto boothFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
    };

    auto matyasFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return 0.26 * (pow(x, 2) + pow(y, 2) - 0.48 * x * y);
    };

    auto treeHumpCamelFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return 2 * pow(x, 2) - 1.05 * pow(x, 4) + pow(x, 6) / 6 + x * y + pow(y, 2);
    };


//    auto bestBooth = brute_force(boothFunc, coords_generator, 1000000, -10, 10);
//    std::cout << "Best Booth x = " << bestBooth.first << " y = " << bestBooth.second << " | result: "
//              << boothFunc(bestBooth) << std::endl << std::endl;
//
//    auto bestMatyas = brute_force(matyasFunc, coords_generator, 1000000, -10, 10);
//    std::cout << "Best Matyas x = " << bestMatyas.first << " y = " << bestMatyas.second << " | result: "
//              << matyasFunc(bestMatyas) << std::endl << std::endl;
//
//    auto bestTreeHumpCamel = brute_force(treeHumpCamelFunc, coords_generator, 1000000, -10, 10);
//    std::cout << "Best Three-hump camel x = " << bestTreeHumpCamel.first << " y = " << bestTreeHumpCamel.second << " | result: "
//              << treeHumpCamelFunc(bestTreeHumpCamel) << std::endl << std::endl;

    for (int i = 1; i <= 20; i++) {
        auto start = high_resolution_clock::now();
        auto bestBooth = brute_force(boothFunc, 1000000, -10, 10);
        std::cout <<"I : " <<i << " | Best Booth x = " << bestBooth.first << " y = " << bestBooth.second << " | result: "
                  << boothFunc(bestBooth);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "| duration: " << duration.count() << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;

    for (int i = 1; i <= 20; i++) {
        auto start = high_resolution_clock::now();
        auto bestMatyas = brute_force(matyasFunc, 1000000, -10, 10);
        std::cout <<"I : " <<i << " | Best Matyas x = " << bestMatyas.first << " y = " << bestMatyas.second << " | result: "
                  << matyasFunc(bestMatyas);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "| duration: " << duration.count() << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;


    for (int i = 1; i <= 20; i++) {
        auto start = high_resolution_clock::now();
        auto bestTreeHumpCamel = brute_force(treeHumpCamelFunc,  1000000, -5, 5);
        std::cout <<"I : " <<i << " | Best Three-hump camel  x = " << bestTreeHumpCamel.first << " y = " << bestTreeHumpCamel.second
                  << " | result: "
                  << treeHumpCamelFunc(bestTreeHumpCamel);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "| duration: " << duration.count() << std::endl;
    }

    return 0;
}