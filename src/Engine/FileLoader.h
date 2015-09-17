#pragma once 
#include "Common.h"
#include <string>

class EXPORT FileLoader 
{
public:
	static std::string GetAllText(std::string filePath);
};