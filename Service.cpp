
#include "Service.h"
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>

/*
Service::Service(Repository& r, WatchListRepo& wl): service(r), wl(wl)
{
}
*/

Service::Service(Repository& r) : service(r)
{
}


int Service::AddTutorialService(const std::string& title, const std::string& presenter, int minutes, int seconds, int likes, const std::string& source)
{
	Tutorial new_tutorial(title, presenter, minutes, seconds, likes, source);
	int rez = this->service.addTutorial(new_tutorial);
	if (rez == -1)
		return -1;
	return 1;

	//check if already exists in the repo
	/*
	if (this->service.CheckIfExist(new_tutorial) == -1)
	{
		this->service.addTutorial(new_tutorial);
		return 1;//the tutorial was added
	}*/

	//return -1;

}




int Service::DeleteTutorialService(const std::string& title, const std::string& presenter, int minutes, int seconds, int likes, const std::string& source)
{
	Tutorial tutorial(title, presenter, minutes, seconds, likes, source);
	int pos = this->service.CheckIfExist(tutorial);
	int rez = service.DeleteTutorial(pos);
	if (rez == -1)
		return -1;
	return 1;


	//find the position of the tutorial
	/*
	int pos = this->service.CheckIfExist(tutorial);
	if (pos == -1)
		return -1;//cannot delete something that does not exist



	return 1;*/
}




int Service::UpdateTutorialService(const std::string& o_title, const std::string& o_presenter, int o_minutes, int o_seconds, int o_likes, const std::string& o_source, const std::string& n_title, const std::string& n_presenter, int n_minutes, int n_seconds, int n_likes, const std::string& n_source)
{
	Tutorial old_tut(o_title, o_presenter, o_minutes, o_seconds, o_likes, o_source);
	Tutorial new_tut(n_title, n_presenter, n_minutes, n_seconds, n_likes, n_source);
	int pos = this->service.CheckIfExist(old_tut);
	int rez = this->service.UpdateTutorial(new_tut, pos);

	if (rez == -1)
		return -1;
	return 1;

	/*
	if (pos == -1)
		return -1;


	return 1;
	*/
}

/*
Tutorial* Service::GetTutorialRepo() const
{
	return this->service.GetTutorials();
}*/




int Service::GetLengthRepo()
{
	return this->service.size();
}

vector<Tutorial> Service::GetServ() const
{
	return this->service.GetTutorials();


}

/*
vector<Tutorial> Service::GetTutorialsWL() const
{
	//return this->wl.GetWL();
	 return this->wl.getWL();
}*/


Service::~Service()
{
}


/*
void Service::AddToWL(Tutorial t)
{
	this->wl.AddTutorialWL(t);
}*/


/*
Tutorial* Service::GetTutorialsWL() const
{
	return this->wl.GetTutorials();
}*/


/*
int Service::GetLenWL()
{
	return this->wl.GetLength();
}*/



/*
void Service::DeleteTutorialWL(int pos)
{
	this->wl.DeleteTutorialWL(pos);

}*/




int Service::FindInRepo(Tutorial t)
{
	int res = this->service.CheckIfExist(t);
	if (res != -1)
		return res;
	return -1;
}

int Service::FindbyTitle(std::string title)
{
	for (int i=0;i<service.GetTutorials().size(); i++)
	{
		if (service.myVector[i].GetTitle() == title)
			return i;
	}
	return -1;
}

void Service::getFiltered(std::vector<Tutorial>& valid_tuts, const std::string& filter_pres)
{
	std::vector<Tutorial> data;
	data = this->service.GetTutorials();
	if (filter_pres[0] == '\0')
		std::copy(data.begin(), data.end(), std::back_inserter(valid_tuts));
	else
		std::copy_if(data.begin(), data.end(), std::back_inserter(valid_tuts), [&filter_pres](Tutorial& tut) { return tut.GetPresenter() == filter_pres;  });
}


void Service::IcreaseLikes(int pos)
{
	this->service.increaseLikes(pos);
}




