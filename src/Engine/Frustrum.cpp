#include "Frustrum.h"


void Frustrum::BuildFromViewProjMatrix(DirectX::XMFLOAT4X4 & mat)
{
	planes[0].x = mat._14 + mat._11;
	planes[0].y = mat._24 + mat._21;
	planes[0].z = mat._34 + mat._31;
	planes[0].w = mat._44 + mat._41;


	planes[1].x = mat._14 - mat._11;
	planes[1].y = mat._24 - mat._21;
	planes[1].z = mat._34 - mat._31;
	planes[1].w = mat._44 - mat._41;


	planes[2].x = mat._14 - mat._12;
	planes[2].y = mat._24 - mat._22;
	planes[2].z = mat._34 - mat._32;
	planes[2].w = mat._44 - mat._42;


	planes[3].x = mat._14 + mat._12;
	planes[3].y = mat._24 + mat._22;
	planes[3].z = mat._34 + mat._32;
	planes[3].w = mat._44 + mat._42;

	planes[4].x = mat._13;
	planes[4].y = mat._23;
	planes[4].z = mat._33;
	planes[4].w = mat._43;

	planes[5].x = mat._14 - mat._13;
	planes[5].y = mat._24 - mat._23;
	planes[5].z = mat._34 - mat._33;
	planes[5].w = mat._44 - mat._43;


	for(int i = 0;i < 6;i++)
	{
		DirectX::XMVECTOR plane = DirectX::XMLoadFloat4((const DirectX::XMFLOAT4*)&planes[i]);
		plane = DirectX::XMPlaneNormalize(plane);
		DirectX::XMStoreFloat4((DirectX::XMFLOAT4*)&planes[i],plane);
	}
}

bool Frustrum::IsSphereIn(BoundingSphere & sphere)
{
	for(int i = 0;i < 6;i++)
	{
		DirectX::XMVECTOR plane = DirectX::XMLoadFloat4((const DirectX::XMFLOAT4*)&planes[i]);
		DirectX::XMVECTOR point = DirectX::XMLoadFloat3((const DirectX::XMFLOAT3*)&sphere.position);
		DirectX::XMVECTOR dot = DirectX::XMPlaneDotCoord(plane,point);
		DirectX::XMFLOAT3 len;
		DirectX::XMStoreFloat3(&len,dot);

		if(len.x + sphere.radius < 0)
		{
			return false;
		}
	}
	return true;
}
