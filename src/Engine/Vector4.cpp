#include "Vector4.h"

bool Vector4::operator!=(Vector4 & vec)
{
	return !(*this == vec);
}

bool Vector4::operator==(Vector4 & vec)
{
	if(x == vec.x && y == vec.y && z == vec.z && w == vec.w)
		return true;
	else return false;
}
