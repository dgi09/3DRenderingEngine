#pragma  once 
#include "Common.h"

class EXPORT Vector4
{
public:
	float x,y,z,w;

	bool operator!=(Vector4 & vec);
	bool operator==(Vector4 & vec);
};