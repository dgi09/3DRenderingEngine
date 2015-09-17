#pragma once 

#include "Common.h"
#include "DeviceDependable.h"
#include "DeviceDependableFactory.h"
#include "TexturePtr.h"
#include "ConstantBufferPtr.h"
#include "Vector3.h"

class EXPORT ParticleSystemEffectBinder : public DeviceDependable
{
	struct CameraVectorsChunck
	{
		Vector3 up;
		float padding1;

		Vector3 right;
		float padding2;
	};

	TexturePtr colorTexture;
	TexturePtr rtvLinearDepth;
	ID3D11RenderTargetView *  rtvColor;

	ConstantBufferPtr cameraBuffer;
	ConstantBufferPtr dataBuffer;

	ConstantBufferPtr cameraVectorsBuffer;
	CameraVectorsChunck camVectorsChunck;

public:

	void Init(DeviceDependableFactory * factory);
	void Destroy();

	void BindOM();
	void UnbindOM();

	void Bind();
	
	void SetColorTexture(TexturePtr texture);
	void SetCameraBuffer(ConstantBufferPtr buffer);
	void SetRTVLinearDepth(TexturePtr texture);
	void SetRTVColor(TexturePtr texture);
	void SetRTVColor(ID3D11RenderTargetView * rtv);
	void FillParticleData(void * data,unsigned int size);
	void SetCameraVectors(Vector3 upNormal,Vector3 rightNormal);
};