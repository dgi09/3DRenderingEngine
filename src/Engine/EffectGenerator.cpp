#include "EffectGenerator.h"
#include "EffectMask.h"
#include "BindingSections.h"
#include "EntityEffect.h"
#include "DeviceDependableFactory.h"
#include "Heap.h"
#include "FileLoader.h"

EffectGenerator::EffectGenerator(DeviceDependableFactory * factory)
{
	this->factory = factory;
	transformationSection.Init(factory);
	
	skinningSection.Init(factory);

	materialSection.Init(factory);
}

void EffectGenerator::SetVertShaderTemplatePath(const char * path)
{
	vShaderPath = path;
}

void EffectGenerator::SetPixelShaderTemplatePath(const char * path)
{
	pShaderPath = path;
}

EntityEffectPtr EffectGenerator::GenerateEffectFromMask(EFFECTMASK mask)
{
	EntityEffectPtr ptr(Heap::GetPtr()->EntityEffects.New());

	EntityEffect * effect = ptr.Get();
	effect->Init(factory);
	effect->SetMask(mask);


	std::string vsContent = FileLoader::GetAllText(vShaderPath);

	std::string psContent = FileLoader::GetAllText(pShaderPath);


	std::string defines = GenerateDefinesFromMask(mask);
	std::string finalVSContent = defines + vsContent;
	std::string finalPSContent = defines + psContent;

	IInputLayout * layout;
	if(EffectMaskUtil::IsBinded(mask,SKINNING))
		layout = &animatedLayout;
	else layout = &staticLayout;

	effect->LoadVertexShaderFromString(finalVSContent.c_str(),finalVSContent.size(),layout);

	effect->LoadPixelShaderFromString(finalPSContent.c_str(),finalPSContent.size());

	AddBindingSectionsFromMask(effect,mask);

	effect->SetUpBinder();
	
	return ptr;
}

std::string EffectGenerator::GenerateDefinesFromMask(EFFECTMASK mask)
{
	std::string defs = "";
	if(EffectMaskUtil::IsBinded(mask,TRANSFORMATION))
	{
		defs += "#define TRANSFORMATION \n";
	}


	if(EffectMaskUtil::IsBinded(mask,MATERIAL))
	{
		defs += "#define MATERIAL \n";
	}

	if(EffectMaskUtil::IsBinded(mask,ILLUMINATION))
	{
		defs += "#define ILLUMINATION \n";
	}
	
	if(EffectMaskUtil::IsBinded(mask,SKINNING))
	{
		defs += "#define SKINNING \n";
	}

	return defs;
}

void EffectGenerator::AddBindingSectionsFromMask(EntityEffect * effect,EFFECTMASK mask)
{
	if(EffectMaskUtil::IsBinded(mask,TRANSFORMATION))
	{
		effect->AddBindingSection(&transformationSection);
	}



	if(EffectMaskUtil::IsBinded(mask,MATERIAL))
	{
		effect->AddBindingSection(&materialSection);
	}

	if(EffectMaskUtil::IsBinded(mask,SKINNING))
	{
		effect->AddBindingSection(&skinningSection);
	}

}

EffectGenerator::~EffectGenerator()
{
	transformationSection.Destroy();
	skinningSection.Destroy();

	materialSection.Destroy();
}
