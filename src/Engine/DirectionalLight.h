#pragma once
#include "Common.h"
#include "Vector3.h"
#include "Vector4.h"
#include "DLData.h"
#include <DirectXMath.h>
#include "TexturePtr.h"

class EXPORT Scene;
class EXPORT DeviceDependableFactory;


class EXPORT DirectionalLight
{
	DLData * data;
	bool isChanged;
	TexturePtr shadowMapPtr;
public:

	void SetDirection(Vector3 dir);
	void SetDirection(float x,float y,float z);
	void SetDiffuseColor(float r,float g,float b,float a);
	void SetDiffuseColor(Vector4 color);
private:
	friend class Scene;
	void Init();
	bool IsChanged();
	void ChangeApplied();
	void SetData(DLData * data);

	DirectX::XMFLOAT4X4 GetViewProjMatrix();

	void InitShadowMap(DeviceDependableFactory * factory);
	TexturePtr GetShadowMap();
};

