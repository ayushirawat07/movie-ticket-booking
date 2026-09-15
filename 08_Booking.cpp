// stores booking details - id, show, seats, customer, payment, amount, status.
// doesn't calculate price or print tickets, that's not its job
#ifndef BOOKING_CPP
#define BOOKING_CPP

#include <string>
#include <vector>
#include "06_ShowSeat.cpp"
#include "07_Customer.cpp"
#include "05_Show.cpp"
#include "09_Payment.cpp"
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

class Booking {
private:
    static int nextId;
    string bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;
    Payment* payment;
    double totalAmount;
    BookingStatus status;

public:
    Booking(Customer* customer, Show* show, vector<ShowSeat*> seats,
            double totalAmount, Payment* payment) {
        this->bookingId = "BK" + to_string(1000 + nextId++);
        this->customer = customer;
        this->show = show;
        this->seats = seats;
        this->totalAmount = totalAmount;
        this->payment = payment;
        this->status = BookingStatus::PENDING;
    }

    void confirm() { status = BookingStatus::CONFIRMED; }
    void fail() { status = BookingStatus::FAILED; }
    void cancel() { status = BookingStatus::CANCELLED; }

    string getBookingId() const { return bookingId; }
    Show* getShow() const { return show; }
    vector<ShowSeat*> getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    string statusToString() const {
        if (status == BookingStatus::CONFIRMED) return "CONFIRMED";
        if (status == BookingStatus::FAILED) return "FAILED";
        if (status == BookingStatus::CANCELLED) return "CANCELLED";
        return "PENDING";
    }
};

int Booking::nextId = 1;

#endif
