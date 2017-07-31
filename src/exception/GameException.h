#pragma once

#include <exception>
#include <string>
#include <sstream>

class GameException : public std::exception{

	std::string msg;

protected:
						GameException(const std::string& error, const std::string& function, const std::string& description);

public:
						GameException(const std::string& function, const std::string& description);

	const char*			what() const throw(){ return msg.c_str(); };
};
