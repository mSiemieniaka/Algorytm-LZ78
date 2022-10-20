#include "Parameters.h"
#include <iostream>

void Parameters::loadInputValues(int argc, char** argv)
{
	bool found[4] = { false, false, false, false }; //funkcja ktora odpowiada za znalezienie "-c" "-d" "-o" "-s"
	for (int i = 1; i < argc - 1; ++i)
	{
		if (strcmp(argv[i], "-c") == 0)
		{
			found[0] = true;
			parameters.what_to_do = 'c';
			parameters.input_filename.assign(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-d") == 0)
		{
			found[1] = true;
			parameters.what_to_do = 'd';
			parameters.input_filename.assign(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			found[2] = true;
			parameters.output_filename.assign(argv[i + 1]);
		}
		else if (strcmp(argv[i], "-s") == 0)
		{
			found[3] = true;
			parameters.dictionary_size = std::stoi(argv[i + 1]);
		}
	}
		
	if (found[0] && found[1]) //znaleziono "-c" "-d"
	{
		std::cout << "Mozliwa jest kompresja i dekompresja ale nie jest mozliwe stworzeniepliku wyjsciowego\n";
		std::exit(EXIT_FAILURE);
	}
	else if (!found[0] && !found[1]) //nie znaleziono "-c" "-d"
	{
		std::cout << "Plik wejsciowy nie zostal stworzony\n";
		std::exit(EXIT_FAILURE);
	}
	if (!found[2]) parameters.output_filename = "Output.txt";
	if (!found[3]) parameters.dictionary_size = 100000000;
}