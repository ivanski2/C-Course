#include "Tool.h"

#include <cstring>
using std::strncpy;
#include <sstream>
#include <iomanip>
using std::setw;

Tool::Tool(int id, std::string name, int quantity, double price)
{
	setId(id);
	setName(name);
	setQuantity(quantity);
	setPrice(price);
}

int Tool::getId() const
{
	return _id;
}

const char* Tool::getName() const
{
	return _name;
}

double Tool::getPrice() const
{
	return _price;
}

void Tool::setId(int id)
{
	_id = id;
}

void Tool::setName(std::string& name)
{
	const char* nameVal = name.data();
	int length = name.length();

	length = length < 20 ? length : 19;
	strncpy(this->_name, nameVal, length);
	this->_name[length] = '\0';
}

void Tool::setPrice(double price)
{
	_price = price;
}

void Tool::setQuantity(int quantity)
{
	_quantity = quantity;
}

int Tool::getQuantity() const
{
	return _quantity;
}

std::string Tool::print() const
{
	std::stringstream result;
	 result << setw(5) <<this->getId() << setw(20) << this->getName()
			 << "\t" << setw(5) << this->getQuantity()
			 << "\t" << setw(5) << this->getPrice()
			 << "\n";

	 return result.str();
}

