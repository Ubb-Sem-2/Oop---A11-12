#include <fstream>
#include "WatchListRepo.h"


WLException::WLException(std::string& _message) : message(_message)
{
}

const char* WLException::what() const NOEXCEPT
{
	return message.c_str();
}


WatchListRepo::WatchListRepo()
{
}

WatchListRepo::WatchListRepo(std::vector<Tutorial>& watchlist1)
{
	this->watchList = watchlist1;
}

WatchListRepo::~WatchListRepo()
{
}