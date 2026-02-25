#include "date.h"
#include <limits>



bool date::isValidDate(int d, int m, int y) const {
	if (y < 1900 || y > 2100) return false;
	if (m < 1 || m > 12) return false;

	int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {
		daysInMonth[1] = 29;
	}

	return d >= 1 && d <= daysInMonth[m - 1];
}

date::date(int d, int m, int y) {
	if (!isValidDate(d, m, y)) {
		throw std::invalid_argument("ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½");
	}
	day = d;
	month = m;
	year = y;
}

void date::input() {
	int d, m, y;
	std::cout << "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½: ";
	std::cin >> d;
	std::cout << "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½: ";
	std::cin >> m;
	std::cout << "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½: ";
	std::cin >> y;

	if (!isValidDate(d, m, y)) {
		throw std::invalid_argument("ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½");
	}

	day = d;
	month = m;
	year = y;
}

void date::output() const
{
	std::cout << day << "." << month << "." << year;
}

date& date::operator=(const date& other)
{
	if (this != &other) {
		day = other.day;
		month = other.month;
		year = other.year;
	}
	return *this;
}

bool date::operator==(const date& other) const
{
	return day == other.day && month == other.month && year == other.year;
}

std::ostream& operator<<(std::ostream& os, const date& dt)
{
	
		os << dt.day << "." << dt.month << "." << dt.year;
		return os;
	
}

std::istream& operator>>(std::istream& is, date& dt)
{
	std::ios_base::iostate original_state = is.rdstate();

	try {
		is.clear(); // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

		int d, m, y;
		std::cout << "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½: ";
		is >> d;
		if (is.fail()) {
			throw std::invalid_argument("ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½");
		}
		std::cout << "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½: ";
		is >> m;
		if (is.fail()) {
			throw std::invalid_argument("ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½");
		}
		std::cout << "ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½: ";
		is >> y;
		if (is.fail()) {
			throw std::invalid_argument("ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½");
		}

		

		if (!dt.isValidDate(d, m, y)) {
			throw std::invalid_argument("ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½");
		}
		dt.day = d;
		dt.month = m;
		dt.year = y;
		

		return is;

	}
	catch (const std::exception& e) {
		// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½
		is.clear(original_state);
		is.setstate(std::ios::failbit);
		is.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
		throw; // Ïðîáðàñûâàåì èñêëþ÷åíèå ÁÅÇ âûâîäà ñîîáùåíèÿ
	}
}
