#include "Pos_Normal_Tangent_TexCoord_Layout.h"
#include <d3d11.h>
#include "LayoutDescription.h"


LayoutDescription * Pos_Normal_Tangent_TexCoord_Layout::GetDescription()
{
	if(desc == nullptr)
	{
		desc = new LayoutDescription();

		D3D11_INPUT_ELEMENT_DESC inEl[4] = 
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};

		desc->numberOfElements = 4;

		desc->elements = new D3D11_INPUT_ELEMENT_DESC[desc->numberOfElements];
		memcpy(desc->elements,inEl,sizeof(D3D11_INPUT_ELEMENT_DESC) * desc->numberOfElements);
	}

	return desc;
}
