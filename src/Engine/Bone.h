#pragma once 
#include "Common.h"
#include <string>
#include <DirectXMath.h>
#include <vector>

class EXPORT Bone 
{
public:
	std::string name;
	DirectX::XMFLOAT4X4 offsetMatrix;
	DirectX::XMFLOAT4X4 transformation;

	std::vector<unsigned int> childIndexes;
};