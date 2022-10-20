#include "LZ78_decompress.h"
#include <string>
#include <map>

std::vector<char> LZ78_decompress::decompress(int s)
{
	std::vector<char> out; //wektor wyjsciowy
	std::map<int, std::string> dictionary;
	int i = 0; //wektor wejœciowy dla indexu par
	int n = data.size(); //wektor wejœciowy dla rozmiaru par
	int index = 1; //index slownika 
	std::string subs;
	std::map<int, std::string>::iterator it; //znaleziono iterator podciagu 

	while (i < n)
	{
		if (data[i].first == 0)
		{
			out.push_back(data[i].second);
			subs = data[i].second;
			dictionary.insert(std::pair<int, std::string>(index, subs));
		}
		else
		{
			it = dictionary.find(data[i].first);
			subs = it->second;
			subs += data[i].second;
			for (int j = 0; j < subs.size(); ++j) out.push_back(subs[j]);
			dictionary.insert(std::pair<int, std::string>(index, subs));
		}
		++i;
		++index;

		if (dictionary.size() == s)
		{
			dictionary.clear();
			index = 1;
		}
	}
	return out;
}