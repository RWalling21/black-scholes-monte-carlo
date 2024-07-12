#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

// Declarations
double normalRandomVariable();
double callOptionPayoff(double S, double K);
double putOptionPayoff(double S, double K);
double monteCarloOptionPricing(double S0, double K, double r, double sigma, double T, int numSimulations, bool isCallOption);

#endif