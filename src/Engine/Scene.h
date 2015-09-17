#pragma once
#include "Common.h"
#include <vector>
#include <string>
#include "IlluminationInfo.h"
#include "Vector4.h"
#include "ObjectPoolPattern_EntityEffect.h"
#include "SceneObjectPtr.h"
#include "ObjectPool.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "PLData.h"
#include "DLData.h"
#include "Camera.h"
#include "StaticEntity.h"
#include "AnimatedEntity.h"
#include "Constants.h"
#include "ResourcePool.h"
#include "SceneShaderData.h"
#include "SceneDXData.h"
#include "GBuffer.h"
#include "Effect.h"
#include "MeshPtr.h"
#include "DefferedShaderBinder.h"
#include "Color.h"
#include "Blur.h"
#include "Sample.h"
#include "Bloom.h"
#include "ToneMapper.h"
#include "ParticleSystem.h"
#include "ParticleSystemEffectBinder.h"


class EXPORT DeviceDependableFactory;
class EXPORT EffectGenerator;
class EXPORT ResourceManager;
class EXPORT AnimatedMeshData;
class EXPORT StaticMeshData;

#define CameraPtr SceneObjectPtr<Camera>
#define StaticEntityPtr SceneObjectPtr<StaticEntity>
#define AnimatedEntityPtr SceneObjectPtr<AnimatedEntity>
#define DirectionalLightPtr SceneObjectPtr<DirectionalLight>
#define PointLightPtr SceneObjectPtr<PointLight>
#define ParticleSystemPtr SceneObjectPtr<ParticleSystem>


#define BLUR_AGGRESSION 4

class EXPORT Scene
{

	SceneDXData dxData;
	ID3D11DepthStencilState * normalDepthState;

	GBuffer gBuffer;

	struct WorldRecData
	{
		DirectX::XMFLOAT4X4 viewProjInverse;
	};

	WorldRecData reconstrData;
	ConstantBufferPtr reconstrDataBuffer;

	PixelShaderPtr defferedEffect;
	PixelShaderPtr finalCombineEffect;

	DefferedShaderBinder dsBinder;

	DeviceDependableFactory * factory;
	EffectGenerator * generator;

	ObjectPoolPattern_EntityEffect<EFFECTMASK> effectPool;

	ResourceManager * resourceManager;

	std::vector<StaticEntityPtr> staticEntites;
	std::vector<AnimatedEntityPtr> animatedEntities;
	std::vector<ParticleSystemPtr> particleSystems;


	ObjectPool<AnimatedEntity> animatedEntitiesPool;
	ObjectPool<StaticEntity> staticEntitiesPool;
	ObjectPool<ParticleSystem> particleSystemsPool;


	SceneShaderData shaderData;

	int windowWidth;
	int windowHeight;

	ObjectPool<Camera> camerasPool;
	CameraPtr activeCamera;

	Vector4 globalAmbient;
	bool rebindGlobalAmbient;

	IlluminationInfo illuminationInfo;
	bool rebindIlluminationInfoBuffer;


	std::vector<DirectionalLightPtr> dirLights;
	ObjectPool<DirectionalLight> dirLightsPool;
	DLData dirLightsData[MAX_DIRECTIONAL_LIGHTS];

	std::vector<PointLightPtr> pointLights;
	ObjectPool<PointLight> pointLightsPool;
	PLData pointLightsData[MAX_POINT_LIGHTS];

	


	std::string shadersPath;

	Color bgColor;
	Blur blurer;
	Sample sample;
	Bloom bloomer;
	ToneMapper toneMapper;

	TexturePtr hdr;
	TexturePtr bloom;
	TexturePtr bloomDownSample;
	TexturePtr bloomVBlur;
	TexturePtr bloomFullBlur;
	TexturePtr particlesLinearDepth;
	TexturePtr nontransperantFinalColor;
	TexturePtr particlesFinalColor;

	MeshPtr particleQuad;
	Effect particleSystemEffect;
	ParticleSystemEffectBinder binder;
	ID3D11BlendState * particleSystemsBlendState;
	ID3D11DepthStencilState * particleSystemsDepthState;
	


public:
	Scene(SceneDXData dxData, int windowW, int windowH);
	~Scene(void);


	void Init();

	

	void SetShadersPath(std::string path);

	ResourceManager * GetResourceManager();

#pragma region STATIC_ENTITIES

	StaticEntityPtr AddStaticEntity(std::string fileName,std::string meshID);
	StaticEntityPtr AddStaticEntity(std::string meshID);

	void RemoveStaticEntity(StaticEntityPtr entity);
	
#pragma endregion

#pragma region ANIMATED_ENTITIES

	AnimatedEntityPtr AddAnimatedEntity(std::string fileName,std::string id);
	AnimatedEntityPtr AddAnimatedEntity(std::string id);

	void RemoveAnimatedEntity(AnimatedEntityPtr entity);

#pragma endregion

	void RemoveAllEntities();
	
#pragma region PARTICLE_SYSTEMS
	ParticleSystemPtr AddParticleSystem();
	void RemoveParticleSystem(ParticleSystemPtr system);
#pragma endregion

#pragma region CAMERAS

	CameraPtr AddCamera();
	void RemoveCamera(CameraPtr camera);
	void SetActiveCamera(CameraPtr camera);
#pragma endregion

#pragma region LIGHTS

	void SetGlobalAmbient(float r,float g,float b,float a);

	DirectionalLightPtr AddDirectionalLight();
	void RemoveDirectionLight(DirectionalLightPtr light);

	void RemoveAllDirectionLights();


	PointLightPtr AddPointLight();
	void RemovePointLight(PointLightPtr light);

	void RemoveAllPointLights();

#pragma endregion

	void DrawAll();

	void SetBackgroundColor(Color color);

protected:

	void BindSceneDataToEffect(EntityEffect * effect);

	void DrawEntities();
	void DrawParticleSystems();

	void SetUpShaderData();

	void SetWindowSize(int w,int h);

	void DrawEntity(EntityBase * entity);

	void InitParticleSystemsDepthAndBlendStates();
};

