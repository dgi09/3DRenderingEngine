#pragma once
#include "Common.h"
#include "EffectMask.h"

#include "EntityShaderData.h"
#include "EntityData.h"
#include "Positionable.h"
#include "Rotateable.h"
#include "Scaleable.h"
#include <string>
#include "ModelHandler.h"
#include "SceneDrawable.h"
#include <vector>
#include "DrawPack.h"
#include "Color.h"
#include "Material.h"


class EXPORT EffectBinder;
class EXPORT Mesh;
class EXPORT Texture;
class EXPORT DeviceDependableFactory;


class EXPORT ResourceManager;

class EXPORT EntityBase : public SceneDrawable , public Rotateable , public Scaleable
{

protected:
	EFFECTMASK effectMask; 
	ModelHandler  modelHandler;
	EntityData data;
	EntityShaderData shaderData;
	ResourceManager * resMgr;

	std::vector<Material> materials;

public:
	virtual void Draw(EffectBinder * binder) = 0;

	EFFECTMASK GetEffectMask();


	void Illuminate(bool val);

	virtual void Destroy();
	void Init(ModelHandler model,ResourceManager * resMgr, DeviceDependableFactory * factory);

	Material * GetMaterial(unsigned int subset);

protected:
	void BindEntityData(EffectBinder * binder);
	void BindMaterialData(EffectBinder * binder, Material & mat);
	void SetUpShaderData();
    virtual void BuildBoundingSphere();
	
};