#include "Scene.h"
#include "EffectMask.h"
#include "TransformationBindingSection.h"
#include "EffectPool.h"
#include "EffectGenerator.h"
#include "EffectBinder.h"
#include "EntityBase.h"
#include "DeviceDependableFactory.h"
#include "EntityEffect.h"
#include "ResourcePool.h"
#include "ResourceManager.h"
#include "StaticMeshData.h"
#include "DirectionalLight.h"
#include "IlluminationBindingSection.h"
#include "PointLight.h"
#include "AssetLoader.h"
#include "Frustrum.h"
#include "Heap.h"
#include <D3D11.h>
#include "ModelHandler.h"
#include "FileLoader.h"
#include "Pos_TexCoord_Layout.h"
#include "Vertex.h"
#include "FullScreenQuad.h"
#include "Mesh.h"
#include "Vertex.h"

Scene::Scene(SceneDXData dxData, int windowW, int windowH)
{
	this->dxData = dxData;
	SetWindowSize(windowW,windowH);
}

Scene::~Scene(void)
{
	RemoveAllEntities();
	RemoveAllDirectionLights();
	RemoveAllPointLights();

	shaderData.Destroy();
	gBuffer.Destroy();
	defferedEffect.Delete();
	blurer.Destroy();
	sample.Destroy();
	toneMapper.Destroy();

	FullScreenQuad::Destroy();



	delete factory;
	delete generator;
	delete resourceManager;

	AssetLoader::Destroy();
	Heap::Free();
}


void Scene::Init()
{
	Heap::GetPtr()->Meshes.Allocate(100);
	Heap::GetPtr()->Animations.Allocate(10);

	Heap::GetPtr()->ConstantBuffers.Allocate(100);
	Heap::GetPtr()->PixelShaders.Allocate(100);
	Heap::GetPtr()->Samplers.Allocate(100);

	Heap::GetPtr()->Skeletons.Allocate(100);
	Heap::GetPtr()->Textures.Allocate(100);

	Heap::GetPtr()->VertexShaders.Allocate(100);
	Heap::GetPtr()->EntityEffects.Allocate(100);
	Heap::GetPtr()->Models.Allocate(100);

	Heap::GetPtr()->ComputeShaders.Allocate(5);

	camerasPool.Allocate(10);
	staticEntitiesPool.Allocate(100);
	animatedEntitiesPool.Allocate(100);
	particleSystemsPool.Allocate(100);

	dirLightsPool.Allocate(4);
	pointLightsPool.Allocate(4);



	factory = new DeviceDependableFactory(dxData.device);
	generator = new EffectGenerator(factory);
	resourceManager = new ResourceManager(factory);

	AssetLoader::GetPtr()->SetFactory(factory);


	SetBackgroundColor(Color::Black());
	SetGlobalAmbient(0.2f,0.2f,0.2f,1.0f);

	activeCamera = CameraPtr(true);

	shaderData.Init(factory);


	rebindIlluminationInfoBuffer = true;
	rebindGlobalAmbient = true;

	gBuffer.SetDevice(dxData.device);
	gBuffer.Init(windowWidth,windowHeight,factory);



	generator->SetPixelShaderTemplatePath((shadersPath + "\\psGBuffer.hlsl").c_str());
	generator->SetVertShaderTemplatePath((shadersPath + "\\vsGBuffer.hlsl").c_str());

	defferedEffect = factory->CreatePixelShader();


	std::string psDeffered = FileLoader::GetAllText(shadersPath + "\\psDeffered.hlsl");
	defferedEffect.Get()->LoadFromString(psDeffered.c_str(),psDeffered.size(),"main");

	FullScreenQuad::Init(factory);
	FullScreenQuad::SetDevice(dxData.device);

	std::string vsFullScrennQuad = FileLoader::GetAllText(shadersPath + "\\vsFullScreen.hlsl");

	FullScreenQuad::SetVS(vsFullScrennQuad.c_str());



	std::string psSample = FileLoader::GetAllText(shadersPath + "\\psRTT.hlsl");


	sample.Init(factory);
	sample.SetDevice(dxData.device);
	sample.SetEffect(psSample.c_str());

	blurer.Init(factory);
	blurer.SetDevice(dxData.device);
	blurer.SetSize(windowWidth,windowHeight);

	std::string csVBlur = FileLoader::GetAllText(shadersPath + "\\csVBlur.hlsl");
	std::string csHBlur = FileLoader::GetAllText(shadersPath + "\\csHBlur.hlsl");
	blurer.SetHorizonatlBlurEffect(csHBlur.c_str());
	blurer.SetVerticalBlurEffect(csVBlur.c_str());

	hdr = factory->CreateTexture();
	bloom = factory->CreateTexture();
	bloomDownSample = factory->CreateTexture();
	bloomFullBlur = factory->CreateTexture();
	bloomVBlur = factory->CreateTexture();


	Texture * t = hdr.Get();
	t->InitTexture(windowWidth,windowHeight,RENDER_TARGET,DXGI_FORMAT_R16G16B16A16_FLOAT);

	t = bloom.Get();
	t->InitTexture(windowWidth,windowHeight,(TextureUsage)(RENDER_TARGET|UNORDERED_VIEW),DXGI_FORMAT_R16G16B16A16_FLOAT);

	t = bloomDownSample.Get();
	t->InitTexture(windowWidth/BLUR_AGGRESSION,windowHeight/BLUR_AGGRESSION,(TextureUsage)(RENDER_TARGET|UNORDERED_VIEW),DXGI_FORMAT_R16G16B16A16_FLOAT);

	t = bloomVBlur.Get();
	t->InitTexture(windowWidth/BLUR_AGGRESSION,windowHeight/BLUR_AGGRESSION,UNORDERED_VIEW,DXGI_FORMAT_R16G16B16A16_FLOAT);

	t = bloomFullBlur.Get();
	t->InitTexture(windowWidth/BLUR_AGGRESSION,windowHeight/BLUR_AGGRESSION,UNORDERED_VIEW,DXGI_FORMAT_R16G16B16A16_FLOAT);

	std::string psToneMapping = FileLoader::GetAllText(shadersPath + "\\psToneMapping.hlsl");

	toneMapper.Init(factory);
	toneMapper.SetDevice(dxData.device);
	toneMapper.SetShaderCode(psToneMapping.c_str());

	std::string csBloom = FileLoader::GetAllText(shadersPath + "\\csBloom.hlsl");
	bloomer.Init(factory);
	bloomer.SetDevice(dxData.device);
	bloomer.SetShader(csBloom.c_str());
	bloomer.SetSize(windowWidth,windowHeight);

	toneMapper.SetBloomTexture(bloomFullBlur);

	dsBinder.SetDevice(dxData.device);
	dsBinder.SetGlobalAmbientBuffer(shaderData.GetGlbobalAmbientBuffer());
	dsBinder.SetIlluminationInfoBuffer(shaderData.GetIlluminationInfoBuffer());
	dsBinder.SetPointLightBuffer(shaderData.GetPointLightsBuffer());
	dsBinder.SetDirLightsBuffer(shaderData.GetDirectionLightsBuffer());

	// Inverse view proj buffer init
	reconstrDataBuffer = factory->CreateConstantBuffer();
	ConstantBuffer * b = reconstrDataBuffer.Get();
	b->InitBuffer(sizeof(WorldRecData));

	dsBinder.SetWorldPosRecBuffer(reconstrDataBuffer);

	particleQuad = factory->CreateMesh();
	Mesh * pm = particleQuad.Get();
	ScreenSpaceVert pmVerts[4] = 
	{
		{Vector3(-1.0f,-1.0f,0.0f),0.0f,1.0f},
		{Vector3(-1.0f, 1.0f,0.0f),0.0f,0.0f},
		{Vector3( 1.0f,-1.0f,0.0f),1.0f,1.0f},
		{Vector3( 1.0f, 1.0f,0.0f),1.0f,0.0f}


	};
	pm->InitVertexBuffer(sizeof(pmVerts),sizeof(ScreenSpaceVert),pmVerts);
	pm->SetPrimitveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	std::string vsParticleSystem = FileLoader::GetAllText(shadersPath + "\\vsParticleSystem.hlsl");
	std::string psParticleSystem = FileLoader::GetAllText(shadersPath + "\\psParticleSystem.hlsl");

	Pos_TexCoord_Layout ptl;

	particleSystemEffect.Init(factory);
	particleSystemEffect.LoadVertexShaderFromString(vsParticleSystem.c_str(),vsParticleSystem.size(),&ptl);
	particleSystemEffect.LoadPixelShaderFromString(psParticleSystem.c_str(),psParticleSystem.size());

	binder.SetDevice(dxData.device);
	binder.Init(factory);
	binder.SetCameraBuffer(shaderData.GetCameraBuffer());

	InitParticleSystemsDepthAndBlendStates();
	ID3D11DeviceContext * context = nullptr;
	dxData.device->GetImmediateContext(&context);
	context->OMGetDepthStencilState(&normalDepthState,nullptr);



	particlesLinearDepth = factory->CreateTexture();
	t = particlesLinearDepth.Get();

	t->InitTexture(windowWidth,windowHeight,RENDER_TARGET,DXGI_FORMAT_R32_FLOAT);

	nontransperantFinalColor = factory->CreateTexture();
	t = nontransperantFinalColor.Get();
	t->InitTexture(windowWidth,windowHeight,RENDER_TARGET,DXGI_FORMAT_R8G8B8A8_UNORM);

	particlesFinalColor = factory->CreateTexture();
	t = particlesFinalColor.Get();

	t->InitTexture(windowWidth,windowHeight,RENDER_TARGET,DXGI_FORMAT_R8G8B8A8_UNORM);

	binder.SetRTVLinearDepth(particlesLinearDepth);
	binder.SetRTVColor(particlesFinalColor);

	std::string psFinalCombie = FileLoader::GetAllText(shadersPath + "\\psFinalCombine.hlsl");
	finalCombineEffect = factory->CreatePixelShader();
	PixelShader * psPtr = finalCombineEffect.Get();
	psPtr->LoadFromString(psFinalCombie.c_str(),psFinalCombie.size(),"main");

}


void Scene::DrawAll()
{
	activeCamera.Get()->CalcFrustrum();
	activeCamera.Get()->CalcVectors();

	SetUpShaderData();

	gBuffer.BindToOM();
	gBuffer.Clear(bgColor);


	DrawEntities();

	gBuffer.GetDiffuseTexture().Get()->GenerateMips();

	ID3D11DeviceContext * context = nullptr;
	dxData.device->GetImmediateContext(&context);


	ID3D11RenderTargetView * views[3] = {nullptr,nullptr,nullptr};
	context->OMSetRenderTargets(3,views,nullptr);

	ID3D11RenderTargetView * hdrView = hdr.Get()->GetRenderTargetPtr();
	context->OMSetRenderTargets(1,&hdrView,nullptr);

	FullScreenQuad::BindVS();

	defferedEffect.Get()->Bind();


	CameraData * camData = activeCamera.Get()->GetData();

	DirectX::XMMATRIX vM = DirectX::XMLoadFloat4x4(&camData->view);
	DirectX::XMMATRIX pM = DirectX::XMLoadFloat4x4(&camData->projection);
	DirectX::XMMATRIX vpMat = vM * pM;
	DirectX::XMVECTOR vpDet = DirectX::XMMatrixDeterminant(vpMat);

	DirectX::XMStoreFloat4x4(&reconstrData.viewProjInverse,DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&vpDet,vpMat)));

	reconstrDataBuffer.Get()->FillBuffer(&reconstrData);

	gBuffer.BindToPS(); 
	dsBinder.Bind();


	FullScreenQuad::Draw();

	gBuffer.UnbindFromPS();

	ID3D11RenderTargetView * hdrNull = nullptr;
	context->OMSetRenderTargets(1,&hdrNull,nullptr);

	bloomer.Run(hdr,bloom);

	D3D11_VIEWPORT vp;
	UINT vps = 1;
	context->RSGetViewports(&vps,&vp);

	vp.Width /= BLUR_AGGRESSION;
	vp.Height /= BLUR_AGGRESSION;
	context->RSSetViewports(1,&vp);

	sample.Run(bloom,bloomDownSample);

	blurer.RunVertical(bloomDownSample,bloomVBlur);
	blurer.RunHorizontal(bloomVBlur,bloomFullBlur);

	vp.Width = windowWidth;
	vp.Height = windowHeight;

	context->RSSetViewports(1,&vp);
	toneMapper.Run(hdr,nontransperantFinalColor);

#pragma region Draw Particles

	if(particleSystems.size() > 0)
	{

		float blendFactor[] = {0.0f,0.0f,0.0f,0.0f};

		context->OMSetBlendState(particleSystemsBlendState, blendFactor, 0xffffffff);
		context->OMSetDepthStencilState(particleSystemsDepthState,1);


		DrawParticleSystems();


		context->OMSetBlendState(nullptr,blendFactor,0xffffffff);
		context->OMSetDepthStencilState(normalDepthState,1);
	}

#pragma endregion

	FullScreenQuad::BindVS();
	finalCombineEffect.Get()->Bind();

	context->OMSetRenderTargets(1,&dxData.renderTarget,nullptr);

	ID3D11ShaderResourceView * rsv[4] = {nontransperantFinalColor.Get()->GetShaderResourcePointer(),
		particlesFinalColor.Get()->GetShaderResourcePointer(),
		gBuffer.GetDepthTexture().Get()->GetShaderResourcePointer(),
		particlesLinearDepth.Get()->GetShaderResourcePointer()};

	context->PSSetShaderResources(0,4,rsv);

	FullScreenQuad::Draw();

	ID3D11ShaderResourceView * rsvNull[4] = {nullptr,nullptr,nullptr,nullptr};

	context->PSSetShaderResources(0,4,rsvNull);

	FullScreenQuad::UnbindVS();

	dxData.swapChain->Present(0,0);
}

#pragma region STATIC_ENTITIES

StaticEntityPtr Scene::AddStaticEntity(std::string fileName,std::string meshID)
{
	ModelHandler handler = resourceManager->GetStaticModelFromFile(fileName,meshID);
	if(handler.ContainsObject())
	{
		StaticEntityPtr ptr(staticEntitiesPool.New(),&staticEntitiesPool);
		ptr.Get()->Init(handler,resourceManager,factory);
		staticEntites.push_back(ptr);
		return ptr;
	}
	else return StaticEntityPtr(true);
}

StaticEntityPtr Scene::AddStaticEntity(std::string meshID)
{
	ModelHandler handler = resourceManager->GetStaticModel(meshID);
	if(!handler.ContainsObject())
		return nullptr;
	else 
	{
		StaticEntityPtr ptr(staticEntitiesPool.New(),&staticEntitiesPool);
		StaticEntity * entity = ptr.Get();
		entity->Init(handler,resourceManager,factory);
		staticEntites.push_back(ptr);
		return ptr;
	}
}



void Scene::RemoveStaticEntity(StaticEntityPtr entity)
{
	for(std::vector<StaticEntityPtr>::iterator it = staticEntites.begin();it != staticEntites.end();++it)
	{
		if((*it) == entity)
		{
			entity.Get()->Destroy();
			staticEntitiesPool.Delete(entity.GetIndex());
			staticEntites.erase(it);
			break;

		}
	}
}

void Scene::DrawEntities()
{
	for(int i = 0;i<staticEntites.size();i++)
	{
		DrawEntity(staticEntites[i].Get());
	}

	for(int i = 0;i < animatedEntities.size(); i++)
	{
		DrawEntity(animatedEntities[i].Get());
	}
}

void Scene::RemoveAllEntities()
{
	for(int i = 0;i < staticEntites.size();i++)
	{
		staticEntites[i].Get()->Destroy();
	}

	staticEntites.clear();

	for(int i = 0;i < animatedEntities.size();i++)
	{
		animatedEntities[i].Get()->Destroy();
	}

	animatedEntities.clear();
}

#pragma endregion

#pragma region ANIMATED_ENTITIS

AnimatedEntityPtr Scene::AddAnimatedEntity(std::string fileName,std::string id)
{
	ModelHandler  mhandler = resourceManager->GetAnimatedModelFromFile(fileName,id);
	if(!mhandler.ContainsObject())
		return AnimatedEntityPtr(true);

	SkeletonHandler sHandler = resourceManager->GetSkeletonFromFile(fileName,id);


	AnimatedEntityPtr ptr(animatedEntitiesPool.New(),&animatedEntitiesPool); 
	AnimatedEntity * entity = ptr.Get();
	entity->Init(mhandler,sHandler,resourceManager,factory);
	animatedEntities.push_back(ptr);
	return ptr;
}

AnimatedEntityPtr Scene::AddAnimatedEntity(std::string id)
{
	ModelHandler mHandler = resourceManager->GetAnimatedModel(id);
	if(!mHandler.ContainsObject())
		return AnimatedEntityPtr(true);

	SkeletonHandler sHandler = resourceManager->GetSkeleton(id);

	AnimatedEntityPtr ptr(animatedEntitiesPool.New(),&animatedEntitiesPool); 
	AnimatedEntity * entity = ptr.Get();
	entity->Init(mHandler,sHandler,resourceManager,factory);
	animatedEntities.push_back(ptr);
	return ptr;
}


void Scene::RemoveAnimatedEntity(AnimatedEntityPtr entity)
{
	for(std::vector<AnimatedEntityPtr>::iterator it = animatedEntities.begin();it != animatedEntities.end();++it)
	{
		if((*it) == entity)
		{
			entity.Get()->Destroy();
			animatedEntitiesPool.Delete(entity.GetIndex());
			animatedEntities.erase(it);
			break;
		}
	}
}
#pragma endregion

#pragma region PARTICLE_SYSTEMS

ParticleSystemPtr Scene::AddParticleSystem()
{
	ParticleSystemPtr ptr(particleSystemsPool.New(),&particleSystemsPool);
	ParticleSystem * system = ptr.Get();
	system->Init(particleQuad,resourceManager);

	particleSystems.push_back(ptr);
	return ptr;
}

void Scene::RemoveParticleSystem(ParticleSystemPtr system)
{
	for(std::vector<ParticleSystemPtr>::iterator it = particleSystems.begin();it != particleSystems.end();++it)
	{
		if(system == *it)
		{
			particleSystemsPool.Delete(system.GetIndex());
			particleSystems.erase(it);
			break;
		}
	}
}


#pragma endregion

void Scene::DrawEntity(EntityBase * entity)
{
	Frustrum * f = activeCamera.Get()->GetFrustrum();

	//if(f->IsSphereIn(entity->GetBoundingSphere()))
	//{
	EFFECTMASK mask = entity->GetEffectMask();
	EntityEffectPtr effect;
	if(effectPool.ObjectExist(mask))
		effect = effectPool.GetResource(mask);
	else
	{
		effect = generator->GenerateEffectFromMask(mask);
		effectPool.AddObject(mask,effect);
	}

	EntityEffect * rawEffect = effect.Get();
	rawEffect->Apply();
	BindSceneDataToEffect(rawEffect);
	entity->Draw(rawEffect->GetBinder());
	//}

}

#pragma region CAMERAS

CameraPtr Scene::AddCamera()
{
	CameraPtr ptr(camerasPool.New(),&camerasPool);

	Camera * cam = ptr.Get();
	cam->Init();
	cam->SetAspectRatio((float)windowWidth/(float)windowHeight);

	return ptr;
}

void Scene::RemoveCamera(CameraPtr camera)
{
	camerasPool.Delete(camera.GetIndex());
}

void Scene::SetActiveCamera(CameraPtr camera)
{
	if(!camera.IsNull())
		activeCamera = camera;
}


#pragma endregion

#pragma region LIGHTS

void Scene::SetGlobalAmbient(float r,float g,float b,float a)
{
	Vector4 vec;
	vec.x = r;
	vec.y = g;
	vec.z = b;
	vec.w = a;

	if(vec != globalAmbient)
	{
		globalAmbient = vec;
		rebindGlobalAmbient = true;
	}
}

DirectionalLightPtr Scene::AddDirectionalLight()
{
	if(dirLights.size() + 1 <= MAX_DIRECTIONAL_LIGHTS)
	{
		rebindIlluminationInfoBuffer = true;

		DirectionalLightPtr ptr(dirLightsPool.New(),&dirLightsPool);
		DirectionalLight * light = ptr.Get();
		DLData * data = &dirLightsData[dirLights.size()];
		light->SetData(data);
		light->Init();
		dirLights.push_back(ptr);
		return ptr;
	}
	else return DirectionalLightPtr(true);
}

void Scene::RemoveDirectionLight(DirectionalLightPtr light)
{

	rebindIlluminationInfoBuffer = true;

	if(light == dirLights.back())
	{
		dirLights.pop_back();
		return;
	}


	for(int i = 0;i < dirLights.size();i++)
	{
		if(dirLights[i] == light)
		{
			std::swap(dirLightsData[i],dirLightsData[dirLights.size()-1]);
			std::swap(dirLights[i],dirLights[dirLights.size()-1]);
			dirLights.pop_back();
			dirLights[i].Get()->SetData(&dirLightsData[i]);
			dirLightsPool.Delete(light.GetIndex());
			break;
		}
	}
}

void Scene::RemoveAllDirectionLights()
{
	rebindIlluminationInfoBuffer = true;
	dirLights.clear();
}

PointLightPtr Scene::AddPointLight()
{
	if(pointLights.size() + 1 <= MAX_POINT_LIGHTS)
	{
		rebindIlluminationInfoBuffer = true;

		PointLightPtr ptr(pointLightsPool.New(),&pointLightsPool);
		PointLight * light = ptr.Get();
		light->SetData(&pointLightsData[pointLights.size()]);
		light->Init();

		pointLights.push_back(ptr);
		return ptr;
	}
	else return PointLightPtr(true);
}

void Scene::RemovePointLight(PointLightPtr light)
{
	rebindIlluminationInfoBuffer = true;

	if(light == pointLights.back())
	{
		pointLights.pop_back();
		return;
	}


	for(int i = 0;i < pointLights.size();i++)
	{
		if(pointLights[i] == light)
		{
			std::swap(pointLightsData[i],pointLightsData[pointLights.size()-1]);
			std::swap(pointLights[i],pointLights[pointLights.size()-1]);
			pointLights.pop_back();
			pointLights[i].Get()->SetData(&pointLightsData[i]);
			pointLightsPool.Delete(light.GetIndex());
			break;
		}
	}
}

void Scene::RemoveAllPointLights()
{
	rebindIlluminationInfoBuffer = true;
	pointLights.clear();
}

#pragma endregion


void Scene::SetWindowSize(int w,int h)
{
	windowHeight = h;
	windowWidth = w;
}
void Scene::BindSceneDataToEffect(EntityEffect * effect)
{
	EffectBinder * binder = effect->GetBinder();
	EFFECTMASK mask = effect->GetMask();


	if(EffectMaskUtil::IsBinded(mask,TRANSFORMATION))
	{
		TransformationBindingSection * transforms = (TransformationBindingSection*)binder->GetBindingSectionByFunctionality(TRANSFORMATION);		
		transforms->SetCameraData(shaderData.GetCameraBuffer());
	}

	/*if(EffectMaskUtil::IsBinded(mask,ILLUMINATION))
	{
	IlluminationBindingSection * illumination = (IlluminationBindingSection*)binder->GetBindingSectionByFunctionality(ILLUMINATION);

	illumination->SetGlobalAmbient(shaderData.GetGlbobalAmbientBuffer());

	shaderData.FillIlluminationInfoBuffer(&illuminationInfo);
	illumination->SetIlluminationInfo(shaderData.GetIlluminationInfoBuffer());

	illumination->SetDirLights(shaderData.GetDirectionLightsBuffer());

	illumination->SetPointLight(shaderData.GetPointLightsBuffer());
	}*/
}

ResourceManager * Scene::GetResourceManager()
{
	return resourceManager;
}


void Scene::SetShadersPath(std::string path)
{
	shadersPath = path;

}

void Scene::SetUpShaderData()
{
	Camera * activeCam = activeCamera.Get();
	if(activeCam->IsChanged())
	{
		CameraData transposed = *activeCam->GetData();
		DirectX::XMStoreFloat4x4(&transposed.view,DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&transposed.view)));
		DirectX::XMStoreFloat4x4(&transposed.projection,DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&transposed.projection)));

		shaderData.FillCameraBuffer(&transposed);
	}

	if(activeCam->IsChanged() || rebindIlluminationInfoBuffer)
	{
		illuminationInfo.camPosition = activeCam->GetPosition();
		illuminationInfo.numberOfDirectionalLights = dirLights.size();
		illuminationInfo.numberOfPointLights = pointLights.size();
		shaderData.FillIlluminationInfoBuffer(&illuminationInfo);
		rebindIlluminationInfoBuffer = false;
	}


	if(activeCam->isChanged)
		activeCam->ChangeApplied();

	if(rebindGlobalAmbient)
	{
		shaderData.FillGlobalAmbientBuffer(globalAmbient);
		rebindGlobalAmbient = false;
	}


	if(illuminationInfo.numberOfDirectionalLights > 0)
	{
		bool fill = false;
		for(int i = 0;i < dirLights.size();i++)
		{
			if(dirLights[i].Get()->IsChanged())
			{
				fill = true;
				dirLights[i].Get()->ChangeApplied();
			}
		}

		if(fill)
			shaderData.FillDirectionLightsBuffer(dirLightsData);
	}

	if(illuminationInfo.numberOfPointLights > 0)
	{
		bool fill = false;
		for(int i = 0;i < pointLights.size();i++)
		{
			if(pointLights[i].Get()->IsChanged())
			{
				fill = true;
				pointLights[i].Get()->ChangeApplied();
			}
		}

		if(fill)
			shaderData.FillPointLightsBuffer(pointLightsData);
	}
}

void Scene::SetBackgroundColor(Color color)
{
	bgColor = color;
}

void Scene::DrawParticleSystems()
{

	particleSystemEffect.Apply();
	binder.BindOM();

	Camera * cam = activeCamera.Get();
	binder.SetCameraVectors(cam->GetUpNormal(),cam->GetRightNormal());

	for(unsigned int i = 0;i < particleSystems.size();i++)
	{
		ParticleSystem * ps = particleSystems[i].Get();
		ps->Draw(&binder);
	}

	binder.UnbindOM();
}

void Scene::InitParticleSystemsDepthAndBlendStates()
{
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription,sizeof(D3D11_BLEND_DESC));

	blendStateDescription.RenderTarget[0].BlendEnable = true;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	dxData.device->CreateBlendState(&blendStateDescription,&particleSystemsBlendState);

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	dxData.device->CreateDepthStencilState(&depthStencilDesc,&particleSystemsDepthState);
}

















