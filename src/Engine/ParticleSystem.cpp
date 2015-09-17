#include "ParticleSystem.h"
#include "ResourceManager.h"
#include "ParticleSystemEffectBinder.h"
#include <random>

void ParticleSystem::Init(MeshPtr quadPtr,ResourceManager * mgr)
{
	this->resMgr = mgr;
	this->quad = quadPtr;

	maxParticles = 70;
	liveParticles = 0;
	minLifeTime = 30.0f;
	maxLifeTime = 50.0f;

	minSpawnParitcles = 4;
	maxSpawnParticles = 7;

	minSize = 7;
	maxSize = 10;
	spawnTime = 7;
	currentSpawnTime = 0.0;
	colorTextureHandler = TextureHandler(false);

	minSpawnVelocity = Vector3(-0.2f,0.3,0.0f);
	maxSpawnVelocity = Vector3(0.2f,1.4f,0.0f);

	minSpawnPosition = Vector3(-5.0f,0.0f,0.0f);
	maxSpawnPosition = Vector3(5.0f,0.0f,0.0f);

	emmiterPosition = Vector3(0.0f,0.0f,0.0f);

	useOpacityOverLife = false;
	useSizeOverLife = true;
	useVelocityOverLife = false;

	AllowParticleAdd(true);
	ZeroMemory(cpuData,sizeof(cpuData));
	ZeroMemory(gpuData,sizeof(gpuData));

}

void ParticleSystem::Draw(ParticleSystemEffectBinder * binder)
{
	if(liveParticles > 0)
	{
		binder->SetColorTexture(colorTextureHandler.Get());
		binder->FillParticleData(gpuData,sizeof(gpuData));
		binder->Bind();

		quad.Get()->DrawInstanced(liveParticles);
	}

}

void ParticleSystem::AddTime(double time)
{

	if(liveParticles > 0)
	{
		for(int i = 0;i < liveParticles;i++)
		{
			if(cpuData[i].currentLifeTime + time >= cpuData[i].lifeTime)
			{
				KillParticle(i);
				if(i == liveParticles)
					break;
			}

			ParticleCPUData & cdata = cpuData[i];
			ParticleGPUData & gdata = gpuData[i];
			cdata.currentLifeTime += time;

			float lifeTimeFactor = ((cdata.lifeTime - cdata.currentLifeTime) / cdata.lifeTime);

			if(useSizeOverLife)
				gdata.size =  lifeTimeFactor* cdata.size;
			else gdata.size = cdata.size;

			Vector3 currentVelocity;
			if(useVelocityOverLife)
				currentVelocity = cdata.velocity * lifeTimeFactor;
			else currentVelocity = cdata.velocity;


			gdata.worldPos = gdata.worldPos + currentVelocity;

			if(useOpacityOverLife)
				gdata.opacityFactor = lifeTimeFactor;
			else gdata.opacityFactor = 1.0f;
		}
	}

	if(addParticles)
	if(currentSpawnTime + time >= spawnTime && liveParticles < maxParticles)
	{
		unsigned int spownCount = minSpawnParitcles + rand() % (maxSpawnParticles - minSpawnParitcles);
		if(liveParticles + spownCount > maxParticles)
			spownCount = maxParticles - liveParticles;

		for(unsigned int i = 0;i < spownCount;i++)
		{
			AddParticle();
		}
		currentSpawnTime = 0;
	}
	else currentSpawnTime += time;

}

void ParticleSystem::SetColorTexture(const char * fileName)
{
	colorTextureHandler = resMgr->GetTexture(fileName);
}

void ParticleSystem::AddParticle()
{
	ParticleCPUData & cdata = cpuData[liveParticles];
	ParticleGPUData & gdata = gpuData[liveParticles];

	cdata.currentLifeTime = 0.0;

	Vector3 distVec = maxSpawnVelocity - minSpawnVelocity;
	Vector3 randVector;
	randVector.x = ((float)rand() / (float)RAND_MAX) * distVec.x;
	randVector.y = ((float)rand() / (float)RAND_MAX) * distVec.y;
	randVector.z = ((float)rand() / (float)RAND_MAX) * distVec.z;

	cdata.velocity = minSpawnVelocity + randVector;

	Vector3 distSpawnPos = maxSpawnPosition - minSpawnPosition;
	randVector.x = ((float)rand() / (float)RAND_MAX) * distSpawnPos.x;
	randVector.y = ((float)rand() / (float)RAND_MAX) * distSpawnPos.y;
	randVector.z = ((float)rand() / (float)RAND_MAX) * distSpawnPos.z;

	cdata.lifeTime = minLifeTime + ((float)rand() / (float)RAND_MAX) * (maxLifeTime - minLifeTime);

	cdata.size = minSize + ((float)rand() / (float)RAND_MAX) * (maxSize - minSize);
	gdata.worldPos = emmiterPosition + minSpawnPosition + randVector;

	liveParticles++;
}

void ParticleSystem::KillParticle(unsigned int index)
{
	for(int i = index;i < liveParticles;i++)
	{
		gpuData[i] = gpuData[i + 1];
		cpuData[i] = cpuData[i + 1];
	}
	liveParticles--;
}

void ParticleSystem::SetEmmiterPosition(Vector3 position)
{
	emmiterPosition = position;
}

void ParticleSystem::SetMaxParticles(unsigned int value)
{
	maxParticles = value;
}

void ParticleSystem::SetMinLifeTime(float value)
{
	minLifeTime = value;
}

void ParticleSystem::SetMaxLifeTime(float value)
{
	maxLifeTime = value;
}

void ParticleSystem::SetMinSize(float value)
{
	minSize = value;
}

void ParticleSystem::SetMaxSize(float value)
{
	maxSize = value;
}

void ParticleSystem::SetSpawnTime(double value)
{
	spawnTime = value;
}

void ParticleSystem::SetMinSpawnParticles(unsigned int value)
{
	minSpawnParitcles = value;
}

void ParticleSystem::SetMaxSpawnParticles(unsigned int value)
{
	maxSpawnParticles = value;
}

void ParticleSystem::SetMinSpawnVelocity(Vector3 value)
{
	minSpawnVelocity = value;
}

void ParticleSystem::SetMaxSpawnVelocity(Vector3 value)
{
	maxSpawnVelocity = value;
}

void ParticleSystem::SetMinSpawnPosition(Vector3 pos)
{
	minSpawnPosition = pos;
}

void ParticleSystem::SetMaxSpawnPosition(Vector3 pos)
{
	maxSpawnPosition = pos;
}

void ParticleSystem::UseSizeOverLife(bool val)
{
	useSizeOverLife = val;
}

void ParticleSystem::UseVelocityOverLife(bool val)
{
	useVelocityOverLife = val;
}

void ParticleSystem::UseOpacityOverLife(bool val)
{
	useOpacityOverLife = val;
}

void ParticleSystem::AllowParticleAdd(bool val)
{
	addParticles = val;
}
