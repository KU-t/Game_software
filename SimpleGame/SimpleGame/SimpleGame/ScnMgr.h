#pragma once
#include "Renderer.h"
#include "Object.h"
#include "Global.h"

class ScnMgr
{
private:

	Renderer * m_Renderer = NULL;
	//Object *m_TestObj;
	Object *m_Objects[MAX_OBJECT]; //맥스 오브젝트 만큼의 슬롯을 가지고 있는거.
	GLuint m_testTexture;
	GLuint m_explosionTexture;

public:
	//씬매니저 생성자에서 렌더러랑 오브젝트.
	ScnMgr();
	~ScnMgr();
	//void Init();
	void RenderScene();
	void Update(float fTimeElapsed); //렌더전에. 색추가
	//void GenerateTestObj();
	void ApplyForce(float x, float y, DWORD eTime);
	void AddObject(float pX, float pY, float pZ, float sX, float sY, float Vx, float vY);
	void DeleteObject(unsigned int id);
	int FindObjectSlot();
};