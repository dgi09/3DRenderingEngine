#include "StaticEntity.h"
#include "Vertex.h"
#include "EffectBinder.h"
#include "Mesh.h"
#include "StaticMeshData.h"
#include "MeshPtr.h"
#include "DrawPack.h"


void StaticEntity::Draw(EffectBinder * binder)
{
	SetUpShaderData();
	BindEntityData(binder);

	Model * model = modelHandler.Get().Get();

	for(unsigned int i = 0;i < model->GetNumberOfMeshes();i++)
	{
		
		Material mat = materials[i];
		BindMaterialData(binder,mat);
		binder->BindAllSections();

		Mesh * mesh = model->GetMeshAt(i).Get();
		mesh->DrawIndexed();
	}
}
