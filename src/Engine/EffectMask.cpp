#include "EffectMask.h"

void EffectMaskUtil::Bind(EFFECTMASK & mask,EffectFunctionality func)
{
	if(IsBinded(mask,func) == false)
	{
		mask |= (unsigned short)func;
	}
}

void EffectMaskUtil::Unbind(EFFECTMASK & mask,EffectFunctionality func)
{
	if(IsBinded(mask,func))
	{
		mask ^= (unsigned short)func;
	}
}

bool EffectMaskUtil::IsBinded(EFFECTMASK mask,EffectFunctionality func)
{
	unsigned short f = (unsigned short)func;
    unsigned short res = mask & f;
	if(res == f)
		return true;
	else return false;
}
