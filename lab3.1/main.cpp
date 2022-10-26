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

auto brute_force = [](auto f, auto domain, int iterations, double minR, double maxR) {
    auto current_p = domain(minR, maxR);
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = domain(minR, maxR);
    }

    return best_point;
};

auto hill_climbing = [](auto f, auto domain, int max_iterations, double minimal_d, double maximal_d) {
    std::pair<double, double> current_p = domain(minimal_d, maximal_d);

    for (int iteration = 0; iteration < max_iterations; iteration++) {
        std::pair<double, double> new_p;
        std::pair<double, double> neighbour_p = domain(minimal_d / 100, maximal_d / 100);
        new_p.first = current_p.first + neighbour_p.first;
        new_p.second = current_p.second + neighbour_p.second;
        if (f(current_p) > f(new_p)) {
            current_p = new_p;
        }
    }
    return current_p;
};

auto simulated_annealing = [](auto f, auto domain, int max_iterations, double minimal_d, double maximal_d) {

    std::vector<std::pair<double, double>> pairsVector;
    std::uniform_real_distribution<double> uk_dis(0, 1);
    double uk = uk_dis(mt_generator);

    auto best_point = domain(minimal_d, maximal_d);
    pairsVector.push_back(best_point);

    for (int i = 0; i < max_iterations; ++i) {
        auto tk = domain(minimal_d, maximal_d);
        if (f(tk) <= f(best_point)) {
            best_point = tk;
            pairsVector.push_back(best_point);
        } else if (uk < exp(-(std::abs(f(tk) - f(best_point)) / (1 / log(i))))) {
            best_point = tk;
            pairsVector.push_back(best_point);
        }
    }
    return best_point;
};

void printResults(std::vector<std::function<double(std::pair<double, double> pair)>> functions,
                  std::vector<std::string> functionNames,
                  std::vector<std::pair<double, double>> domain_range, int iterations) {


    std::cout << "Brute force" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    for (int i = 0; i < 3; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best_point = brute_force(functions[i], coords_generator, iterations,
                                      domain_range[i].first, domain_range[i].second);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "Best " << functionNames[i] << " x = " << best_point.first << " y = " << best_point.second
                  << " | result: " << functions[i](best_point) << " | duration: "
                  << duration << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    }


    std::cout << std::endl << "Hill Climbing" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    for (int i = 0; i < 3; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best_point = hill_climbing(functions[i], coords_generator, iterations,
                                        domain_range[i].first, domain_range[i].second);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "Best " << functionNames[i] << " x = " << best_point.first << " y = " << best_point.second
                  << " | result: " << functions[i](best_point) << " | duration: "
                  << duration << std::endl;
    }

    std::cout << std::endl << "Simulated Annealing" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------" << std::endl;
    for (int i = 0; i < 3; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto best_point = simulated_annealing(functions[i], coords_generator, iterations,
                                              domain_range[i].first, domain_range[i].second);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "Best " << functionNames[i] << " x = " << best_point.first << " y = " << best_point.second
                  << " | result: " << functions[i](best_point)
                  << " | duration: " << duration
                  << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
    }
}

int main() {
    auto boothFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return pow((x + 2 * y - 7), 2) + pow((2 * x + y - 5), 2);
    };

    auto holderTableFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return -abs(sin(x) * cos(y) * exp(abs(1 - (sqrt(pow(x, 2) + pow(y, 2)))/M_PI)));
    };

    auto treeHumpCamelFunc = [](std::pair<double, double> pair) {
        double x = pair.first, y = pair.second;
        return 2 * pow(x, 2) - 1.05 * pow(x, 4) + pow(x, 6) / 6 + x * y + pow(y, 2);
    };
    std::vector<std::function<double(std::pair<double, double> pair)>> functions = {boothFunc, holderTableFunc,
                                                                                    treeHumpCamelFunc};
    std::vector<std::string> functionNames = {"Booth", "Holder table", "Tree Hump Camel"};
    std::vector<std::pair<double, double>> domain_range = {{-10, 10},
                                                           {-10, 10},
                                                           {-5,  5}};

    printResults(functions, functionNames, domain_range, 100000);
    return 0;
}