#pragma once 
#include "Common.h"
#include "Color.h"
#include "TextureHandler.h"
#include "TexturePtr.h"


class EXPORT EntityBase;
class EXPORT ResourceManager;


struct EXPORT MaterialData
{
	Color diffuseColor;
	unsigned char specularIntesity;
	unsigned char specularPower;
	unsigned char emmisivePowerNorm;
	unsigned char padding1;
	unsigned int optionsMask;
	char padding2[8];
};

class EXPORT Material
{
	TextureHandler diffuseMap;
	TextureHandler bumpMap;
	MaterialData data;

	ResourceManager * resMgr;
public:

	void UseDiffuseMap(bool val);
	void SetDiffuseMap(const char * fileName);
	
	void UseBumpMap(bool val);
	void SetBumpMap(const char * fileName);

	void SetDiffuseColor(Color color);
	void SetSpecularIntesity(unsigned short val);
	void SetSpecularPower(unsigned short val);
	void SetEmmisivePower(unsigned short val);
private:
	friend class EntityBase;

	void Init(ResourceManager * mgr);
	void FreeResources();
	MaterialData * GetData();
	TexturePtr GetDiffuseTexture();
	TexturePtr GetBumpTexture();
};