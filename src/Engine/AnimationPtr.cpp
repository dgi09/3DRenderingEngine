#include "AnimationPtr.h"
#include "Animation.h"
#include "Heap.h"

AnimationPtr::AnimationPtr(unsigned int index) : HeapPtr(index)
{
	
}

AnimationPtr::AnimationPtr()
{

}

AnimationPtr::AnimationPtr(bool isNull) : HeapPtr(isNull)
{

}

Animation * AnimationPtr::Get()
{
	return Heap::GetPtr()->Animations.Get(index);
}

void AnimationPtr::Delete()
{
	Heap::GetPtr()->Animations.Get(index)->Destroy();
	Heap::GetPtr()->Animations.Delete(index);
}
