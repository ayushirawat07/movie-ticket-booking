// physical seat - number + type. booking status doesn't belong here since
// the same seat can be free/booked differently per show (see ShowSeat)
#ifndef SEAT_CPP
#define SEAT_CPP

#include <string>
using namespace std;

const double SILVER_PRICE = 150.0;
const double GOLD_PRICE = 250.0;
const double PLATINUM_PRICE = 400.0;

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    string seatNumber;
    SeatType type;

public:
    Seat(string seatNumber, SeatType type) {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    string getSeatNumber() const { return seatNumber; }
    SeatType getType() const { return type; }

    string typeToString() const {
        if (type == SeatType::SILVER) return "SILVER";
        if (type == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }

    double priceForType() const {
        if (type == SeatType::SILVER) return SILVER_PRICE;
        if (type == SeatType::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }
};

#endif
