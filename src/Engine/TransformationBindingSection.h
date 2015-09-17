#pragma once 
#include "Common.h"
#include "IEffectBindingSection.h"
#include <DirectXMath.h>
#include "ConstantBufferPtr.h"


class EXPORT DeviceDependableFactory;
class EXPORT CameraData;

class EXPORT TransformationBindingSection : public IEffectBindingSection
{

public:
	virtual EffectFunctionality GetEffectFunctionality();

	virtual void Init(DeviceDependableFactory * factory);

	void SetWorldMatrix(ConstantBufferPtr matrixBuffer);
	void SetCameraData(ConstantBufferPtr buffer);

	void Destroy();

};