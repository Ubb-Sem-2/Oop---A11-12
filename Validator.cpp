#pragma once
#include "Validator.h"

ValidationException::ValidationException(std::string& _message) : message(_message)
{
}

const char* ValidationException::what() const NOEXCEPT
{
	return message.c_str();
}

TutValidator::TutValidator()
{
}


bool TutValidator::validateString(const std::string& input)
{
	for (char i : input)
	{
		if (isdigit(i) != false)
			return false;
	}
	return true;
}


bool TutValidator::validateMinStr(std::string& min)
{
	std::string errors;
	if (min.empty())
		errors += std::string("The minutes input is empty");
	if (min.find_first_not_of("0123456789") != std::string::npos)
		errors += std::string("The minutes input has non-digit characters!");
	if (!errors.empty())
		throw ValidationException(errors);
}


bool TutValidator::validateMinutes(int min)
{
	std::string errors;
	if (min < 0 || min > 60)
		errors += std::string("Not valid minutes");

	if (!errors.empty())
		throw ValidationException(errors);
}


bool TutValidator::validateSecStr(std::string& sec)
{
	std::string errors;
	if (sec.empty())
		errors += std::string("The seconds input is empty");
	if (sec.find_first_not_of("0123456789") != std::string::npos)
		errors += std::string("The seconds inpus has non-digit characters");
	if (!errors.empty())
		throw ValidationException(errors);
}


bool TutValidator::validateSeconds(int sec)
{
	std::string errors;
	if (sec < 0 || sec > 60)
		errors += std::string("Not valid seconds");

	if (!errors.empty())
		throw ValidationException(errors);

}


bool TutValidator::validateLikesStr(std::string& likes)
{
	std::string errors;
	if (likes.empty())
		errors += std::string("The likes input is empty");
	if (likes.find_first_not_of("0123456789") != std::string::npos)
		errors += std::string("The likes inpus has non-digit characters");
	if (!errors.empty())
		throw ValidationException(errors);

}

bool TutValidator::validateSource(std::string& source)
{
	std::string errors;
	if (source.length() == 0)
		errors += std::string("The input source is empty");
	if (!errors.empty())
		throw ValidationException(errors);

}

bool TutValidator::validateTitle(std::string& title)
{
	std::string errors;
	if (title.length() == 0)
		errors += std::string("The title input is empty");
	if (!errors.empty())
		throw ValidationException(errors);
}

bool TutValidator::validatePresenter(std::string& presenter)
{
	std::string errors;
	if (presenter.length() == 0)
		errors += std::string("The presenter input is empty");
	if (!errors.empty())
		throw ValidationException(errors);
}

TutValidator::~TutValidator()
{
}