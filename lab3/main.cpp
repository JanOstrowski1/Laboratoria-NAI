#include <iostream>
#include <random>
#include <cmath>
#include <functional>
#include <chrono>

std::random_device rd;
std::mt19937 mt_generator(rd());

auto coords_generator = [](double minR, double maxR) {
    std::uniform_real_distribution<> coords(minR, maxR);
    return std::pair<double, double>(coords(mt_generator), coords(mt_generator));
};

auto brute_force = [](auto f, int iterations, double minimal_d, double maximal_d) {
    std::pair<double, double> current_p = coords_generator(minimal_d, maximal_d);
    auto best_point = current_p;
    double precision = (maximal_d - minimal_d) / (iterations);

    while (current_p.first < maximal_d) {
        while (current_p.second < maximal_d) {
            if (f(current_p) < f(best_point)) {
                best_point = current_p;
            }
            current_p.second += precision;
        }
        current_p.first += precision;
        current_p.second = minimal_d + precision;
    }

    return best_point;
};

auto hill_climbing = [](auto f, int iterations, double minimal_d, double maximal_d) {
    std::pair<double, double> current_p = coords_generator(minimal_d, maximal_d);

    for (int iteration = 0; iteration < iterations; iteration++) {
        std::pair<double, double> new_p;
        std::pair<double, double> close_p = coords_generator(-1.0 / 200, 1.0 / 200);
        new_p.first = current_p.first + close_p.first;
        new_p.second = current_p.second + close_p.second;

        if (f(current_p) > f(new_p)) {
            current_p = new_p;
        }
    }
    return current_p;
};

auto simulated_annealing = [](auto f, int max_iterations, double minimal_d, double maximal_d) {

    std::uniform_real_distribution<double> uk_dis(0, 1);


    auto best_point = coords_generator(minimal_d, maximal_d);

    for (int i = 0; i < max_iterations; ++i) {

        double uk = uk_dis(mt_generator);
        std::normal_distribution<> neighbour;
        std::pair<double, double> tk;
        tk.first= best_point.first+ neighbour(mt_generator) * 0.01;
        tk.second= best_point.second+ neighbour(mt_generator) * 0.01;
        if (f(tk) <= f(best_point)) {
            best_point = tk;
        } else if (uk < exp(-(std::abs(f(tk) - f(best_point)) / (1 / log(i))))) {
            best_point = tk;
        }
    }
    return best_point;
};

auto printResults = [](auto algorithm, const std::string &algorithmName,
                       const std::function<double(std::pair<double, double> pair)> &function,
                       const std::string &functionName,
                       std::pair<double, double> domain_range, int iterations) {


    std::cout << algorithmName << std::endl;
    std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    for (int i = 0; i < 3; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best_point = algorithm(function, iterations,
                                    domain_range.first, domain_range.second);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "Best " << functionName << " x = " << best_point.first << " y = " << best_point.second
                  << " | result: " << function(best_point) << " | duration: "
                  << duration << "[ms]" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    }
};

int main() {
    auto boothFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
    };

    auto holderTableFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return -std::abs(sin(x) * cos(y) * exp(std::abs(1 - (sqrt(pow(x, 2) + pow(y, 2))) / M_PI)));
    };

    auto treeHumpCamelFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return 2 * pow(x, 2) - 1.05 * pow(x, 4) + pow(x, 6) / 6 + x * y + pow(y, 2);
    };

    printResults(brute_force, "Brute Force", boothFunc, "Booth", {-10, 10}, 10000);
    printResults(brute_force, "Brute Force", holderTableFunc, "Holder table", {-10, 10}, 10000);
    printResults(brute_force, "Brute Force", treeHumpCamelFunc, "Tree Hump Camel", {-5, 5}, 10000);

    std::cout << std::endl;

    printResults(hill_climbing, "Hill Climbing", boothFunc, "Booth", {-10, 10}, 1000000);
    printResults(hill_climbing, "Hill Climbing", holderTableFunc, "Holder table", {-10, 10}, 1000000);
    printResults(hill_climbing, "Hill Climbing", treeHumpCamelFunc, "Tree Hump Camel", {-5, 5}, 1000000);

    std::cout << std::endl;

    printResults(simulated_annealing, "Simulated Annealing", boothFunc, "Booth", {-10, 10}, 1000000);
    printResults(simulated_annealing, "Simulated Annealing", holderTableFunc, "Holder table", {-10, 10}, 1000000);
    printResults(simulated_annealing, "Simulated Annealing", treeHumpCamelFunc, "Tree Hump Camel", {-5, 5}, 1000000);


    return 0;
}