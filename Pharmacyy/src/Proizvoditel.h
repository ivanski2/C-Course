/*
 * Proizvoditel.h
 *
 *  Created on: 20.06.2017 ã.
 *      Author: ivanski
 */

#ifndef PROIZVODITEL_H_
#define PROIZVODITEL_H_
using namespace std;
#include <string>

enum Types
{
    FreeToSell,
    WithBlue,
    WithGreen
};

class Proizvoditel
{
public:
    std::string name;
    std::string code;
    std::string country;

    bool operator ==(const Proizvoditel &other) const
    {
        return (name == other.name) && (code == other.code) && (country == other.country);
    };
};

#endif /* PROIZVODITEL_H_ */
