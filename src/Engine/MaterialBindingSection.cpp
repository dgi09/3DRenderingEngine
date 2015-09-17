#include "MaterialBindingSection.h"
#include "DeviceDependableFactory.h"
#include "ConstantBuffer.h"

void MaterialBindingSection::Init(DeviceDependableFactory * factory)
{
	inVS = false;
	inPS = true;

	psShader.texturesCount = 2;
	psShader.buffersCount = 1;

	psShader.buffers[0] = factory->CreateConstantBuffer();
	psShader.buffers[0].Get()->InitBuffer(sizeof(MaterialData));

	psShader.textures[0] = TexturePtr(true);
	psShader.textures[1] = TexturePtr(true);
}

EffectFunctionality MaterialBindingSection::GetEffectFunctionality()
{
	return MATERIAL;
}

void MaterialBindingSection::Destroy()
{
	psShader.buffers[0].Delete();
}

void MaterialBindingSection::SetDiffuseMap(TexturePtr texture)
{
	psShader.textures[0] = texture;
	
}

void MaterialBindingSection::SetBumpMap(TexturePtr bumpMap)
{
	psShader.textures[1] = bumpMap;
}

void MaterialBindingSection::SetMaterialData(MaterialData * data)
{
	psShader.buffers[0].Get()->FillBuffer(data);
}
