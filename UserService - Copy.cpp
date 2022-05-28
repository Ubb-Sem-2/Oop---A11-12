#include "UserService.h"
#include <algorithm>
#include "CSVrepo.h"
#include "HTMLrepo.h"



UserService::UserService(Repository& repo1, WatchListRepo* wl) : repo(repo1) {
	this->watchListRepo = wl;
}

UserService::UserService(Repository& repo1) : repo(repo1)
{
}

std::vector<Tutorial> UserService::getAllUserService()
{
	if (this->watchListRepo->getWL().empty())
	{
		std::string error;
		error += std::string("The watch list is empty");
		if (!error.empty())
			throw WLException(error);
	}
	return this->watchListRepo->getWL();
}

int UserService::getNrElems()
{
	if (this->watchListRepo->GetLength() == 0)
	{
		std::string error;
		error += std::string("The watch list is empty");
		if (!error.empty())
			throw WLException(error);
	}
	return this->watchListRepo->GetLength();
}


std::string& UserService::getFileService()
{
	return this->watchListRepo->getFilename();
}


void UserService::AddUserService(const Tutorial& tut)
{
	this->watchListRepo->AddTutorialWL(tut);
}

void UserService::DeleteUserService(int pos)
{
	this->watchListRepo->DeleteTutorialWL(pos);
}

void UserService::repoType(const std::string& fileType)
{
	if (fileType == "csv")
	{
		std::vector<Tutorial> userVector;
		//std::string userFile = "D:\\FACULTATE\\Materiale facultate 2021-2022\\1.2\\Object Oriented Programming\\Assignments\\A8-9\\A8-9\\A8-9\\WatchList.csv";
		std::string userFile = "D:\FACULTATE\WatchList.csv";
		auto* repo = new CSVRepo(userVector, userFile);
		this->watchListRepo = repo;
	}
	else if (fileType == "html")
	{
		std::vector<Tutorial> userVector;
		//std::string userFile = "D:\\FACULTATE\\Materiale facultate 2021-2022\\1.2\\Object Oriented Programming\\Assignments\\A8-9\\A8-9\\A8-9\\WatchList.html";
		std::string userFile = "D:\FACULTATE\WatchList.html";
		auto* repo = new HTMLRepo(userVector, userFile);
		this->watchListRepo = repo;
	}
	else
	{
		std::string error;
		error += std::string("The filename is invalid");
		if (!error.empty())
			throw WLException(error);
	}
}

UserService::~UserService()
{
}