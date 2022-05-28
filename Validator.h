#pragma once
#include "Tutorial.h"

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif


class ValidationException : public std::exception
{
private:
	std::string message;
public:
	explicit ValidationException(std::string& _message);
	const char* what() const NOEXCEPT override;
};

class TutValidator
{
public:
	TutValidator();

	bool validateTitle(std::string& title);
	bool validatePresenter(std::string& presenter);

	bool validateMinutes(int min);
	bool validateMinStr(std::string& min);

	bool validateSeconds(int sec);
	bool validateSecStr(std::string& sec);

	//bool validateLikes(int likes);
	bool validateLikesStr(std::string& likes);

	bool validateSource(std::string& source);

	bool validateString(const std::string& input);
	~TutValidator();

};