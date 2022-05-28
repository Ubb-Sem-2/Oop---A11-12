#include <fstream>
#include "HTMLrepo.h"

HTMLRepo::HTMLRepo(const std::vector<Tutorial>& watchlist, const std::string& userFilename)
{
	this->watchList = watchlist;
	this->userFilename = userFilename;
}

std::vector<Tutorial>& HTMLRepo::getWL()
{
	return this->watchList;
}

int HTMLRepo::GetLength()
{
	return this->watchList.size();
}

std::string& HTMLRepo::getFilename()
{
	return this->userFilename;
}

void HTMLRepo::AddTutorialWL(const Tutorial& tut)
{
	this->watchList.push_back(tut);
	this->writeToFile();
}

void HTMLRepo::DeleteTutorialWL(int pos)
{
	this->watchList.erase(watchList.begin() + pos);
	this->writeToFile();
}

void HTMLRepo::writeToFile()
{
	std::ofstream fout(this->userFilename);
	fout << "<!DOCTYPE html>\n<html><head>\n<title>Watch List</title></head><body>\n";
	fout << "<table border=\"1\">\n";
	fout << "<tr><td>Title</td><td>Presenter</td><td>Minutes</td><td>Seconds</td><td>Likes</td><td>Source</td></tr>\n";
	for (const Tutorial& tut : this->watchList)
	{
		fout << "<tr>\n<td>" << tut.GetTitle() << "</td>"
			<< "<td>" << tut.GetPresenter() << "</td>"
			<< "<td>" << tut.GetMinutes() << "</td>"
			<< "<td>" << tut.GetSeconds() << "</td>"
			<< "<td>" << tut.GetLikes() << "</td>"
			<< "<td><a href =\"" << tut.GetSource() << "\">" << "Link</a></td>" << '\n' << "</tr>";
	}
	fout << "</table></body></html>";
	fout.close();
}

HTMLRepo::~HTMLRepo()
{
}