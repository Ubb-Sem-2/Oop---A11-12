
#include "Tutorial.h"
#include <assert.h>
#include <vector>
#include <sstream>



Tutorial::Tutorial() : title(""), presenter(""), minutes(0), seconds(0), likes(0), source("")
{
}


Tutorial::Tutorial(const std::string& title, const std::string& presenter, int minutes, int seconds, int likes, const std::string& source)
	: title(title), presenter(presenter), minutes(minutes), seconds(seconds), likes(likes), source(source)
{
}


Tutorial::Tutorial(const Tutorial& tutorial) : title(tutorial.title), presenter(tutorial.presenter), minutes(tutorial.minutes), seconds(tutorial.seconds), likes(tutorial.likes), source(tutorial.source)
{
}

Tutorial::~Tutorial()
{
}

//return the title of the tutorial
std::string Tutorial::GetTitle() const
{
	return title;
}


//return the presenter of the tutorial
std::string Tutorial::GetPresenter() const
{
	return presenter;
}



//return the number of minutes that the tutorial has
int Tutorial::GetMinutes() const
{
	return minutes;
}




//return the number of seconds the tutorial has
int Tutorial::GetSeconds() const
{
	return seconds;
}



//return the number of likes the tutorial has
int Tutorial::GetLikes() const
{
	return likes;
}



//return the source of the tutorial
std::string Tutorial::GetSource() const
{
	return source;
}



//Sets a new title
void Tutorial::SetTitle(std::string new_title)
{
	title = new_title;
}





//sets a new presenter
void Tutorial::SetPresenter(std::string new_presenter)
{
	presenter = new_presenter;
}




//sets the new number of minutes
void Tutorial::SetMinutes(int min)
{
	minutes = min;
}



//sets a new number of seconds
void Tutorial::SetSeconds(int sec)
{
	seconds = sec;
}




//sets a new number of likes
void Tutorial::SetLikes(int new_likes)
{
	likes = new_likes;
}



//sets a new source
void Tutorial::SetSource(std::string new_source)
{
	source = new_source;
}





//plays the tutorial
void Tutorial::play()
{
	ShellExecuteA(NULL, NULL, "firefox.exe", this->GetSource().c_str(), NULL, SW_SHOWMAXIMIZED);
}


//overload the operator <<
std::ostream& operator<<(std::ostream& os, const Tutorial& t)
{
	os << t.title << "," << t.presenter << "," << t.minutes << "," << t.seconds << "," << t.likes << "," << t.source << "\n";
	return os;
}



std::vector<std::string> tokenize(const std::string& str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;

}


//overload the operator >>
std::istream& operator>>(std::istream& is, Tutorial& tut)
{
	std::string line;
	std::getline(is, line);
	std::vector<std::string> tokens;
	if (line.empty())
		return is;
	tokens = tokenize(line, ',');

	tut.SetTitle(tokens[0]);
	tut.SetPresenter(tokens[1]);
	tut.SetMinutes(std::stoi(tokens[2]));
	tut.SetSeconds(std::stoi(tokens[3]));
	tut.SetLikes(std::stoi(tokens[4]));
	tut.SetSource(tokens[5]);

	return is;


}

bool operator==(const Tutorial& t1, const Tutorial& t2)
{
	if (t1.title != t2.title)
		return false;
	if (t1.presenter != t2.presenter)
		return false;
	if (t1.minutes != t2.minutes)
		return false;
	if (t1.seconds != t2.seconds)
		return false;
	if (t1.likes != t2.likes)
		return false;
	if (t1.source != t2.source)
		return false;

	return true;//if the t1 == t2
}


