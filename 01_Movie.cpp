// stores movie info only - title, language, duration
#ifndef MOVIE_CPP
#define MOVIE_CPP

#include <string>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int durationMin;

public:
    Movie(string title, string language, int durationMin) {
        this->title = title;
        this->language = language;
        this->durationMin = durationMin;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDurationMin() const { return durationMin; }
};

#endif
