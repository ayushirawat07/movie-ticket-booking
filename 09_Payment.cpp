// abstract payment contract - every payment method implements pay()
#ifndef PAYMENT_CPP
#define PAYMENT_CPP

class Payment {
protected:
    double amount;

public:
    Payment() { amount = 0.0; }
    virtual bool pay(double amount) = 0;
    virtual ~Payment() {}
};

#endif
