// one screening = movie + screen + time. builds its own ShowSeats on creation
#ifndef SHOW_CPP
#define SHOW_CPP

#include <string>
#include <vector>
#include <iostream>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"
using namespace std;

class Show {
private:
    static int nextShowId;
    int showId;
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(Movie* movie, Screen* screen, string startTime) {
        this->showId = nextShowId++;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        for (Seat& seat : screen->getSeats())
            showSeats.push_back(ShowSeat(&seat));
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    ShowSeat* findShowSeat(string seatNumber) {
        for (ShowSeat& ss : showSeats)
            if (ss.getSeat()->getSeatNumber() == seatNumber) return &ss;
        return nullptr;
    }

    void printSeatLayout() {
        cout << "\n  SCREEN-" << screen->getScreenNumber() << "  " << startTime
             << "  |  " << movie->getTitle() << endl;
        printRow("SILVER", SeatType::SILVER);
        printRow("GOLD", SeatType::GOLD);
        printRow("PLATINUM", SeatType::PLATINUM);
        cout << "\n  ( [ ] = available   [X] = booked )\n";
    }

private:
    void printRow(string label, SeatType type) {
        cout << "  " << label;
        for (int i = label.length(); i < 10; i++) cout << " ";
        for (ShowSeat& ss : showSeats) {
            if (ss.getSeat()->getType() == type)
                cout << ss.getSeat()->getSeatNumber() << (ss.isAvailable() ? "[ ] " : "[X] ");
        }
        cout << endl;
    }
};

int Show::nextShowId = 1;

#endif
