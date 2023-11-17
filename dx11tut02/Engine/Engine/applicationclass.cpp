////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "applicationclass.h"


ApplicationClass::ApplicationClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Arena = 0;
	m_SecondRight = 0;
	m_RightPaddle = 0;
	m_Ball = 0;
	m_GameManager = 0;

	m_ColorShader = 0;
	m_FontShader = 0;
	m_Font = 0;
	m_TextString1 = 0;
	m_TextString2 = 0;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	char testString1[32], testString2[32];
	bool result;


	// Create and initialize the Direct3D object.
	m_Direct3D = new D3DClass;

	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the camera object.
	m_Camera = new CameraClass;

	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();

	m_Arena = new ArenaClass;
	if (!m_Arena)
	{
		return false;
	}

	// Initialize the arena object.
	result = m_Arena->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the arena.", L"Error", MB_OK);
		return false;
	}

	// Create the paddles
	m_SecondRight = new PaddleClass();
	if (!m_SecondRight)
	{
		return false;
	}

	// Initialize the paddle object
	result = m_SecondRight->Initialize(m_Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the left paddle.", L"Error", MB_OK);
		return false;
	}

	m_RightPaddle = new PaddleClass();
	if (!m_RightPaddle)
	{
		return false;
	}

	result = m_RightPaddle->Initialize(m_Direct3D->GetDevice());
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

	result = m_Ball->Initialize(m_Direct3D->GetDevice());
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
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the font shader object.
	m_FontShader = new FontShaderClass;

	result = m_FontShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the font object.
	m_Font = new FontClass;

	result = m_Font->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), 0);
	if (!result)
	{
		return false;
	}

	// Set the strings we want to display.
	strcpy_s(testString1, "Hello");
	strcpy_s(testString2, "Goodbye");

	// Create and initialize the first text object.
	m_TextString1 = new TextClass;

	result = m_TextString1->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, testString1, 10, 10, 0.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	// Create and initialize the second text object.
	m_TextString2 = new TextClass;

	result = m_TextString2->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), screenWidth, screenHeight, 32, m_Font, testString2, 10, 50, 1.0f, 1.0f, 0.0f);
	if (!result)
	{
		return false;
	}

	return true;
}


void ApplicationClass::Shutdown()
{
	//Release the color shader object
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the text string objects.
	if (m_TextString2)
	{
		m_TextString2->Shutdown();
		delete m_TextString2;
		m_TextString2 = 0;
	}

	if (m_TextString1)
	{
		m_TextString1->Shutdown();
		delete m_TextString1;
		m_TextString1 = 0;
	}

	// Release the font object.
	if (m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	// Release the font shader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the arena object.
	if (m_Arena)
	{
		m_Arena->Shutdown();
		delete m_Arena;
		m_Arena = 0;
	}

	// Release the paddle objects.
	if (m_SecondRight)
	{
		m_SecondRight->Shutdown();
		delete m_SecondRight;
		m_SecondRight = 0;
	}

	if (m_RightPaddle)
	{
		m_RightPaddle->Shutdown();
		delete m_RightPaddle;
		m_RightPaddle = 0;
	}

	//Release the ball object
	if (m_Ball)
	{
		m_Ball->Shutdown();
		delete m_Ball;
		m_Ball = 0;
	}

	//Release the game manager object
	if (m_GameManager)
	{
		delete m_GameManager;
		m_GameManager = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}


bool ApplicationClass::Frame()
{
	bool result;

	if (m_GameManager->GetState() == States::Play)
	{
		m_Ball->CollisionCheck(m_SecondRight);
		m_Ball->CollisionCheck(m_RightPaddle);
		m_Ball->Update();
	}

	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

PaddleClass* ApplicationClass::GetPaddle(int index)
{
	if (index == 0)
	{
		//return m_Paddle;
	}
	else
		return m_RightPaddle;
}

GameManagerClass* ApplicationClass::GetGameManager()
{
	return m_GameManager;
}



bool ApplicationClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, orthoMatrix, translation;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Arena->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Arena->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	

	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(orthoMatrix);

	translation = XMMatrixTranslation(0.0f, m_RightPaddle->GetDy(), 0.0f);

	worldMatrix *= translation;

	m_RightPaddle->Render(m_Direct3D->GetDeviceContext());

	result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_RightPaddle->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(orthoMatrix);

	translation = XMMatrixTranslation(m_Ball->GetX(), m_Ball->GetY(), 0.0f);

	worldMatrix *= translation;

	m_Ball->Render(m_Direct3D->GetDeviceContext());

	result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Ball->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetOrthoMatrix(orthoMatrix);

	/*translation = XMMatrixTranslation(0.0f, m_SecondRight->GetDy(), 0.0f);

	worldMatrix *= translation;*/


	m_SecondRight->Render(m_Direct3D->GetDeviceContext());

	result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_SecondRight->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix);

	if (!result)
	{
		return false;
	}


	//// Disable the Z buffer and enable alpha blending for 2D rendering.
	//m_Direct3D->TurnZBufferOff();
	//m_Direct3D->EnableAlphaBlending();

	//// Render the first text string using the font shader.
	//m_TextString1->Render(m_Direct3D->GetDeviceContext());

	//result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString1->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
	//	m_Font->GetTexture(), m_TextString1->GetPixelColor());
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the second text string using the font shader.
	//m_TextString2->Render(m_Direct3D->GetDeviceContext());

	//result = m_FontShader->Render(m_Direct3D->GetDeviceContext(), m_TextString2->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix,
	//	m_Font->GetTexture(), m_TextString2->GetPixelColor());
	//if (!result)
	//{
	//	return false;
	//}

	//// Enable the Z buffer and disable alpha blending now that 2D rendering is complete.
	//m_Direct3D->TurnZBufferOn();
	//m_Direct3D->DisableAlphaBlending();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}