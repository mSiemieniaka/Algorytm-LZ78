#include "LZ78_compress.h"
#include <string>
#include <map>
#include <algorithm>

std::vector<std::pair<int, char>> LZ78_compress::compress(int s)
{
	std::vector<std::pair<int, char>> out; // wektor wyjsciowy par
	std::map<int, std::string> dictionary; // zmienna w ktorej przechowujemy i wartosc maksymalna slownika i napis
	int index = 1; //index slownika 
	int found_prev; //index najdluzszego mozliwego podciagu 
	int i = 0; //index wektora wejsciowego
	int n = data.size(); //rozmiar wektora wejsciowego 
	std::string subs;
	std::map<int, std::string>::iterator it; //znaleziony iterator podciagu
	bool flag = true; //zakres sterowania flag¹ 

	while (i < n)
	{
		subs = data[i];
		flag = true;
		do
		{
			it = std::find_if(dictionary.begin(), dictionary.end(), [&](auto q)->bool { return subs == q.second; });
			if (it != dictionary.end() && i != n - 1)
			{
				++i;
				subs += data[i];
				found_prev = it->first;
				flag = false;
			}
			else if (flag) found_prev = 0;
			if (i == n - 1) break;
		} while (it != dictionary.end());

		dictionary.insert(std::pair<int, std::string>(index, subs));
		out.emplace_back(std::make_pair(found_prev, data[i]));

		++index;
		++i;

		if (dictionary.size() == s)
		{
			dictionary.clear();
			index = 1;
		}
	}
	return out;
}