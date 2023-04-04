// Name: Eric Rak
// Seneca Student ID: 180211211
// Seneca email: erak@myseneca.ca
// Date of completion: Mar 25th 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.



#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>
#include <cctype>
#include "Utilities.h"

namespace sdds
{

    class Station
    {

        int m_id{};
        std::string m_name{};
        std::string m_description{};
        size_t m_nextSerialNumber{};
        size_t m_itemInStockCount{};
        static int m_widthField;
        static int id_generator;

    public:
        Station(const std::string rec);
        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };

}

#endif