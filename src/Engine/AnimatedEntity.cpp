#include "AnimatedEntity.h"
#include "Skeleton.h"
#include "SkeletonHandler.h"
#include "EffectBinder.h"
#include "SkinningBindingSection.h"
#include "BoneAnimationData.h"
#include "ResourceManager.h"
#include "AnimationHandler.h"
#include "Mesh.h"
#include "Vertex.h"
#include "DeviceDependableFactory.h"
#include "ConstantBuffer.h"

void AnimatedEntity::Draw(EffectBinder * binder)
{
	SetUpShaderData();

	BindAnimationData(binder);
	BindEntityData(binder);

	Model * model = modelHandler.Get().Get();

	for(unsigned int i = 0;i < model->GetNumberOfMeshes();i++)
	{
		Material mat = materials[i];
		BindMaterialData(binder,mat);
		binder->BindAllSections();


		MeshPtr ptr = model->GetMeshAt(i);
		Mesh * mesh = ptr.Get();
		mesh->DrawIndexed();
	}

}


void AnimatedEntity::BindAnimationData(EffectBinder * binder)
{
	if(currentAnimController == nullptr)
		palleteBuffer.Get()->FillBuffer(&bindPosePallete.matrixes);
	else 
		palleteBuffer.Get()->FillBuffer(&currentAnimController->GetData().matrixes);

	SkinningBindingSection * skinning = (SkinningBindingSection*)binder->GetBindingSectionByFunctionality(SKINNING);
	skinning->BindPallete(palleteBuffer);
}

void AnimatedEntity::FillBindPosePallete(unsigned int boneIndex,DirectX::XMFLOAT4X4 & parent)
{
	DirectX::XMMATRIX animMatrix;
	DirectX::XMFLOAT4X4 animMatData;


	Skeleton * skeleton = skeletonHandler.Get().Get();

	
    animMatData = skeleton->bones[boneIndex].transformation;
	
	

	animMatrix = DirectX::XMLoadFloat4x4(&animMatData);

	DirectX::XMMATRIX pMatrix = XMLoadFloat4x4(&parent);
	DirectX::XMMATRIX gInverse = XMLoadFloat4x4(&skeleton->globalInverse);

	DirectX::XMMATRIX globalTranform = animMatrix * pMatrix;


	DirectX::XMMATRIX offSet = XMLoadFloat4x4(&skeleton->bones[boneIndex].offsetMatrix);
	DirectX::XMMATRIX final =  offSet * globalTranform *  gInverse;

	//final *= skeleton->globalInverse;
	DirectX::XMFLOAT4X4 fin;
	DirectX::XMStoreFloat4x4(&bindPosePallete.matrixes[boneIndex],XMMatrixTranspose(final));
	
	DirectX::XMFLOAT4X4 gt;
	DirectX::XMStoreFloat4x4(&gt,globalTranform);
	for(int i = 0;i<skeleton->bones[boneIndex].childIndexes.size();i++)
	{
		FillBindPosePallete(skeleton->bones[boneIndex].childIndexes[i],gt);
	}
}


AnimationController * AnimatedEntity::LoadAnimationFromFile(std::string fileName,std::string id)
{
	AnimationHandler handler = resMgr->GetAnimationFromFile(fileName,id);
	AnimationController controller;
	controller.Init(skeletonHandler.Get(),handler);

	animations.push_back(controller);
	return &animations[animations.size()-1];
}


void AnimatedEntity::Init(ModelHandler model,SkeletonHandler skeleton,ResourceManager * resMgr, DeviceDependableFactory * factory)
{
	EntityBase::Init(model,resMgr, factory);

	this->skeletonHandler = skeleton;


	palleteBuffer = factory->CreateConstantBuffer();
	ConstantBuffer * buffer = palleteBuffer.Get();
	buffer->InitBuffer(sizeof(DirectX::XMFLOAT4X4) * MAX_BONES);

	currentAnimController = nullptr;

	DirectX::XMFLOAT4X4 id;
	DirectX::XMStoreFloat4x4(&id,DirectX::XMMatrixIdentity());
	FillBindPosePallete(0,id);

	EffectMaskUtil::Bind(effectMask,SKINNING);
}

void AnimatedEntity::Destroy()
{
	for(int i = 0;i<animations.size();i++)
	{
		animations[i].Destroy();
	}

	palleteBuffer.Delete();
	skeletonHandler.Destroy();

	EntityBase::Destroy();
}

void AnimatedEntity::SetCurrentAnimationController(AnimationController * controller)
{
	currentAnimController = controller;
}