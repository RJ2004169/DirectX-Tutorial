#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: PaddleClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _PADDLECLASS_H_
#define _PADDLECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: PaddleClass
////////////////////////////////////////////////////////////////////////////////
class PaddleClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	PaddleClass(int index);
	PaddleClass(const PaddleClass&);
	~PaddleClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	void Update(float);
	float GetDy();
	int GetLeftRightIndex();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount, m_LeftRightIndex;
	float m_yPosition;
};

#endif