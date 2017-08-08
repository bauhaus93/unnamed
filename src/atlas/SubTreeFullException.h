#pragma once

#include <exception>

class SubTreeFullException : public std::exception {

public:
                    SubTreeFullException() { };

    const char*		what() const throw() { return "Subtree is full"; };
};
