#include "GameException.h"

GameException::GameException(const std::string& error, const std::string& function, const std::string& description){
	std::stringstream s;
	s << error << " @ " << function << ": " << description;
	msg = s.str();
}

GameException::GameException(const std::string& function, const std::string& description):
	GameException { "GameException", function, description } {

}
