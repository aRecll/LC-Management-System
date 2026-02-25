#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
class date
{
private:
#pragma region data
    int day;
    int month;
    int year;
    bool isValidDate(int d, int m, int y)const;
#pragma endregion

    
public:
#pragma region constructors
    date() : day(1), month(1), year(2000) {}
    date(int d, int m, int y);
#pragma endregion

    

#pragma region functions
    void input();

    void output() const;
#pragma endregion

    
#pragma region getters
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
#pragma endregion

    
    

#pragma region operators
    friend std::ostream& operator<<(std::ostream& os, const date& dt);

    
    friend std::istream& operator>>(std::istream& is, date& dt);
    date& operator=(const date& other);
    bool operator==(const date& other) const;
#pragma endregion

    
};


