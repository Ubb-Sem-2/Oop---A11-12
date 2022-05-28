#pragma once

#include "Repository.h"
#include "WatchListRepo.h"

class UserService
{
private:
	Repository& repo;
	WatchListRepo* watchListRepo;
public:
	UserService(Repository& repo, WatchListRepo* wl1);

	explicit UserService(Repository& repo);

	std::vector<Tutorial> getAllUserService();

	int getNrElems();

	void AddUserService(const Tutorial& tut);
	void DeleteUserService(int pos);

	void repoType(const std::string& fileType);
	std::string& getFileService();
	~UserService();

};