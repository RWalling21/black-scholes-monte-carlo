#include <cmath>
#include "black_scholes.hpp"

// Normal Cumulative Distribution Function
double normalCDF(double value) {
    return 0.5 * (1.0 + std::erf(value / std::sqrt(2.0)));
}

// Computes the value of a Call or Put option using the Black-Scholes model
double blackScholesOptionPricing(double S0, double K, double r, double sigma, double T, bool isCallOption) {
    // https://www.investopedia.com/terms/b/blackscholes.asp - Black-Scholes Invetopedia Article
    double d1 = (std::log(S0/K) + (r + ((std::pow(sigma, 2)) * 0.5)) * T / (sigma * std::sqrt((T))));
    double d2 = d1 - sigma * std::sqrt(T);

    // Call and put options are priced differently
    if (isCallOption) {
        // Black-Scholes formula for a Call Option
        return (S0 * normalCDF(d1) - K * std::exp(-r * (T)) * normalCDF(d2));
    } else {
        // Black-Scholes formula for a Put Option
        return (K * std::exp(-r * T) * normalCDF(-d2) - S0 * normalCDF(-d1));
    }
}
