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
#include "Station.h"

using namespace std;

namespace sdds
{
	int Station::m_widthField{};
	int Station::id_generator = 0;

	Station::Station(const std::string rec)
	{
		Utilities util;

		m_id = ++id_generator; // set id and increment id generator
		std::string temp{};	   // to help with reading integers

		// name
		size_t pos = 0u;
		bool dummy{};
		m_name = util.extractToken(rec, pos, dummy);
		// check if this objects names width is the longest.
		if (m_widthField < (int)strlen(m_name.c_str()))
		{
			m_widthField = (int)strlen(m_name.c_str());
		}
		// serialNumber
		temp = util.extractToken(rec, pos, dummy);
		m_nextSerialNumber = stoi(temp);
		// quantity
		temp = util.extractToken(rec, pos, dummy);
		m_itemInStockCount = stoi(temp);
		// description
		m_description = util.extractToken(rec, pos, dummy);
	}
	const std::string &Station::getItemName() const
	{
		return m_name;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_nextSerialNumber++;
	}
	size_t Station::getQuantity() const { return m_itemInStockCount; }

	void Station::updateQuantity()
	{
		if (m_itemInStockCount > 0)
			m_itemInStockCount--;
	}

	void Station::display(std::ostream &os, bool full) const
	{
		// id
		os << setw(3) << setfill('0') << right << m_id << setfill(' ') << " | ";
		// name
		os << setw(m_widthField + 1) << left << m_name << " | ";
		// serialNum
		os << fixed << setw(6) << right << setfill('0') << m_nextSerialNumber << setfill(' ') << " | ";

		if (full)
		{
			// quantity and desc
			os << "" << setw(4) << right << m_itemInStockCount << " | " << m_description;
		}

		os << endl;
	}

}