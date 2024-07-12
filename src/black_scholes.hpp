#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

// Declarations
double normalCDF(double value);
double blackScholesOptionPricing(double S0, double K, double r, double sigma, double T, bool isCallOption);

#endif