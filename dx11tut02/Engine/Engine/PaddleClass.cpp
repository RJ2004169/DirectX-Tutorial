////////////////////////////////////////////////////////////////////////
// This class is used to attach each paddle with its vertex and index //
////////////////////////////////////////////////////////////////////////
#include "PaddleClass.h"


PaddleClass::PaddleClass(int index)
{
	m_LeftRightIndex = index;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_yPosition = 0.0f;
}


PaddleClass::PaddleClass(const PaddleClass& other)
{
}


PaddleClass::~PaddleClass()
{
}


bool PaddleClass::Initialize(ID3D11Device* device)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}


void PaddleClass::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


void PaddleClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int PaddleClass::GetIndexCount()
{
	return m_indexCount;
}


bool PaddleClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	if (m_LeftRightIndex == 0)
	{
		vertices[0].position = D3DXVECTOR3(-7.2f, 0.7f, 0.0f);  // Top left.
		vertices[0].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[1].position = D3DXVECTOR3(-7.2f, -0.7f, 0.0f);  // Bottom left.
		vertices[1].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[2].position = D3DXVECTOR3(-7.0f, -0.7f, 0.0f);  // Bottom right.
		vertices[2].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[3].position = D3DXVECTOR3(-7.0f, 0.7f, 0.0f); // Top right
		vertices[3].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		vertices[0].position = D3DXVECTOR3(7.0f, 0.7f, 0.0f);  // Top left.
		vertices[0].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[1].position = D3DXVECTOR3(7.0f, -0.7f, 0.0f);  // Bottom left.
		vertices[1].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[2].position = D3DXVECTOR3(7.2f, -0.7f, 0.0f);  // Bottom right.
		vertices[2].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

		vertices[3].position = D3DXVECTOR3(7.2f, 0.7f, 0.0f); // Top right
		vertices[3].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	// Load the index array with data.

	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}


void PaddleClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void PaddleClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void PaddleClass::Update(float dy)
{
	if (dy < 0.0f)
	{
		m_yPosition = max(m_yPosition + dy, -3.2f);
	}
	else
	{
		m_yPosition = min(m_yPosition + dy, 3.2f);
	}
}

float PaddleClass::GetDy()
{
	return m_yPosition;
}

int PaddleClass::GetLeftRightIndex()
{
	return m_LeftRightIndex;
}
