// Name: Eric Rak
// Seneca Student ID: 180211211
// Seneca email: erak@myseneca.ca
// Date of completion: Mar 25th 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.



#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>
#include <string>

#include <iomanip>
#include <cstring>
#include <string>
#include <cctype>

namespace sdds
{

	class Utilities
	{

		static size_t m_widthField;

		static char m_delimiter;

	public:
		Utilities()
		{
			m_widthField = 0;
		};
		void setFieldWidth(size_t newWidth);

		size_t getFieldWidth() const;

		std::string extractToken(const std::string &str, size_t &next_pos, bool &more);

		static void setDelimiter(char newDelimiter)
		{
			m_delimiter = newDelimiter;
		}
		static char getDelimiter()
		{
			return m_delimiter;
		}
	};

	void trim(std::string &str);

}

#endif