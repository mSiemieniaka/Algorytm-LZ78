#pragma once
#include <fstream>
#include <vector>
#include "Files.h"


class Compress
{
public:
	virtual std::vector<std::pair<int, char>> compress(int s) = 0; //algorytm kompresji 
	virtual void loadData(Files<std::ifstream> &inputfile) = 0; //ladujemy dane z pliku 
	virtual ~Compress() {}
};