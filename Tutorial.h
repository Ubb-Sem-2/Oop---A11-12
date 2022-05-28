#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

/*
class Duration
{
private:
	double minutes;
	double seconds;
public:
	Duration() : minutes(0), seconds(0) {}
	Duration(double min, double sec) : minutes(min), seconds(sec) {}

	double getMinutes() const {return minutes; }
	double getSeconds() const {return seconds; }
};*/


class Tutorial
{
private:
	std::string title;
	std::string presenter;
	//Duration duration;
	int minutes;
	int seconds;
	int likes;  //nr of likes
	std::string source; // youtube link

public:
	//deafult constructor for a tutorial
	Tutorial();

	Tutorial(const std::string&, const std::string&, int minutes, int second, int, const std::string&);
	Tutorial(const Tutorial& tutorial);
	~Tutorial();

	std::string GetTitle() const;
	std::string GetPresenter() const;
	int GetMinutes() const;
	int GetSeconds() const;
	int GetLikes() const;
	std::string GetSource() const;

	friend std::ostream& operator<<(std::ostream& os, const Tutorial& t);
	friend std::istream& operator>>(std::istream& is, Tutorial& t);


	void SetTitle(std::string new_title);
	void SetPresenter(std::string new_presenter);

	void SetMinutes(int new_min);
	void SetSeconds(int new_sec);
	void SetLikes(int new_likes);
	void SetSource(std::string new_source);

	//Plays the current song: the page corresponding to the source link is opened in a browser
	void play();

	friend bool operator==(const Tutorial& t1, const Tutorial& t2);



};

