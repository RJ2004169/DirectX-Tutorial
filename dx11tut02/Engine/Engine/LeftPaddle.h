#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: PaddleClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LEFTPADDLE_H
#define _LEFTPADDLE_H


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: LeftPaddle
////////////////////////////////////////////////////////////////////////////////
class LeftPaddle
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	LeftPaddle();
	LeftPaddle(const LeftPaddle&);
	~LeftPaddle();

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