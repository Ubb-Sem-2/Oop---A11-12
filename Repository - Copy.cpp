#include "Tutorial.h"
#include "Repository.h"
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <fstream>
using namespace std;


RepositoryException::RepositoryException(std::string& _message) : message(_message)
{
}

const char* RepositoryException::what() const NOEXCEPT
{
	return message.c_str();
}



Repository::Repository(string& tutfn)
{
	this->tutFilename = tutfn;
}

int Repository::addTutorial(const Tutorial& element)
{
	int check = CheckIfExist(element);
	if (check != -1)
	{
		std::string error;
		error += std::string("The tutorial already exists");
		if (!error.empty())
		{
			throw RepositoryException(error);
			return -1;
		}
	}

	myVector.push_back(element);
	this->writeTutFile();
	return 1;
}


int Repository::DeleteTutorial(int pos)
{
	if (pos == -1)
	{
		std::string error;
		error += std::string("The tutorial does not exist");
		if (!error.empty())
		{
			throw RepositoryException(error);
			return -1;
		}
	}

	this->myVector.erase(myVector.begin() + pos);
	this->writeTutFile();
	return 1;
}

//if the element is in the repo, return the position of it, else return -1
int Repository::CheckIfExist(const Tutorial& tut)
{
	//i need the position
	for (int i = 0; i < myVector.size(); i++)
	{
		if (myVector[i] == tut)
		{
			return i;
		}
	}
	return -1;


}

//return -1 if the position is bigger than the size of repo, else return 1
int Repository::UpdateTutorial(const Tutorial& tut, int pos)
{
	if (pos == -1)
	{
		std::string error;
		error += std::string("The tutorial does not exist");
		if (!error.empty())
		{
			throw RepositoryException(error);
			return -1;
		}
	}

	myVector[pos] = tut;
	this->writeTutFile();
	return 1;
}


int Repository::size()
{
	return myVector.size();
}


vector<Tutorial> Repository::GetTutorials() const
{
	return this->myVector;
}



void Repository::increaseLikes(int pos)
{
	//i need the position
	int len = this->myVector.size();
	int i = 0, ok = 0;
	while (i < len && ok == 0)
	{
		if (i == pos)
		{
			ok = 1;
			int likes = this->myVector[i].GetLikes();
			likes++;
			this->myVector[i].SetLikes(likes);
		}

		i++;
	}

}


Repository::~Repository()
{
}



void Repository::writeTutFile()
{
	if (!this->tutFilename.empty())
	{
		ofstream fout(this->tutFilename);
		for (const Tutorial& tut : this->myVector)
			fout << tut << "\n";
		fout.close();
	}

}



void Repository::loadTutFromFile()
{
	if (!this->tutFilename.empty())
	{
		Tutorial tutfile;
		ifstream fin(this->tutFilename);
		while (fin >> tutfile)
		{
			if (find(this->myVector.begin(), this->myVector.end(), tutfile) == this->myVector.end())
				this->myVector.push_back(tutfile);
		}
		fin.close();
	}

}


void Repository::initialiseRepo()
{
	this->loadTutFromFile();

}


