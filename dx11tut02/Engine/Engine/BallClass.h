#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: BallClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BALLCLASS_H_
#define _BALLCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include "PaddleClass.h"
#include <LeftPaddle.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: BallClass
////////////////////////////////////////////////////////////////////////////////
class BallClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	BallClass();
	BallClass(const BallClass&);
	~BallClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	void Update();
	float GetX();
	float GetY();

	void CollisionCheck(PaddleClass*);

	void CollisionCheck(LeftPaddle* paddle);

	void InvertDx();
	void InvertDy();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	int m_vertexCount, m_indexCount;
	float m_xPosition, m_yPosition, m_dx, m_dy;
};

#endif