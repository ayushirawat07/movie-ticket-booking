// seats -> total amount. nothing else.
#ifndef PRICECALCULATOR_CPP
#define PRICECALCULATOR_CPP

#include <vector>
#include "06_ShowSeat.cpp"
using namespace std;

class PriceCalculator {
public:
    static double calculate(vector<ShowSeat*> seats) {
        double total = 0.0;
        for (ShowSeat* ss : seats) total += ss->getSeat()->priceForType();
        return total;
    }
};

#endif
