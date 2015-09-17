#include "Material.h"
#include "ResourceManager.h"
#include "EffectMask.h"

void Material::UseDiffuseMap(bool val)
{
	if(val)
	{
		if((data.optionsMask & 1) != 1)
			data.optionsMask |= 1;
	}
	else 
	{
		if((data.optionsMask & 1) == 1)
			data.optionsMask ^= 1;
	}
}

void Material::SetDiffuseMap(const char * fileName)
{
	diffuseMap = resMgr->GetTexture(fileName);
}

void Material::UseBumpMap(bool val)
{
	if(val)
		data.optionsMask |= (1 << 1);
	else 
		data.optionsMask |= (1 << 1);
}

void Material::SetBumpMap(const char * fileName)
{
	bumpMap = resMgr->GetTexture(fileName);
}

void Material::SetDiffuseColor(Color color)
{
	data.diffuseColor = color;
}

void Material::SetSpecularIntesity(unsigned short val)
{
	data.specularIntesity = (unsigned char)val;
}

void Material::SetSpecularPower(unsigned short val)
{
	data.specularPower = (unsigned char)val;
}

void Material::SetEmmisivePower(unsigned short val)
{
	data.emmisivePowerNorm = (unsigned char)val;
}

void Material::Init(ResourceManager * mgr)
{
	resMgr = mgr;
	data.optionsMask = 0;

	SetDiffuseColor(Color::White());
	
	SetEmmisivePower(1);
	SetSpecularPower(3);
	SetSpecularIntesity(3);
	
	diffuseMap = TextureHandler(false);
	bumpMap = TextureHandler(false);
}

void Material::FreeResources()
{
	diffuseMap.Destroy();
	bumpMap.Destroy();
}

MaterialData * Material::GetData()
{
	return &data;
}

TexturePtr Material::GetDiffuseTexture()
{
	return diffuseMap.Get();
}

TexturePtr Material::GetBumpTexture()
{
	return bumpMap.Get();
}
