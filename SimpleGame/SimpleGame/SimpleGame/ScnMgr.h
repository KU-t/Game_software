#pragma once
#include "Renderer.h"
#include "Object.h"
#include "Global.h"
#include "Sound.h"

class ScnMgr{
private:

	Renderer * m_Renderer = NULL;
	Sound *m_Sound = NULL;
	GLuint m_SoundBG, m_SoundFire, m_SoundEX;
	Object *m_Objects[MAX_OBJECT]; //맥스 오브젝트 만큼의 슬롯을 가지고 있는거.
	GLuint m_santa, m_gift, m_house, m_village;
	GLuint m_explosionTexture;
	GLuint m_particle;

public:
	ScnMgr();
	~ScnMgr();

	void RenderScene();
	void Update(float fTimeElapsed); //렌더전에. 색추가
	void UpdateCollision();
	void ApplyForce(float x, float y,float z, DWORD eTime);
	void AddObject(float pX, float pY, float pZ, float hight, float sX, float sY, float Vx, float vY, float vz, KIND kind, int hp, STATE state);
	void DeleteObject(unsigned int id);
	int FindObjectSlot();
	void Shoot(int ShootID, DWORD fTimeElapsed);
	bool RRCollision(float minX, float maxX, float minY, float maxY, float minX1, float maxX1, float minY1, float maxY1);
	bool IsCollision(float minx, float miny, float maxx, float maxy, float minx1, float miny1, float maxx1, float maxy1);
	void processCollision(int  i, int j);
	void DoGarbagecollet();
	DWORD Create_Bullet_sum = 0;
};