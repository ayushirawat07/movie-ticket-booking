// one auditorium, owns its own seats (built in the constructor)
#ifndef SCREEN_CPP
#define SCREEN_CPP

#include <vector>
#include "02_Seat.cpp"
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber) {
        this->screenNumber = screenNumber;
        buildLayout(4, 3, 2);
    }

    Screen(int screenNumber, int silverCount, int goldCount, int platinumCount) {
        this->screenNumber = screenNumber;
        buildLayout(silverCount, goldCount, platinumCount);
    }

    int getScreenNumber() const { return screenNumber; }
    vector<Seat>& getSeats() { return seats; }

private:
    void buildLayout(int silverCount, int goldCount, int platinumCount) {
        char row = 'A';
        for (int i = 1; i <= silverCount; i++)
            seats.push_back(Seat(string(1, row) + to_string(i), SeatType::SILVER));
        row = 'B';
        for (int i = 1; i <= goldCount; i++)
            seats.push_back(Seat(string(1, row) + to_string(i), SeatType::GOLD));
        row = 'C';
        for (int i = 1; i <= platinumCount; i++)
            seats.push_back(Seat(string(1, row) + to_string(i), SeatType::PLATINUM));
    }
};

#endif
