#include <iostream>
#include <string>
#include <cstdlib>
using std::cerr;
#include <fstream>

#include "Tool.h"
#include "HardwareStore.h"
enum Menu {exit_opt, add_opt, update_opt, remove_opt};

int promptId(std::string& prompt);

int main()
{
	std::fstream store("HardwareStoreDataBase.dat", std::ios::in |std::ios::out | std::ios::binary);
	if(! store)
	{
		std::cerr << "Cant open binary file.\n";
		exit(1);
	}

	std::ofstream output("output.txt", std::ios::out | std::ios::in);
	if(! output)
	{
		std::cerr << "Cant open text file.\n";
		exit(1);
	}

	HardwareStore::populateTemplateFile(store);

	std::cout << "Select option(1 - 3) or 0 to exit:\n";
	std::cout << "1 -> add tool.\n";
	std::cout << "2 -> update tool data.\n";
	std::cout << "3 -> delete tool.\n";


	int option;
	std::cin >> option;

	while(option != exit_opt)
	{
		switch(option)
		{
		case add_opt:
			HardwareStore::addToBinary(store);
			break;

		case update_opt:
		{
			int toolId = HardwareStore::promptId(*new std::string("Enter tool id to update(1-100)") );
			HardwareStore::updateRecord(store, toolId);
		}
			break;

		case remove_opt:
		{
			int toolId = HardwareStore::promptId(*new std::string("Enter tool id to delete(1-100)"));
			HardwareStore::deleteRecord(store, toolId);
		}
			break;

		default: break;
		}

		std::cout << "Select option(1 - 3) or 0 to exit:\n";
		std::cin >> option;
	}

	HardwareStore::sendTotextFile(output, store);
	return 0;
}
