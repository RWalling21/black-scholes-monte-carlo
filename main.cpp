#include <iostream>
#include <cmath>
#include <random>
#include <vector>

// Black Scholes Approach

double normalCDF(double value) {
    return 0.5 * (1.0 + std::erf(value / std::sqrt(2.0)));
}

double blackScholesOptionPricing(double S0, double K, double r, double sigma, double T, bool isCallOption) {
    // if you've never seen the black Scholes model before the below code is going to look like black magic, just know I'm expressing a mathmatical formula to price a financial derivative
    // https://www.investopedia.com/terms/b/blackscholes.asp - Black Scholes Invetopedia
    // https://www.youtube.com/playlist?list=PLeJXxpEi4UA_WEe2LLE5DmhDdqoz_aiNR - Understanding Black Scholes

    double d1 = (std::log(S0/K) + (r + ((std::pow(sigma, 2)) * 0.5)) * T / (sigma * std::sqrt((T))));
    double d2 = d1 - sigma * std::sqrt(T);

    // Call and put options are priced differently
    if (isCallOption) {
        // Black Scholes formula for a Call Option
        return (S0 * normalCDF(d1) - K * std::exp(-r * (T)) * normalCDF(d2));
    } else {
        // Black Scholes formula for a Put Option
        return (K * std::exp(-r * T) * normalCDF(-d2) - S0 * normalCDF(-d1));
    }
}

// Monte Carlo Approach 

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

int main() {
    // Params 
    double S0 = 100.0; // initial price
    double K = 115.0; // strike price
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
