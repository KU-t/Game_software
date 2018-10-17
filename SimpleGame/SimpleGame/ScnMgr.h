#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Global.h"

class ScnMgr
{
public:
	ScnMgr();
	~ScnMgr();

	void RenderScene();
	void Update(float eTimeInSec);
	void ApplyForce(float x, float y, float eTime);
	void AddObject(float px, float py, float pz, float sx, float sy, float vx, float vy);
	void DeleteObject(unsigned int id);
	int FindEmptyObjectSlot();
private:
	Renderer * m_Renderer;
	Object *m_Objects[MAX_OBJECT];
	GLuint m_TestTexture;
};

