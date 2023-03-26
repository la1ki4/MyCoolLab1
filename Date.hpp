#ifndef _DATE_H_
#define _DATE_H_

#include <iostream>
#include <string>

class Date
{
private:
	unsigned short day;
	unsigned short month;
	unsigned short year;

public:
	Date() = default;
	Date(const unsigned short&, const unsigned short&, const unsigned short&);
	Date(const Date&);

	const Date& operator=(const Date&);
	bool operator==(const Date&);

	std::string toString() const;
	unsigned short Day() const;
	unsigned short Month() const;
	unsigned short Year() const;
};

std::istream& operator>>(std::istream&, Date&);
std::ostream& operator<<(std::ostream&, Date&);


#endif