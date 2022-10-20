#pragma once
#include <string>

struct InputValues //parametry wejsciowe
{
	char what_to_do; //zmienna ktora bedzie odpowiadac jakie parametry ma zwrocic czy kompresja czy dekompresja 
	std::string input_filename;
	std::string output_filename;
	int dictionary_size;
};

class Parameters
{
private:
	InputValues parameters; //parametry wejsciowe
	public:
	void loadInputValues(int argc, char** argv); //Funkcja trzymajaca nasze wartosci (bedzie uzywana w mainie)	
	char getWhatToDo() { return parameters.what_to_do; }
	std::string getInFilename() { return parameters.input_filename; }
	std::string getOutFilename() { return parameters.output_filename; }
	int getDictionarySize() { return parameters.dictionary_size; }
	void setDictionarySize(int s) { parameters.dictionary_size = s; }
};

