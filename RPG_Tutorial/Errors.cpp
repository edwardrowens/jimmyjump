#include "Errors.h"

void PrintErrors(std::string error, const char* (*errorFcn)()){
	std::cout << error << std::endl;
	std::cout << "Error Log:\n" << errorFcn() << std::endl;
	exit(1);
}


void PrintErrors(std::string error){
	std::cout << error << std::endl;
	exit(1);
}