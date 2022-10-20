#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Parameters.h"

template <class T>
class Files
{
private:
	T file; //zmienna odpowiadajaca za pliki wejsciowy/wyjsciowy
	std::string filename;

public:
	Files(std::string fn) : filename(fn) {}

	std::vector<char> load() //wczytaj plik do struktury danych zeby skompresowac (wektor)
	{
		std::vector<char> vec; //wektor przechowujacy nasze dane (text)
		file.open(filename);
		if (file.is_open())
		{
			auto ss = std::ostringstream{};
			ss << file.rdbuf();
			auto s = ss.str();
			file.close();
			std::copy(s.begin(), s.end(), std::back_inserter(vec));
		}
		else std::cout << "Ups cos poszlo nie tak z otwarciem pliku\n";
		return vec;
	}

	std::vector<std::pair<int, char>> load(Parameters &p) //wczytaj plik do struktury danych zeby zdekompresowac (pary wektorow)
	{
		std::vector<std::pair<int, char>> vec; //wektor przechowujacy dane (pair <index,znaw>)
		std::string buffer; //buffer tymczasowy
		int index; //zaladowany index
		std::string is; //aux
		char c; //zaladowany znak 
		std::string control; //zmienna potrzebna do sprawdzenia czy mozna zdekompresowac plik jesli nie bedzie mozliwe w oknie wyskoczy nam komunikat o bledzie
		int s; //zmienna przechowujaca rozmiar slownika
		file.open(filename);
		if (file.is_open())
		{
			file >> control;
			if (strcmp(control.c_str(), "W pliku jest mozliwa dekompresja :)") != 0) { std::cout << "Cos poszlo nie tak i dekompresja nie jest mozliwa\n"; return vec; }
			file >> s;
			p.setDictionarySize(s);
			while (file >> buffer)
			{

				is = "";
				for (int i = 0; buffer[i] != ','; ++i) is += buffer[i];
				index = std::stoi(is);
				if (buffer[buffer.size() - 1] == ',') c = ' ';
				else c = buffer[buffer.size() - 1];
				vec.emplace_back(std::make_pair(index, c));
			}
			file.close();
		}
		else std::cout << "Nie mozna otworzyc pliku wejsciowego\n";
		return vec;
	}

	void save(std::vector<char> const &vec) //funckja ta odpowiada za zapis wektora do pliku (dekompresja)	
	{
		file.open(filename);
		if (file.is_open())
		{
			std::ofstream ofs(filename);
			std::copy(vec.begin(), vec.end(), std::ostreambuf_iterator<char>(ofs));
			file.close();
		}
		else std::cout << "Nie mozna utworzyc pliku wyjsciowego\n";
	}

	void save(std::vector<std::pair<int, char>> const &vec, int s) //funkcja ta odpoiwada za zapis pary wektorow do pliku (kompresja)
	{
		file.open(filename);
		if (file.is_open())
		{
			file << "Kompresja wykonana :)\n" << s << "\n";
			std::ofstream ofs(filename);
			std::for_each(vec.begin(), vec.end(), [&](auto q)->void { file << q.first << "," << q.second << " "; });
			file.close();
		}
		else std::cout << "Nie mozna utworzyc pliku wyjsciowego\n";
	}
};
