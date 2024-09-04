# Calculating the price of financial derivatives using Black-Scholes and Monte-Carlo simulation. 

The Black-Scholes algorithm, often called the "trillion-dollar equation" caught my attention recently and I wanted to understand why it's such a big deal. Black-Scholes is used to price financial derivatives, which is *extremely* valuable for market makers. Although some famous investors like Warren Buffett and Charlie Munger have historically criticized the Black-Scholes model, it remains a widely used and powerful tool in finance.

So, what does my project do? Simply speaking, it finds how accurate the Black-Scholes equation is compared to a simulation of a hypothetical stock over some time (time to maturity for the derivative). To do this, first the [Black-Scholes equation](https://www.investopedia.com/terms/b/blackscholes.asp) is applied to some hypothetical derivated according to the standard approach, and second, a Monte Carlo simulation is run over the same hypothetical derivative tracing its performance using [geometric brownian motion](https://www.quantstart.com/articles/Geometric-Brownian-Motion/).

Huh? What does that even mean? 

I'm predicting the value of a hypothetical derivative using a relatively straightforward (though somewhat lengthy) formula, and also simulating many different ways the stock could move over time. By comparing the two results, we can see how close our theoretical prediction is to the experimental outcome. (Spoiler: it's surprisingly close!)

# Building the application

g++ compiler
```shell
g++ -std=c++20 -o main main.cpp src/black_scholes.cpp src/monte_carlo.cpp

./main
```
