#pragma once
#include "Renderer.h"
#include "Object.h"
#include "Global.h"

class ScnMgr
{
private:

	Renderer * m_Renderer = NULL;
	//Object *m_TestObj;
	Object *m_Objects[MAX_OBJECT]; //�ƽ� ������Ʈ ��ŭ�� ������ ������ �ִ°�.
	GLuint m_testTexture;
	GLuint m_explosionTexture;

public:
	//���Ŵ��� �����ڿ��� �������� ������Ʈ.
	ScnMgr();
	~ScnMgr();
	//void Init();
	void RenderScene();
	void Update(float fTimeElapsed); //��������. ���߰�
	//void GenerateTestObj();
	void ApplyForce(float x, float y, DWORD eTime);
	void AddObject(float pX, float pY, float pZ, float sX, float sY, float Vx, float vY);
	void DeleteObject(unsigned int id);
	int FindObjectSlot();
};