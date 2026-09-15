// console menu - just reads input and calls into BookingService.
// no business logic should live here

#include <iostream>
#include <vector>
#include <sstream>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "10_PaymentTypes.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"
using namespace std;

vector<string> splitSeats(string input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        while (!token.empty() && token.front() == ' ') token.erase(token.begin());
        while (!token.empty() && token.back() == ' ') token.pop_back();
        if (!token.empty()) result.push_back(token);
    }
    return result;
}

int main() {
    Movie movie1("3 Idiots", "Hindi", 170);
    Movie movie2("Interstellar", "English", 169);
    vector<Movie*> movies = { &movie1, &movie2 };

    Screen screen1(1);
    Screen screen2(2);

    Show show1(&movie1, &screen1, "06:00 PM");
    Show show2(&movie1, &screen2, "09:00 PM");
    Show show3(&movie2, &screen1, "09:30 PM");
    vector<vector<Show*>> showsByMovie = { { &show1, &show2 }, { &show3 } };

    BookingService bookingService;
    vector<Customer> customers;

    cout << "===== MOVIE TICKET BOOKING =====\n";

    bool running = true;
    while (running) {
        cout << "\n1. Movies  2. Book  3. Cancel  4. My tickets   0. Exit\nChoose: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "  Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 0) {
            running = false;

        } else if (choice == 1) {
            cout << "\n";
            for (size_t i = 0; i < movies.size(); i++) {
                cout << "  [" << (i + 1) << "] " << movies[i]->getTitle()
                     << "\t" << movies[i]->getLanguage()
                     << "\t" << movies[i]->getDurationMin() << " min\n";
            }

        } else if (choice == 2) {
            cout << "\n";
            for (size_t i = 0; i < movies.size(); i++)
                cout << "  [" << (i + 1) << "] " << movies[i]->getTitle() << "\n";
            cout << "Choose movie: ";
            int m;
            if (!(cin >> m) || m < 1 || (size_t)m > movies.size()) {
                cout << "  Invalid movie choice.\n";
                cin.clear(); cin.ignore(10000, '\n');
                continue;
            }
            vector<Show*>& shows = showsByMovie[m - 1];
            for (size_t i = 0; i < shows.size(); i++) {
                cout << "  [" << (i + 1) << "] Screen-" << shows[i]->getScreen()->getScreenNumber()
                     << "  " << shows[i]->getStartTime() << "\n";
            }
            cout << "Choose show: ";
            int s;
            if (!(cin >> s) || s < 1 || (size_t)s > shows.size()) {
                cout << "  Invalid show choice.\n";
                cin.clear(); cin.ignore(10000, '\n');
                continue;
            }
            Show* show = shows[s - 1];
            show->printSeatLayout();

            cout << "\nSeats (e.g. A1,B2): ";
            cin.ignore();
            string seatInput;
            getline(cin, seatInput);
            vector<string> seatNumbers = splitSeats(seatInput);
            if (seatNumbers.empty()) {
                cout << "  No seats entered.\n";
                continue;
            }

            vector<ShowSeat*> preview;
            bool allValid = true;
            for (string sn : seatNumbers) {
                ShowSeat* ss = show->findShowSeat(sn);
                if (ss == nullptr) { allValid = false; break; }
                preview.push_back(ss);
                cout << "  " << sn << " " << ss->getSeat()->typeToString()
                     << " Rs." << ss->getSeat()->priceForType() << "\n";
            }
            if (!allValid) {
                cout << "  One or more seat numbers are invalid.\n";
                continue;
            }
            cout << "  TOTAL\t\tRs." << PriceCalculator::calculate(preview) << "\n";

            cout << "\nCustomer name: ";
            string name; getline(cin, name);
            cout << "Phone: ";
            string phone; getline(cin, phone);
            customers.push_back(Customer(name, phone));
            Customer* customer = &customers.back();

            cout << "\nPay by: 1.UPI  2.Card  3.Cash > ";
            int payChoice;
            if (!(cin >> payChoice)) {
                cin.clear(); cin.ignore(10000, '\n');
                cout << "  Invalid payment choice.\n";
                continue;
            }

            Payment* payment = nullptr;
            if (payChoice == 1) payment = new UpiPayment("customer@upi");
            else if (payChoice == 2) payment = new CardPayment("XXXX-XXXX-XXXX-1234");
            else if (payChoice == 3) payment = new CashPayment();
            else { cout << "  Invalid payment method.\n"; continue; }

            Booking* booking = bookingService.bookSeats(customer, show, seatNumbers, payment);
            if (booking != nullptr) TicketPrinter::printTicket(booking);
            delete payment;

        } else if (choice == 3) {
            cout << "Enter Booking ID to cancel: ";
            string id; cin >> id;
            bookingService.cancelBooking(id);

        } else if (choice == 4) {
            for (Booking& b : bookingService.getAllBookings()) {
                cout << "  " << b.getBookingId() << "  "
                     << b.getShow()->getMovie()->getTitle() << "  "
                     << b.statusToString() << "\n";
            }

        } else {
            cout << "  Invalid choice. Please pick from the menu.\n";
        }
    }

    cout << "Thank you for using the booking system!\n";
    return 0;
}
