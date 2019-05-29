#pragma once
#include "Global.h"

struct Point {
	float x;
	float y;
};

class Object{
public:
	Object();
	~Object();

	void Setpos(float x, float y, float z);// { m_fposX = x; m_fposY = y; }
	void Getpos(float* x, float* y, float* z);
	void GetHight(float *hight);
	void SetHight(float hight);
	void SetSize(float width, float height);
	void GetSize(float* width, float* height);
	void GetForce(float* width, float* height);
	void SetForce(float width, float height);
	void GetMass(float* mass);
	void SetMass(float mass);
	void SetFrictionCoef(float mass);
	void GetFrictionCoef(float* mass);
	void SetAcc(float accX, float accY, float accZ);
	void GetAcc(float* accX, float* accY, float* accZ);
	void SetVelocity(float velX, float velY, float velZ);// { m_velX = velX; m_velY = velY;};
	void GetVelocity(float* velx, float* vely, float* velZ);
	void Update(float ElipsedTime);
	void ApplyForce(float x, float y,float z, DWORD eTime);
	void GetKind(KIND *kind);
	void SetKind(KIND kind);
	void GetColor(float *R, float *G, float *B);
	void SetColor(float R, float G, float B);
	void SetHP(int hp);
	void GetHP(int *hp);
	void Setstate(STATE state);
	void Getstate(STATE* state);

private:

	float m_fposX, m_fposY, m_fposZ;
	float m_hight;
	float m_sizeWidth, m_sizeHeight;

	float m_speed; //¼Óµµ set --> vx,vy
	float m_velX, m_velY, m_velZ;
	float m_accY, m_accX, m_accZ;
	float m_forceX, m_forceY;
	float m_mass;
	float m_coefFriction;

	int m_nObject;
	bool m_bRender = false;

	KIND m_Kind;
	float m_R, m_G, m_B;
	
	int m_hp;

	STATE m_state;
};

