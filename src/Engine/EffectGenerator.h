#pragma once
#include "Common.h"
#include <string>
#include "EffectMask.h"
#include "Pos_Normal_Tangent_TexCoord_Layout.h"
#include "Pos_Normal_Tangent_TexCoord_BoneInfo.h"
#include "EntityEffectPtr.h"
#include "BindingSections.h"

class EXPORT DeviceDependableFactory;

class EXPORT EffectGenerator
{
	DeviceDependableFactory * factory;
	std::string vShaderPath;
	std::string pShaderPath;

	Pos_Normal_Tangent_TexCoord_Layout staticLayout;
	Pos_Normal_Tanget_TexCoord_BoneInfo animatedLayout;

	TransformationBindingSection transformationSection;

	SkinningBindingSection skinningSection;
	MaterialBindingSection materialSection;
public:
	EffectGenerator(DeviceDependableFactory * factory);
	~EffectGenerator();
	void SetVertShaderTemplatePath(const char * path);
	void SetPixelShaderTemplatePath(const char * path);
	EntityEffectPtr GenerateEffectFromMask(EFFECTMASK mask);

protected:
    std::string GenerateDefinesFromMask(EFFECTMASK mask);
	void AddBindingSectionsFromMask(EntityEffect * effect,EFFECTMASK mask);
};