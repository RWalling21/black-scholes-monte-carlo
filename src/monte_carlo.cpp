#include <cmath>
#include <random>
#include "monte_carlo.hpp"

// Generate a normally distributed random variable
double normalRandomVariable() {
    static std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

// Calculate the payoff of a european call option at the current stock price 
double callOptionPayoff(double S, double K) {
    return std::max(S - K, 0.0);
}

// Calculate the payoff of a european put option at the current stock price 
double putOptionPayoff(double S, double K) {
    return std::max(K - S, 0.0);
}

// Monte Carlo Simulation
double monteCarloOptionPricing(double S0, double K, double r, double sigma, double T, int numSimulations, bool isCallOption) {
    double payoffSum = 0.0;

    for (int i = 0; i < numSimulations; i++) {
        // Trace price across random geometric brownian motion
        double ST = S0 * std::exp((r - 0.5 * pow(sigma, 2)) * T + sigma * std::sqrt(T) * normalRandomVariable());

        // Calculate the payoff from the path
        double payoff = isCallOption ? callOptionPayoff(ST, K) : putOptionPayoff(ST, K);
        payoffSum += payoff;
    }

    // Calculate the average payoff over the simulation
    double avgPayoff = payoffSum / static_cast<double>(numSimulations);
    // "Discount" the avg payoff to present value according to the risk-free interest rate
    return std::exp(-r * T) * avgPayoff;
}