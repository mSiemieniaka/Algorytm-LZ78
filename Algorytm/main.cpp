#include "parameters.h"
#include "Compress.h"
#include "Decompress.h"
#include "LZ78_compress.h"
#include "LZ78_decompress.h"
#include <iostream>

int main(int argc, char** argv)
{
	Parameters params; //parametry wejsciowe
	params.loadInputValues(argc, argv);

	Compress *compressible_data; //wskaünik danych wejúciowych kompresji
	Decompress *decompressible_data; //wskaünik danych wejúciowych dekompresji
	std::vector<std::pair<int, char>> compressed; //skompresowane dane 
	std::vector<char> decompressed; //zdekopresowane dane

	Files<std::ifstream> inputfile(params.getInFilename());
	Files<std::ofstream> outputfile(params.getOutFilename());

	if (params.getWhatToDo() == 'c')//funkcja odpowiedzialna za kompresje
	{
		compressible_data = new LZ78_compress;
		compressible_data->loadData(inputfile);
		compressed = compressible_data->compress(params.getDictionarySize());
		delete compressible_data;
		outputfile.save(compressed, params.getDictionarySize());
	}
	else if (params.getWhatToDo() == 'd')//funkcja odpowiedzialna za kompresje
	{
		decompressible_data = new LZ78_decompress;
		decompressible_data->loadData(inputfile, params);
		decompressed = decompressible_data->decompress(params.getDictionarySize());
		delete decompressible_data;
		if (decompressed.empty()) std::exit(EXIT_FAILURE);
		outputfile.save(decompressed);
	}

	return 0;
}