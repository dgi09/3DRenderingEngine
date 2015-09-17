#pragma once
#include "Common.h"
#include <vector>
#include "EffectFunctionality.h"
#include "BuffersCollection.h"
#include "SamplersCollection.h"
#include "TexturesCollection.h"

class EXPORT IEffectBindingSection;

class EXPORT DeviceDependableFactory;

class EXPORT EffectBinder
{
	std::vector<IEffectBindingSection*> * sections;

	BuffersCollection vsBuffers;
	SamplersCollection vsSamplers;
	TexturesCollection vsTextures;

	BuffersCollection psBuffers;
	SamplersCollection psSamplers;
	TexturesCollection psTextures;

	DeviceDependableFactory * factory;

public:

	void Init();
	void Destroy();
	void SetFactory(DeviceDependableFactory * factory);
	void SetSections(std::vector<IEffectBindingSection*> * sections);

	IEffectBindingSection * GetBindingSectionByFunctionality(EffectFunctionality func);
	void BindAllSections();
};

