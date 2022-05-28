#pragma once
#include "WatchListRepo.h"

class CSVRepo : public WatchListRepo
{
public:
	CSVRepo(const std::vector<Tutorial>& wl, const std::string& userFilename);

	std::vector<Tutorial>& getWL() override;

	int GetLength() override;

	void AddTutorialWL(const Tutorial& tut) override;
	void DeleteTutorialWL(int pos) override;

	void writeToFile() override;

	std::string& getFilename() override;

	~CSVRepo();


};