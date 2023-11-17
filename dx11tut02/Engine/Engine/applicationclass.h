////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _APPLICATIONCLASS_H_
#define _APPLICATIONCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "ArenaClass.h"
#include "PaddleClass.h"
#include "LeftPaddle.h"
#include "BallClass.h"
#include "GameManagerClass.h"
#include "colorshaderclass.h"
#include "fontshaderclass.h"
#include "fontclass.h"
#include "textclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	PaddleClass* GetPaddle(int);
	GameManagerClass* GetGameManager();

private:
	bool Render();

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	ArenaClass* m_Arena;
	PaddleClass* m_RightPaddle, * m_SecondRight;
	BallClass* m_Ball;
	GameManagerClass* m_GameManager;
	FontShaderClass* m_FontShader;
	FontClass* m_Font;
	TextClass* m_TextString1, * m_TextString2;

	ColorShaderClass* m_ColorShader;
};

#endif