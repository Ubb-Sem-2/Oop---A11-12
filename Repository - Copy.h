#pragma once
#include "Tutorial.h"
//#include "DynamicVector.h"
#include <vector>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif



using namespace std;

class Repository
{
private:
	//DynamicVector<Tutorial> repo;
	string tutFilename;

public:
	/*
	//deafult constructor
	Repository(DynamicVector<Tutorial>& v);

	Tutorial* GetTutorials() const;


	//Add a tutorial to the repository; t-Tutorial, output the tutorial is added
	void AddTutorial(const Tutorial& new_tutorial);

	//Find a song, by presenter and title; presenter and title - string, output: the tutorial that was found, or an "Empty" tutorial (all fields empty and duration 0), if nothing was found
	//Tutorial findByPresAndTitle(const std::string& presenter, const std::string& title);

	void DeleteTutorial(int pos);
	int UpdateTutorial(int pos, const Tutorial& tut);


	//check if a tutorial exists in the repo
	int CheckIfExist(const Tutorial& tut);
	int GetLength();*/

	Repository(string& tutFn);
	vector<Tutorial> myVector;
	//add tutorial
	int addTutorial(const Tutorial& element);
	//delete tutorial
	int DeleteTutorial(int position);
	//void update tutorial
	int UpdateTutorial(const Tutorial& tut, int pos);
	//size of repo
	int size();

	//check if a tutorial exists in the repo
	int CheckIfExist(const Tutorial& tut);

	vector<Tutorial> GetTutorials() const;

	void increaseLikes(int pos);

	//Tutorial* GetTutorials() const;
	~Repository();

	void writeTutFile();
	void loadTutFromFile();
	void initialiseRepo();


};


class RepositoryException : public std::exception
{
private:
	std::string message;

public:
	explicit RepositoryException(std::string& _message);
	const char* what() const NOEXCEPT override;

};


