///////////////////////////////////////////////////////////////////////////////
// This file passes the model, vertices and indices to the graphics pipeline //
///////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Arena = 0;
	m_ColorShader = 0;
	m_LeftPaddle = 0;
	m_RightPaddle = 0;
	m_Ball = 0;
	m_GameManager = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the arena object.
	m_Arena = new ArenaClass;
	if(!m_Arena)
	{
		return false;
	}

	// Initialize the arena object.
	result = m_Arena->Initialize(m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the arena.", L"Error", MB_OK);
		return false;
	}

	// Create the paddles
	m_LeftPaddle = new PaddleClass(0);
	if (!m_LeftPaddle)
	{
		return false;
	}

	// Initialize the paddle object
	result = m_LeftPaddle->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the left paddle.", L"Error", MB_OK);
		return false;
	}

	m_RightPaddle = new PaddleClass(1);
	if (!m_RightPaddle)
	{
		return false;
	}

	result = m_RightPaddle->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the right paddle.", L"Error", MB_OK);
		return false;
	}

	m_Ball = new BallClass();
	if (!m_Ball)
	{
		return false;
	}

	result = m_Ball->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not intitialize the ball.", L"Error", MB_OK);
	}

	m_GameManager = new GameManagerClass();
	if (!m_GameManager)
	{
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the arena object.
	if(m_Arena)
	{
		m_Arena->Shutdown();
		delete m_Arena;
		m_Arena = 0;
	}

	// Release the paddle object.
	if(m_LeftPaddle)
	{
		m_LeftPaddle->Shutdown();
		delete m_LeftPaddle;
		m_LeftPaddle = 0;
	}

	if (m_RightPaddle)
	{
		m_RightPaddle->Shutdown();
		delete m_RightPaddle;
		m_RightPaddle = 0;
	}

	if (m_Ball)
	{
		m_Ball->Shutdown();
		delete m_Ball;
		m_Ball = 0;
	}

	if (m_GameManager)
	{
		delete m_GameManager;
		m_GameManager = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	if (m_GameManager->GetState() == States::Play)
	{
		m_Ball->CollisionCheck(m_LeftPaddle);
		m_Ball->CollisionCheck(m_RightPaddle);
		m_Ball->Update();
	}
	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}

PaddleClass* GraphicsClass::GetPaddle(int index)
{
	if (index == 0)
	{
		return m_LeftPaddle;
	}
	else
		return m_RightPaddle;
}

GameManagerClass* GraphicsClass::GetGameManager()
{
	return m_GameManager;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translation;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Arena->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Arena->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if(!result)
	{
		return false;
	}

	D3DXMatrixTranslation(&translation, 0.0f, m_LeftPaddle->GetDy(), 0.0f);

	worldMatrix *= translation;

	m_LeftPaddle->Render(m_D3D->GetDeviceContext());

	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_LeftPaddle->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixTranslation(&translation, 0.0f, m_RightPaddle->GetDy(), 0.0f);

	worldMatrix *= translation;

	m_RightPaddle->Render(m_D3D->GetDeviceContext());

	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_RightPaddle->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMatrixTranslation(&translation, m_Ball->GetX(), m_Ball->GetY(), 0.0f);

	worldMatrix *= translation;

	m_Ball->Render(m_D3D->GetDeviceContext());

	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Ball->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}