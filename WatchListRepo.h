#pragma once

#include <vector>
#include "Tutorial.h"

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif


class WatchListRepo
{
protected:
	std::vector<Tutorial> watchList;
	std::string userFilename;
public:
	explicit WatchListRepo(std::vector<Tutorial>& watchList1);

	WatchListRepo();

	//get all the elements from the WatchListRepo
	virtual std::vector<Tutorial>& getWL() = 0;


	//return the number of elements from the WatchListRepos
	virtual int GetLength() = 0;

	//add a tutorial to the WatchListRepo
	virtual void AddTutorialWL(const Tutorial& tut) = 0;

	//delete a tutorial from the WatchListRepo
	virtual void DeleteTutorialWL(int pos) = 0;


	virtual void writeToFile() = 0;

	virtual std::string& getFilename() = 0;

	//void repositoryType(const std::string& fileType);

	~WatchListRepo();

};



class WLException : public std::exception
{
private:
	std::string message;
public:
	explicit WLException(std::string& _message);

	const char* what() const NOEXCEPT override;
};