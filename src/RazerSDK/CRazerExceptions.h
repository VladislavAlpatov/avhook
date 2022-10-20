#pragma once
#include <exception>
#include <string>
#include "../Utils/xorstr.h"

class RzDllNotFoundError : public std::exception
{
public:
	RzDllNotFoundError(const char* message) : std::exception(message) {}
	RzDllNotFoundError() : std::exception() {}
};