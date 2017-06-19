#ifndef SRC_HARDWARESTORE_H_
#define SRC_HARDWARESTORE_H_

#include "Tool.h"

class HardwareStore
{
private:
	static int getPosition();
public:
	HardwareStore();
	virtual ~HardwareStore();
	static void populateTemplateFile(std::fstream& binaryFile);
	static void addToBinary(std::fstream& insertInFile);
	static void updateRecord(std::fstream& binaryFile, int toolId);
	static void deleteRecord(std::fstream& binaryFile, int toolId);

	static void sendTotextFile(std::ofstream& outputFile, std::fstream& readFromFile);

	static int promptId(std::string& prompt);
};

#endif /* SRC_HARDWARESTORE_H_ */
