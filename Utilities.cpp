// Name: Eric Rak
// Seneca Student ID: 180211211
// Seneca email: erak@myseneca.ca
// Date of completion: Mar 25th 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Utilities.h"

using namespace std;

namespace sdds
{

	size_t Utilities::m_widthField{};
	char Utilities::m_delimiter{};

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
	{
		std::string::size_type end_pos;
		std::string returnString{}; // set returnStrings default value

		end_pos = str.find(m_delimiter, next_pos); // get pos of the next delimiter

		more = false;
		if (str[next_pos] == m_delimiter) // check if nextPos is already position of delimiter
		{
			throw "delimiter Found at next_post";
		}

		returnString = str.substr(next_pos, end_pos - next_pos); // assign substring value to return String

		if (returnString != "") // check if it succesfully assigned anything
		{
			next_pos = end_pos + 1;							 // update next_pos
			more = true;									 // should repeat loop
			if (m_widthField < strlen(returnString.c_str())) // check if the current object is the longest
			{
				m_widthField = strlen(returnString.c_str());
			}
		}
		if (end_pos > str.length()) // shouldnt continue if the end positon is greater than the length.
		{
			more = false;
		}
		trim(returnString);
		return returnString;
	}

	void trim(std::string &str)
	{
		while (str[0] == ' ' || str[str.length() - 1] == ' ')
		{
			if (str[0] == ' ')
			{
				str.erase(0, 1);
			}
			if (str[str.length() - 1] == ' ')
			{
				str.erase(str.find_last_not_of(" \t\r\n") + 1);
			}
		}
	}
}