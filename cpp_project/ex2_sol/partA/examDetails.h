//
// Created by USER on 31/10/2021.
//

#ifndef EX2_SPRING21_EXAMDETAILS_H
#define EX2_SPRING21_EXAMDETAILS_H

#include <iostream>
#include <string>
#include <utility>
#include <exception>

class ExamDetails {
    int _course_number, _month, _day, _how_long;
    double _time;
    std::string _url;

    static void dateValid(int day, int month);

    static void timeValid(double time);

    static void longValid(int how_long);

    static bool examParallel(double time_differance, int how_long_first, int how_long_second);

public:
    //C'tor and defaults
    ExamDetails(int course_number, int month, int day, double time, int how_long, std::string url = "");

    ExamDetails(const ExamDetails &exam_details) = default;

    ~ExamDetails() = default;

    ExamDetails &operator=(const ExamDetails &a) = default;

    //operators
    int operator-(const ExamDetails &a) const;

    int operator<(const ExamDetails &a) const;

    friend std::ostream& operator<<(std::ostream& out , const ExamDetails& a);

    // methods
    std::string getLink() const {
        return _url;
    }

    void setLink(std:: string url) {
        _url = std::move(url);
    }

    static ExamDetails makeMatamExam();

class InvalidDateException:public std::exception{
    };

    class InvalidTimeException:public std::exception{
    };

    class InvalidArgsException:public std::exception{
    };
};

#endif //EX2_SPRING21_EXAMDETAILS_H
