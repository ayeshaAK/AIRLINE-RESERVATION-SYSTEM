#pragma once

#include <iostream>
#include "utilFunctions.h"
using namespace std;

class Date {
private:
	int year;
	int month;
	int day;
	int upp_lim(int m);
	string toStr(int x);
	string toStr(int x) const;
	void ensure_valid(Date& x, bool y);
public:
	Date();
	Date(int year, int month, int day);
	const Date& operator =(const Date& obj);
	Date operator +(const Date& obj);
	Date operator -(const Date& obj);
	Date operator +(int x);
	Date operator -(int x);
	bool operator > (const Date& obj) const;
	bool operator >= (const Date& obj) const;
	bool operator < (const Date& obj) const;
	bool operator <= (const Date& obj) const;
	bool operator == (const Date& obj) const;
	bool operator != (const Date& obj) const;
	void display() const;
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	bool isLeapYear() const;
	string toString();
};

template <typename O>
O& operator<<(O& o, const Date& obj)
{
	o<<obj.getDay()<<"/"<<obj.getMonth()<<"/"<<obj.getYear();
	return o;
}

Date::Date(int year, int month, int day) {
	this->year = year;
	this->month = month;
	this->day = day;
	ensure_valid(*this, 0);
	ensure_valid(*this, 1);
}
Date::Date()
{
	this->year = 1998;
	this->month = 12;
	this->day = 2;
	ensure_valid(*this, 0);
	ensure_valid(*this, 1);
}
const Date& Date::operator =(const Date& obj) {
	this->year = obj.year;
	this->month = obj.month;
	this->day = obj.day;
	return *this;
}
bool Date::isLeapYear() const {
	if (this->year % 4 == 0) {
		if ((this->year % 400 != 0) && (this->year % 100 == 0)) {
			return false;
		}
		return true;
	}
	return false;
}
int Date::upp_lim(int m) {
	switch (m) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12: {
		return 31;
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11: {
		return 30;
	}
	case 2: {
		if (this->isLeapYear() == 1) {
			return 29;
		}
		return 28;
	}
	}
}
Date Date::operator +(const Date& obj){
	Date x(this->year + obj.year, this->month + obj.month, this->day + obj.day);
	ensure_valid(x, 1);
	return x;
}
Date Date::operator +(int x){
	Date z(this->year, this->month, this->day + x);
	ensure_valid(z, 1);
	return z;
}
Date Date::operator -(const Date& obj) {
	Date x(this->year - obj.year, this->month - obj.month, this->day - obj.day);
	ensure_valid(x, 0);
	return x;
}
void Date::display() const {
	cout
		<< toStr(this->year) + "/" + toStr(this->month) + "/"
		+ toStr(this->day) << endl;
}
string Date::toStr(int x) const{
	if (x <= 0) {
		return "";
	}
	char c = (x % 10) + 48;
	return toStr(x / 10) + c;
}
string Date::toStr(int x){
	if (x <= 0) {
		return "";
	}
	char c = (x % 10) + 48;
	return toStr(x / 10) + c;
}
Date Date::operator -(int x) {
	Date z(this->year, this->month, this->day - x);
	ensure_valid(z, 0);
	return z;
}
int Date::getDay() const {
	return this->day;
}
int Date::getMonth() const {
	return this->month;
}
int Date::getYear() const {
	return this->year;
}
string Date::toString() {
	return toStr(this->year) + "/" + toStr(this->month) + "/" + toStr(this->day);
}
bool Date::operator >(const Date& obj) const {
	if (this->year > obj.year) {
		return true;
	}
	else if (this->year == obj.year) {
		if (this->month > obj.month) {
			return true;
		}
		else if (this->month == obj.month) {
			if (this->day > obj.day) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
bool Date::operator >=(const Date& obj) const {
	if (this->year == obj.year) {
		if (this->month == obj.month) {
			if (this->day >= obj.day) {
				return true;
			}
			return false;
		}
		else if (this->month > obj.month) {

			return true;
		}
		return false;
	}
	else if (this->year > obj.year) {
		return true;
	}
	return false;
}
bool Date::operator <(const Date& obj) const {
	if (this->year < obj.year) {
		return true;
	}
	else if (this->year == obj.year) {
		if (this->month < obj.month) {
			return true;
		}
		else if (this->month == obj.month) {
			if (this->day < obj.day) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
bool Date::operator <=(const Date& obj) const {
	if (this->year == obj.year) {
		if (this->month == obj.month) {
			if (this->day <= obj.day) {
				return true;
			}
			return false;
		}
		else if (this->month < obj.month) {

			return true;
		}
		return false;
	}
	else if (this->year < obj.year) {
		return true;
	}
	return false;
}
bool Date::operator ==(const Date& obj) const {
	if (this->year == obj.year) {
		if (this->month == obj.month) {
			if (this->day == obj.day) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
bool Date::operator !=(const Date& obj) const {
	if (this->year == obj.year) {
		if (this->month == obj.month) {
			if (this->day == obj.day) {
				return false;
			}
			return true;
		}
		return true;
	}
	return true;
}
void Date::ensure_valid(Date& x,
	bool y /*0 means check lower limit, 1 means check upper limit*/) {
	if (y) {
		while (x.month > 12) {
			x.month -= 12;
			x.year += 1;
		}
		while (x.day > upp_lim(x.month)) {
			x.day -= upp_lim(x.month);
			x.month += 1;
		}
		while (x.month > 12) {
			x.month -= 12;
			x.year += 1;
		}
	}
	else {
		while (x.month <= 0) {
			x.month += 12;
			x.year -= 1;
		}
		while (x.day <= 0) {
			x.day += upp_lim(x.month);
			x.month -= 1;
		}
		while (x.month <= 0) {
			x.month += 12;
			x.year -= 1;
		}
	}
}
