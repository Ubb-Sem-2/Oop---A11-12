#include <fstream>
#include "CSVrepo.h"


CSVRepo::CSVRepo(const std::vector<Tutorial>& watchlist, const std::string& userFilename)
{
	this->watchList = watchlist;
	this->userFilename = userFilename;
}


std::vector<Tutorial>& CSVRepo::getWL()
{
	return this->watchList;
}

int CSVRepo::GetLength()
{
	return this->watchList.size();
}

std::string& CSVRepo::getFilename()
{
	return this->userFilename;
}

void CSVRepo::AddTutorialWL(const Tutorial& tut)
{
	this->watchList.push_back(tut);
	this->writeToFile();
}

void CSVRepo::DeleteTutorialWL(int pos)
{
	this->watchList.erase(watchList.begin() + pos);
	this->writeToFile();
}

void CSVRepo::writeToFile()
{
	std::ofstream fout(this->userFilename);
	if (!this->watchList.empty())
	{
		for (const Tutorial& tut : this->watchList)
			fout << tut << "\n";
	}
	fout.close();

}

CSVRepo::~CSVRepo()
{
}