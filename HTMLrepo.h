#pragma once
#include "WatchListRepo.h"

class HTMLRepo : public WatchListRepo
{
public:
	HTMLRepo(const std::vector<Tutorial>& watchlost, const std::string& userFilename);

	std::vector<Tutorial>& getWL() override;

	int GetLength() override;

	void AddTutorialWL(const Tutorial& tut) override;
	void DeleteTutorialWL(int pos) override;

	void writeToFile() override;

	std::string& getFilename() override;

	~HTMLRepo();
};