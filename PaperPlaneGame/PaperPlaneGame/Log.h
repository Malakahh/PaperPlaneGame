#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

namespace Log
{
	void Message(const std::string message);
	void Error(const std::string message);
}
