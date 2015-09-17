#include "PointLight.h"

void PointLight::SetPosition(float x,float y,float z)
{
	Vector3 p;
	p.x = x;
	p.y = y;
	p.z = z;

	SetPosition(p);
}

void PointLight::SetPosition(Vector3 position)
{
	if(data->position != position)
	{
		data->position = position;
		isChanged = true;
	}

}

void PointLight::SetDiffuse(Vector4 diffuse)
{
	if(data->diffuse != diffuse)
	{
		data->diffuse = diffuse;
		isChanged = true;
	}

}

void PointLight::SetDiffuse(float r,float g,float b,float a)
{
	Vector4 d;
	d.x = r;
	d.y = g;
	d.z = b;
	d.w = a;

	SetDiffuse(d);
}


void PointLight::SetRange(float val)
{
	if(val != 0)
	{
		if(data->range != 1/val)
		{
			data->range = 1/val;
			isChanged = true;
		}

	}

}

void PointLight::Init()
{
	SetPosition(0.0f,0.0f,0.0f);
	SetDiffuse(0.3f,0.3f,0.3f,1.0f);
	isChanged = true;
}

bool PointLight::IsChanged()
{
	return isChanged;
}

void PointLight::ChangeApplied()
{
	isChanged = false;
}

void PointLight::SetData(PLData * data)
{
	this->data = data;
}
