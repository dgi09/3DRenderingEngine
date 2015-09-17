#pragma once
#include "Common.h"
#include "BoundingSphere.h"
#include "Positionable.h"

class EXPORT SceneDrawable : public Positionable
{
protected:
	bool visible;
	BoundingSphere sphere;
public:
	
	BoundingSphere GetBoundingSphere();
	void SetVisible(bool val);
	bool IsVisible();
};

