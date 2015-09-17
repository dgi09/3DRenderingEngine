#include "SceneDrawable.h"

BoundingSphere SceneDrawable::GetBoundingSphere()
{
	sphere.position = GetPosition();
	return sphere;
}

void SceneDrawable::SetVisible(bool val)
{
	visible = val;
}

bool SceneDrawable::IsVisible()
{
	return visible;
}
