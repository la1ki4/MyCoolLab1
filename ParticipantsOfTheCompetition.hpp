#ifndef _PARTICIPANTS_H_
#define _PARTICIPANTS_H_

#include <iostream>
#include <string>
#include <vector>
#include "Date.hpp"

class ParticipantsOfTheCompetition : public Date
{
private:
	std::string last_name;
	std::string first_name;
	std::string _category;
	std::string _country;
	Date birth_year;
	unsigned short id_Participant;

public:
	ParticipantsOfTheCompetition() = default;
	ParticipantsOfTheCompetition(const std::string&, const std::string&, const std::string&, const std::string&, const Date&, const unsigned short&);
	ParticipantsOfTheCompetition(const ParticipantsOfTheCompetition&);
	const ParticipantsOfTheCompetition& operator=(const ParticipantsOfTheCompetition&);
	bool operator==(const ParticipantsOfTheCompetition&);

	std::string LastName() const;
	std::string FirstName() const;
	std::string Category() const;
	std::string Country() const;
	Date BirthYear() const;
	unsigned short IDParticipant() const;
};

std::istream& operator>>(std::istream&, ParticipantsOfTheCompetition&);
std::ostream& operator<<(std::ostream&, const ParticipantsOfTheCompetition&);

#endif