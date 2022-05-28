#pragma once
#include "Repository.h"
//#include "WatchList.h"
#include "WatchListRepo.h"

class Service
{
private:
	Repository& service;
	//WatchList & wl;
	//WatchListRepo& wl;
public:
	//Service(Repository& r, WatchList& wl);
	//Service(Repository& r, WatchListRepo& wl);
	Service(Repository& r);
	//Service(Repository& r, WatchList& w);

	int AddTutorialService(const std::string& title, const std::string& presenter, int minutes, int seconds, int likes, const std::string& source);

	int DeleteTutorialService(const std::string& title, const std::string& presenter, int minutes, int seconds, int likes, const std::string& source);

	int UpdateTutorialService(const std::string& o_title, const std::string& o_presenter, int o_minutes, int o_seconds, int o_likes, const std::string& o_source, const std::string& n_title, const std::string& n_presenter, int n_minutes, int n_seconds, int n_likes, const std::string& n_source);

	int GetLengthRepo();
	//Tutorial* GetTutorialRepo() const;

	//void AddToWL(Tutorial t);
	//Tutorial* GetTutorialsWL() const;
	//int GetLenWL();

	int FindInRepo(Tutorial t);

	//void DeleteTutorialWL(int pos);
	void IcreaseLikes(int pos);

	int size();
	~Service();
	vector<Tutorial> GetServ() const;
	//vector<Tutorial> GetTutorialsWL() const;

	int FindbyTitle(std::string name);
	void getFiltered(std::vector<Tutorial>& valid_tuts, const std::string& filter_pres);
	void writetoFileServie() { this->service.writeTutFile(); };

};
