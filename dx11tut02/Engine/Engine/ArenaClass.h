#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: ArenaClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ARENACLASS_H_
#define _ARENACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: ArenaClass
////////////////////////////////////////////////////////////////////////////////
class ArenaClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	ArenaClass();
	ArenaClass(const ArenaClass&);
	~ArenaClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif