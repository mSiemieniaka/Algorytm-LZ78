#pragma once
#include <fstream>
#include <vector>
#include "Files.h"
#include "Parameters.h"

class Decompress
{
public:
	virtual std::vector<char> decompress(int s) = 0; //algorytm dekompresji 
	virtual void loadData(Files<std::ifstream> &inputfile, Parameters &p) = 0; //ladujemy dane z pliku 
	virtual ~Decompress() {}
};