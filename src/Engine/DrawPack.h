#pragma once 
#include "Common.h"
#include "MeshPtr.h"
#include "TextureHandler.h"


class EXPORT DrawPack 
{
public:
	DrawPack();

	TextureHandler diffuseMap;
	TextureHandler bumpMap;
};