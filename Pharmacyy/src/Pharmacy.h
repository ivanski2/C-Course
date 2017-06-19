/*
 * Pharmacy.h
 *
 *  Created on: 20.06.2017 ã.
 *      Author: ivanski
 */

#ifndef PHARMACY_H_
#define PHARMACY_H_
#include"Proizvoditel.h"
#include"Lekarstvo.h"

class Farmacy
{
public:
    Lekarstvo* lekarstva;
    int nCount;

    Farmacy(Lekarstvo* lek, int count)
        : lekarstva(lek),
          nCount(count)
    {

    };

    void AddLekarstvo(Lekarstvo lek)
    {
        bool bExists = false;

        for (int i = 0; i < nCount; i++)
        {
            if (lekarstva[i] == lek)
            {
                bExists = true;
                break;
            }
        }


        if (!bExists)
        {
            nCount++;
            lekarstva[nCount] = lek;
        }
    };

    const Lekarstvo& FindLekarstvo(double price)
    {
        double min = lekarstva[0].price;
        Lekarstvo& minLek = lekarstva[0];

        for (int i = 0; i < nCount; i++)
        {
            if (min > lekarstva[i].price)
            {
                min = lekarstva[i].price;
                minLek = lekarstva[i];
            }
        }

        return minLek;
    };

    void GetTypesCount(int &nFree, int &nBlue, int &nGreen)
    {
        nFree = nBlue = nGreen = 0;

        for (int i = 0; i < nCount; i++)
        {
            switch(lekarstva[i].type)
            {
            case Types::FreeToSell:
                nFree++;
                break;
            case Types::WithBlue:
                nBlue++;
                break;
            case Types::WithGreen:
                nGreen++;
                break;
            }
        }
    };
};

#endif /* PHARMACY_H_ */
