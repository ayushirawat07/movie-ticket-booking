// concrete payment methods - adding a new one (e.g. netbanking) just means
// a new class here, nothing else needs to change
#ifndef PAYMENTTYPES_CPP
#define PAYMENTTYPES_CPP

#include <string>
#include <iostream>
#include "09_Payment.cpp"
using namespace std;

class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(string upiId) { this->upiId = upiId; }

    bool pay(double amount) override {
        if (amount <= 0) return false;
        cout << "  [UPI] Rs." << amount << " paid successfully\n";
        return true;
    }
};

class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(string cardNumber) { this->cardNumber = cardNumber; }

    bool pay(double amount) override {
        if (amount <= 0) return false;
        cout << "  [CARD] Rs." << amount << " paid successfully\n";
        return true;
    }
};

class CashPayment : public Payment {
public:
    CashPayment() {}

    bool pay(double amount) override {
        if (amount <= 0) return false;
        cout << "  [CASH] Rs." << amount << " received\n";
        return true;
    }
};

#endif
