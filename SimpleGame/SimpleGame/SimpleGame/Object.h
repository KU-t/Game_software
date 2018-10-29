#pragma once
#include "Global.h"

struct Point {
	float x;
	float y;
};
class Object
{
public:
	Object();
	~Object();
	void Setpos(float x, float y, float z);// { m_fposX = x; m_fposY = y; }
	void Getpos(float* x, float* y, float* z);
	void SetSize(float width, float height);
	void GetSize(float* width, float* height);
	void GetForce(float* width, float* height);
	void SetForce(float width, float height);
	void GetMass(float* mass);
	void SetMass(float mass);
	void SetFrictionCoef(float mass);
	void GetFrictionCoef(float* mass);
	void SetAcc(float accX, float accY);
	void GetAcc(float* accX, float* accY);
	void SetVelocity(float velX, float velY);// { m_velX = velX; m_velY = velY;};
	void GetVelocity(float* x, float* y);
	void Update(float ElipsedTime);
	void ApplyForce(float x, float y, DWORD eTime);
	void GetKind(int *kind);
	void SetKind(int kind);

	

private:
	
	float m_fposX, m_fposY, m_fposZ;

	float m_sizeWidth, m_sizeHeight;
	float m_speed; //¼Óµµ set --> vx,vy
	float m_velX, m_velY;
	float m_accY, m_accX;
	float m_forceX, m_forceY;
	float m_mass;
	float m_coefFriction;

	int m_nObject;
	bool m_bRender = false;

	int m_Kind;
};

