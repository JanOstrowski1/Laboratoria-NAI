#include <iostream>
#include <vector>
#include <random>

using chromosome_t = std::vector<int>;
using population_t = std::vector<chromosome_t>;
std::random_device rd;
std::mt19937 mt_generator(rd());

std::pair<double, double> decode(chromosome_t chromosome) {
    double x = 0.0;
    double y = 0.0;
    double base_x = 1.0;
    double base_y = 1.0;
    int half_c = chromosome.size() / 2;

    for (int i = 0; i < half_c; i++) {
        if (chromosome[i] == 1){
            x += base_x;
        }
        base_x = base_x * 2;
    }

    for (int i = half_c; i < chromosome.size(); i++) {
        if (chromosome[i] == 1){
            y += base_y;
        }
        base_y = base_y * 2;
    }
    x = x / pow(2.0, (half_c - 4)) - 8;
    y = y / pow(2.0, (half_c - 4)) - 8;

    return {x, y};
}

population_t generate_population(int size) {
    population_t population;
    for (int i = 0; i < size; i++){
        chromosome_t chromosome;
        for (int j = 0; j < 100; j++){
            std::uniform_int_distribution<int> byte(0, 1);
            chromosome.push_back(byte(mt_generator));
        }
        population.push_back(chromosome);
    }
    return population;
}

auto ackley_f = [](std::pair<double, double> pair) {
    double x = pair.first;
    double y = pair.second;
    return -20.0 * exp(-0.2 * sqrt(0.5 * (pow(x, 2) + pow(y, 2)))) -
           exp(0.5 * (cos(2 * M_PI * x) + cos(2 * M_PI * y))) + exp(1) + 20;
};

double fitness_function(chromosome_t &chromosome_t) {
    std::pair<double,double> pair =  decode(chromosome_t);
    return 1.0 / ackley_f(pair);
}

int main() {
    using namespace std;
    population_t population = generate_population(100 + (23820 % 10) * 2);

    for (chromosome_t &chromosome: population) {
        pair<double, double> decoded = decode(chromosome);
        cout << "x: "<< decoded.first << " y: "<<  decoded.second << " | fitness: " << fitness_function(chromosome) << endl;
    }

    return 0;
}