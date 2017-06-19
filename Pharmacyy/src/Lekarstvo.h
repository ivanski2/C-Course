/*
 * Lekarstvo.h
 *
 *  Created on: 20.06.2017 ã.
 *      Author: ivanski
 */

#ifndef LEKARSTVO_H_
#define LEKARSTVO_H_
#include<string>
#include"Proizvoditel.h"

class Lekarstvo
{
public:
    std::string name;
    Types type;
    double price;
    int kolichestvo;
    Proizvoditel proizvoditel;

    bool operator ==(const Lekarstvo &other) const
    {
        return ((name == other.name) && (type == other.type) && (price == other.price) && (kolichestvo == other.kolichestvo)
                && (proizvoditel == other.proizvoditel));
    };
};

#endif /* LEKARSTVO_H_ */
