#include <iostream>
#include "src/black_scholes.hpp"
#include "src/monte_carlo.hpp"

int main() {
    // Params 
    double S0 = 100.0; // initial price
    double K = 110.0; // strike price
    double r = 0.05; // risk-free interest rate
    double sigma = 0.2; // variance 
    double T = 1.0; // Time to maturity
    int numSimulations = 100000; // monte carlo simulation runs

    // Calculate derivative prices
    double estCallPrice = monteCarloOptionPricing(S0, K, r, sigma, T, numSimulations, true);
    double actCallPrice = blackScholesOptionPricing(S0, K, r, sigma, T, true);
    double estPutPrice = monteCarloOptionPricing(S0, K, r, sigma, T, numSimulations, false);
    double actPutPrice = blackScholesOptionPricing(S0, K, r, sigma, T, false);

    std::cout << "Estimated european Call Option Price: " << estCallPrice << std::endl;
    std::cout << "Actual european Call Option Price: " << actCallPrice << std::endl;

    std::cout << "Estimated european Put Option Price: " << estPutPrice << std::endl;
    std::cout << "Actual european Put Option Price: " << actPutPrice << std::endl;

    return 0;
}
