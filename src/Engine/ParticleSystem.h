#pragma once 

#include "ParticleGPUData.h"
#include "ParticleCPUData.h"
#include "ParticleSystemsInfo.h"
#include "MeshPtr.h"
#include "TextureHandler.h"
#include "Vector3.h"

class EXPORT ParticleSystemEffectBinder;
class EXPORT ResourceManager;


class EXPORT ParticleSystem 
{
	MeshPtr quad;
	ResourceManager * resMgr;
	
	ParticleGPUData gpuData[MAX_PARTICLES_IN_SYSTEM];
	ParticleCPUData cpuData[MAX_PARTICLES_IN_SYSTEM];

	unsigned int maxParticles;
	unsigned int liveParticles;
	float minLifeTime;
	float maxLifeTime;
	float minSize;
	float maxSize;
	double spawnTime;
	double currentSpawnTime;
	unsigned int minSpawnParitcles;
	unsigned int maxSpawnParticles;

	Vector3 minSpawnVelocity;
	Vector3 maxSpawnVelocity;
	Vector3 emmiterPosition;
	Vector3 minSpawnPosition;
	Vector3 maxSpawnPosition;

	TextureHandler colorTextureHandler;

	bool useSizeOverLife;

	bool useOpacityOverLife;
	bool useVelocityOverLife;

	bool addParticles;



public:

	void Init(MeshPtr quadPtr,ResourceManager * mgr);
	
	void Draw(ParticleSystemEffectBinder * binder);
	void AddTime(double time);

	void SetEmmiterPosition(Vector3 position);

	void SetColorTexture(const char * fileName);
	void SetMaxParticles(unsigned int value);
	void SetMinLifeTime(float value);
	void SetMaxLifeTime(float value);
	void SetMinSize(float value);
	void SetMaxSize(float value);

	void SetSpawnTime(double value);
	void SetMinSpawnParticles(unsigned int value);
	void SetMaxSpawnParticles(unsigned int value);

	void SetMinSpawnVelocity(Vector3 value);
	void SetMaxSpawnVelocity(Vector3 value);

	void SetMinSpawnPosition(Vector3 pos);
	void SetMaxSpawnPosition(Vector3 pos);

	void UseSizeOverLife(bool val);
	void UseVelocityOverLife(bool val);
	void UseOpacityOverLife(bool val);

	void AllowParticleAdd(bool val);

private:

	void AddParticle();
	void KillParticle(unsigned int index);
};