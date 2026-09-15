// formats + prints a ticket, nothing else
#ifndef TICKETPRINTER_CPP
#define TICKETPRINTER_CPP

#include <iostream>
#include "08_Booking.cpp"
using namespace std;

class TicketPrinter {
public:
    static void printTicket(Booking* booking) {
        cout << "\n  ================ TICKET ================\n";
        cout << "   Booking ID : " << booking->getBookingId() << endl;
        cout << "   Movie      : " << booking->getShow()->getMovie()->getTitle() << endl;
        cout << "   Screen     : Screen-" << booking->getShow()->getScreen()->getScreenNumber()
             << "   " << booking->getShow()->getStartTime() << endl;
        cout << "   Seats      : ";
        vector<ShowSeat*> seats = booking->getSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i]->getSeat()->getSeatNumber();
            if (i != seats.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "   Amount     : Rs." << booking->getTotalAmount()
             << "     Status: " << booking->statusToString() << endl;
        cout << "  =========================================\n";
    }
};

#endif
