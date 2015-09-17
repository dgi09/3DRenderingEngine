#include "FileLoader.h"
#include <fstream>
#include <streambuf>

std::string FileLoader::GetAllText(std::string filePath)
{
	std::ifstream t(filePath);
	std::string vsContent((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	return vsContent;
}
