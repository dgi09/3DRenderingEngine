#pragma once 
#include "EffectFunctionality.h"

#define EFFECTMASK unsigned short

class EffectMaskUtil
{
public:
	static void Bind(EFFECTMASK & mask,EffectFunctionality func);
	static void Unbind(EFFECTMASK & mask,EffectFunctionality func);
	static bool IsBinded(EFFECTMASK mask,EffectFunctionality func);
};