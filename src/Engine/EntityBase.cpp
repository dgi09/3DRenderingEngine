#include "EntityBase.h"
#include "BindingSections.h"
#include <DirectXMath.h>
#include "EffectBinder.h"
#include "Mesh.h"
#include "DeviceDependableFactory.h"
#include "ResourceManager.h"

#include "Vertex.h"
#include <cmath>
#include "DrawPack.h"
#include "MaterialBindingSection.h"

using namespace DirectX;


EFFECTMASK EntityBase::GetEffectMask()
{
	return effectMask;
}

void EntityBase::BindEntityData(EffectBinder * binder)
{
	TransformationBindingSection * transforms =(TransformationBindingSection*)binder->GetBindingSectionByFunctionality(TRANSFORMATION);
	transforms->SetWorldMatrix(shaderData.GetWorldMatrixBuffer());

}

void EntityBase::SetUpShaderData()
{
	if(isPositionChanged || isRotationChanged || isScaleChanged)
	{
		XMFLOAT3 rotRad;
		rotRad.x = XMConvertToRadians(rotation.x);
		rotRad.y = XMConvertToRadians(rotation.y);
		rotRad.z = XMConvertToRadians(rotation.z);

		XMVECTOR R = XMLoadFloat3((XMFLOAT3*)&rotRad);
		XMVECTOR S = XMLoadFloat3((XMFLOAT3*)&scale);

		XMMATRIX mT = XMMatrixTranslation(position.x,position.y,position.z);
		XMMATRIX mR = XMMatrixRotationRollPitchYawFromVector(R);
		XMMATRIX mS = XMMatrixScalingFromVector(S);

		XMMATRIX res =  XMMatrixTranspose(mS * mR * mT);
		XMStoreFloat4x4(&data.worldMatrix,res);

		shaderData.FillWorldMatrixBuffer(data.worldMatrix);

		isPositionChanged = false;
		isRotationChanged = false;
		isScaleChanged = false;
	}
}

void EntityBase::Draw(EffectBinder * binder)
{

}




void EntityBase::Illuminate(bool val)
{
	if(val)
	{
		EffectMaskUtil::Bind(effectMask,ILLUMINATION);
	}
	else 
	{
		EffectMaskUtil::Unbind(effectMask,ILLUMINATION);
	}
}

void EntityBase::Init(ModelHandler model,ResourceManager * resMgr, DeviceDependableFactory * factory)
{
	Positionable::Positionable();
	Rotateable::Rotateable();
	Scaleable::Scaleable();


	this->modelHandler = model;
	this->resMgr = resMgr;

	materials.resize(model.Get().Get()->GetNumberOfMeshes());

	for(unsigned int i = 0;i < materials.size();i++)
	{
		materials[i].Init(resMgr);
	}

	BuildBoundingSphere();

	shaderData.Init(factory);

	effectMask = 0;
	EffectMaskUtil::Bind(effectMask,TRANSFORMATION);
	EffectMaskUtil::Bind(effectMask,MATERIAL);

	SetVisible(true);

	Illuminate(false);

}

void EntityBase::Destroy()
{

	for(unsigned int i = 0;i < materials.size();i++)
	{
		materials[i].FreeResources();
	}

	shaderData.Destroy();
	modelHandler.Destroy();

	resMgr = nullptr;
}



void EntityBase::BuildBoundingSphere()
{
	float maxRadius = 0.0f;
	Model * model = modelHandler.Get().Get();

	for(unsigned int i = 0;i < model->GetNumberOfMeshes();i++)
	{
		
		Mesh * mesh = model->GetMeshAt(i).Get();
		Vector3 * pos = mesh->GetPoistions();

		for(int i = 0;i < mesh->GetNumberOfVerts();i++)
		{
			float rad = std::sqrt(pos[i].x * pos[i].x + pos[i].y * pos[i].y + pos[i].z + pos[i].z);
			if(rad > maxRadius)
			{
				maxRadius = rad;
			}
		}

	}

	sphere.radius = maxRadius;
}

void EntityBase::BindMaterialData(EffectBinder * binder, Material & mat)
{
	if(EffectMaskUtil::IsBinded(effectMask,MATERIAL))
	{
		MaterialBindingSection * section = (MaterialBindingSection*)binder->GetBindingSectionByFunctionality(MATERIAL);
		section->SetDiffuseMap(mat.GetDiffuseTexture());
		section->SetBumpMap(mat.GetBumpTexture());

		section->SetMaterialData(mat.GetData());
	}
}


Material * EntityBase::GetMaterial(unsigned int subset)
{
	return &materials[subset];
}

