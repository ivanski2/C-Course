/*
 * Door.h
 *
 *  Created on: 20.06.2017 ã.
 *      Author: ivanski
 */

#ifndef DOOR_H_
#define DOOR_H_

class Door
{
public:
    int m_nWidth;
    int m_nHeigth;
    std::string m_strColor;

    Door(int width, int height, std::string color)
        : m_nWidth(width),
          m_nHeigth(height),
          m_strColor(color)
    {

    }

    inline bool operator < (const Door& rhs)
    {
        return (m_nWidth < rhs.m_nWidth) && (m_nHeigth < rhs.m_nHeigth);
    }


    inline bool operator > (const Door& rhs)
    {
        return (m_nWidth > rhs.m_nWidth) && (m_nHeigth > rhs.m_nHeigth);
    }

    bool operator==(const Door& other)
    {
        return (m_nWidth == other.m_nWidth) && (m_nHeigth == other.m_nHeigth) && (m_strColor == other.m_strColor);
    }

    std::ostream& operator<<(std::ostream& os)
    {
        return os << "door=> " << m_nHeigth << "x" << m_nWidth << " : " << m_strColor;
    }

    std::istream& operator>> (std::istream& is)
    {
        is >> m_nHeigth >> m_nWidth >> m_strColor;

        return is;
    }

    Door operator+(const Door& other)
    {
        Door door(
            m_nWidth + other.m_nWidth,
            m_nHeigth + other.m_nHeigth,
            m_strColor
        );

        return door;
    }
};

#endif /* DOOR_H_ */
