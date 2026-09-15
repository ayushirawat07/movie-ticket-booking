// status (available/booked) of one seat for one specific show.
// separate from Seat because A1 can be booked for 6pm but free for 9pm
#ifndef SHOWSEAT_CPP
#define SHOWSEAT_CPP

#include "02_Seat.cpp"

enum class SeatStatus { AVAILABLE, BOOKED };

class ShowSeat {
private:
    Seat* seat;
    SeatStatus status;

public:
    ShowSeat(Seat* seat) {
        this->seat = seat;
        this->status = SeatStatus::AVAILABLE;
    }

    Seat* getSeat() const { return seat; }
    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }
    void book() { status = SeatStatus::BOOKED; }
    void release() { status = SeatStatus::AVAILABLE; }
};

#endif
