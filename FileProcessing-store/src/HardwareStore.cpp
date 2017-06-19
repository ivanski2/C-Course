#include "HardwareStore.h"
#include <fstream>
#include <iostream>
using std::cout;
using std::cin;
#include <cstdlib>
using std::exit;
#include <string>

HardwareStore::HardwareStore()
{
	// TODO Auto-generated constructor stub

}

HardwareStore::~HardwareStore()
{
	// TODO Auto-generated destructor stub
}

void HardwareStore::populateTemplateFile(std::fstream& binaryFile)
{
	Tool* tool = new Tool;
	for (int i = 0; i < 100; ++i)
	{
		binaryFile.write(reinterpret_cast<const char*>(tool), sizeof(Tool) );
	}
}

int HardwareStore::getPosition()
{
	int filePostition;

	do
	{
		cout << "Enter id(1 - 100).\n";
		cin >> filePostition;
	}while(filePostition < 1 || filePostition > 100);

	return filePostition;
}

void HardwareStore::addToBinary(std::fstream& insertInFile)
{
	int position = getPosition();
	insertInFile.seekg((position - 1) * sizeof(Tool));

	Tool* tool = new Tool;
	insertInFile.read(reinterpret_cast< char* >(tool), sizeof(Tool));

	//Check if current postion has Empty template
	if(tool->getId() == 0)
	{
		tool->setId(position);
		cout << "Enter tool name:\n";
		std::string toolName;
		cin >> toolName;
		tool->setName(toolName);

		cout << "Enter quantity:\n";
		int quantity;
		cin >> quantity;
		tool->setQuantity(quantity);

		cout << "Enter price:\n";
		double price;
		cin >> price;
		tool->setPrice(price);

		insertInFile.seekg((position - 1) * sizeof(Tool) );
		insertInFile.write(reinterpret_cast<const char *>(tool), sizeof(Tool) );

		delete tool;
	}
	else
	{
		std::cerr << "Accout with id:" << tool->getId() << " already exists.\n";
	}
}

void HardwareStore::sendTotextFile(std::ofstream& outputFile, std::fstream& readFromFile)
{
	if(! outputFile)
	{
		std::cerr << "Can't open output file.\n";
		exit(1);
	}
	if(! readFromFile)
	{
		std::cerr << "Can't open binary file.\n";
		exit(1);
	}

	outputFile << "#\t Name \t Quantity \t Price\n";

	//set position to begining of file
	readFromFile.seekg(0);
	Tool* tool = new Tool;
	readFromFile.read(reinterpret_cast<char *>(tool), sizeof(Tool) );

	while(! readFromFile.eof())
	{

		if(tool->getId() != 0)
		{
			std::cout << tool->print();
			outputFile << tool->print();
		}

		readFromFile.read(reinterpret_cast<char*>(tool), sizeof(Tool) );
	}
}

void HardwareStore::updateRecord(std::fstream& binaryFile, int toolId)
{
	if(! binaryFile)
	{
		std::cerr << "Can't open binary file.\n";
		return;
	}

	binaryFile.seekg( (toolId - 1) * sizeof(Tool) );

	Tool* tool = new Tool;
	binaryFile.read(reinterpret_cast< char * >(tool), sizeof(Tool) );//populate with data from file

	if(tool->getId() == 0)
	{
		std::cout << "Record is empty.\n";
		return;
	}

	std::cout << "Enter new name, quantity and price:\n";
	std::string name;
	int quantity;
	double price;
	std::cin >> name >> quantity >> price;
	tool->setName(name);
	tool->setQuantity(quantity);
	tool->setPrice(price);

	binaryFile.seekp( (tool->getId() - 1) * sizeof(Tool) );
	binaryFile.write(reinterpret_cast<const char*>(tool), sizeof(Tool) );

	delete tool;
}

void HardwareStore::deleteRecord(std::fstream& binaryFile, int toolId)
{
	if(! binaryFile)
	{
		std::cerr << "Can't open binary file.\n";
		return;
	}

	binaryFile.seekg( (toolId - 1) * sizeof(Tool) );

	Tool* tool = new Tool;
	binaryFile.read(reinterpret_cast<char*>(tool), sizeof(Tool) );

	if(tool->getId() == 0)
	{
		std::cerr << "Data field is empty.\n";
		delete tool;
		return;
	}
	Tool* emptyTool = new Tool;
	binaryFile.seekp( (toolId - 1) * sizeof(Tool) );
	binaryFile.write(reinterpret_cast<const char*>(emptyTool), sizeof(Tool) );
	delete emptyTool;
}

int HardwareStore::promptId(std::string& prompt)
{
	std::cout << prompt;
	int toolId;
	std::cin >> toolId;
	return toolId;
}
