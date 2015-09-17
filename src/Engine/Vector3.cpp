#include "Vector3.h"
#include <cmath>


bool Vector3::operator!=(Vector3 & vec)
{
	return !(*this == vec);
}

bool Vector3::operator==(Vector3 & vec)
{
	if(vec.x == x && vec.y == y && vec.z == z)
		return true;
	
	return false;
}

Vector3 Vector3::operator-(Vector3 & vec)
{
	return Vector3(x - vec.x,y - vec.y,z - vec.z);
}
Vector3::Vector3(float x,float y,float z) : x(x),y(y),z(z)
{

}

Vector3::Vector3()
{

}

Vector3 Vector3::operator+(Vector3 & vec)
{
	return Vector3(x + vec.x,y + vec.y,z + vec.z);
}

Vector3 Vector3::operator*(float val)
{
	return Vector3(x * val,y * val,z * val);
}

Vector3 Vector3::Normalize()
{
	float l = Lenght();
	return Vector3(x/l,y/l,z/l);
}

float Vector3::Lenght()
{
	return std::sqrt(x * x + y * y + z * z);
}


