#ifndef SRC_TOOL_H_
#define SRC_TOOL_H_

#include <string>

class Tool
{
private:
	int _id;
	char _name[20];
	int _quantity;
	double _price;

public:
	Tool(int id = 0, std::string name = "", int quantity = 0, double price = 0.0);
	virtual ~Tool();

	//getters
	int getId() const;
	const char* getName() const;
	double getPrice() const;
	int getQuantity() const;

	//setters
	void setId(int id);
	void setName(std::string& name);
	void setPrice(double price);
	void setQuantity(int quantity);

	std::string print() const;
};

#endif /* SRC_TOOL_H_ */
