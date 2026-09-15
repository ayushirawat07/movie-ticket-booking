// runs the booking flow end to end - the orchestrator.
// doesn't price, print, or decide seat status itself, just calls the right class for each
//
// note: ideally this would receive a ready-made Payment object instead of building
// one based on the menu choice (that'd be full DIP), but kept it simple for a
// single console app with no DI setup
#ifndef BOOKINGSERVICE_CPP
#define BOOKINGSERVICE_CPP

#include <vector>
#include <deque>
#include <string>
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "11_PriceCalculator.cpp"
using namespace std;

class BookingService {
private:
    // deque instead of vector - growing it never invalidates pointers to
    // existing Bookings, so a Booking* handed back to the caller stays valid
    deque<Booking> allBookings;

public:
    Booking* bookSeats(Customer* customer, Show* show, vector<string> seatNumbers, Payment* payment) {
        vector<ShowSeat*> selected;

        for (string seatNo : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(seatNo);
            if (ss == nullptr) {
                cout << "  Invalid seat number: " << seatNo << ". Booking cancelled.\n";
                return nullptr;
            }
            if (!ss->isAvailable()) {
                cout << "  Seat " << seatNo << " is already booked. Booking cancelled.\n";
                return nullptr;
            }
            selected.push_back(ss);
        }

        double total = PriceCalculator::calculate(selected);

        bool paymentOk = payment->pay(total);
        if (!paymentOk) {
            cout << "  Payment failed. Seats remain AVAILABLE. Booking NOT confirmed.\n";
            return nullptr;
        }

        for (ShowSeat* ss : selected) ss->book();

        allBookings.push_back(Booking(customer, show, selected, total, payment));
        Booking* newBooking = &allBookings.back();
        newBooking->confirm();
        return newBooking;
    }

    bool cancelBooking(string bookingId) {
        for (Booking& b : allBookings) {
            if (b.getBookingId() == bookingId) {
                if (b.getStatus() == BookingStatus::CANCELLED) {
                    cout << "  Booking already cancelled.\n";
                    return false;
                }
                for (ShowSeat* ss : b.getSeats()) ss->release();
                b.cancel();
                cout << "  Booking " << bookingId << " cancelled. Seats released.\n";
                return true;
            }
        }
        cout << "  Booking ID not found.\n";
        return false;
    }

    deque<Booking>& getAllBookings() { return allBookings; }
};

#endif
