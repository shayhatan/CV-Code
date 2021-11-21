//
// Created by USER on 31/10/2021.
//

#include "examDetails.h"
#include <cmath>

#define DAYS_IN_MONTH 30
#define NUM_OF_MONTH 12
#define HALF_AN_HOUR 0.5
#define TEN_POWER_MINUS_SIX 0.000001

using std::cout;
using std::endl;
using std::string;
using std::modf;
using std::abs;


void ExamDetails::dateValid(int day, int month) {
    if (!(day >= 1 && day <= DAYS_IN_MONTH) || !(month >= 1 && month <= NUM_OF_MONTH)) {
        throw InvalidDateException();
    }
}

void ExamDetails::timeValid(double time) {
    if (time < 0) {
        // encase of 00:00
        if (abs(time) >= TEN_POWER_MINUS_SIX) {
            throw InvalidTimeException();
        }
    }
    double int_part;
    double fraction = modf(time, &int_part);

    if (!(abs(HALF_AN_HOUR - fraction) < TEN_POWER_MINUS_SIX || fraction < TEN_POWER_MINUS_SIX)) {
        throw InvalidTimeException();
    }
}

void ExamDetails::longValid(int how_long) {
    if (how_long < 0) {
        throw InvalidArgsException();
    }
}

bool ExamDetails::examParallel(double time_differance, int how_long_first, int how_long_second) {
    if (time_differance < 0) {
        return (-time_differance) < double(how_long_first);
    }
    return (time_differance) < double(how_long_second);
}

ExamDetails::ExamDetails(int course_number, int month, int day, double time, int how_long, string url) :
        _course_number(course_number), _month(month), _day(day), _time(time), _how_long(how_long),
        _url(std::move(url)) {
    dateValid(day, month);
    timeValid(time);
    longValid(how_long);
}

ExamDetails ExamDetails::makeMatamExam() {
    return ExamDetails(234124, 7, 28, 13, 3, "https://tinyurl.com/59hzps6m ");
}

int ExamDetails::operator-(const ExamDetails &a) const {
    return (_month - a._month) * DAYS_IN_MONTH + _day - a._day;
}

int ExamDetails::operator<(const ExamDetails &a) const {
    int day_differance = this->operator-(a);

    if (day_differance == 0) {
        double time_differance = _time - a._time;
        if (time_differance == 0) {
            return false;
        }
        if (examParallel(time_differance, _how_long, a._how_long)) {
            return false;
        }
        return time_differance < 0;
    }
    return day_differance < 0;
}

std::ostream &operator<<(std::ostream &out, const ExamDetails &a) {
    double fraction;
    double int_part;
    fraction = modf(a._time, &int_part);
    out << endl << "Course Number: " << a._course_number << endl;
    out << "Time: " << a._day << "." << a._month << " at " << int(int_part) << ":";
    if (abs(fraction) > TEN_POWER_MINUS_SIX) {
        out << "30" << endl;
    } else {
        out << "00" << endl;
    }
    out << "Duration: " << a._how_long << ":" << "00" << endl;
    out << "Zoom Link: " << a._url;

    return out;
}
