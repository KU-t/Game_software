#pragma once
class Object
{
public:
	Object();
	~Object();

	//Functions
	void GetPosition(float * x, float * y, float * z);
	void SetPosition(float x, float y, float z);
	void GetSize(float * width, float * height);
	void SetSize(float width, float height);
	void GetVelocity(float *x, float *y);
	void SetVelocity(float x, float y);
	void GetAcc(float * x, float * y);
	void SetAcc(float x, float y);
	void GetForce(float * x, float * y);
	void SetForce(float x, float y);
	void GetMass(float * x);
	void SetMass(float x);
	void GetFrictionCoef(float * x);
	void SetFrictionCoef(float x);

	void Update(float eTimeInSec);
	void ApplyForce(float x, float y, float eTime);

private:
	//Variables
	float m_PosX;
	float m_PosY;
	float m_PosZ;
	float m_SizeWidth;
	float m_SizeHeight;
	float m_VelX;
	float m_VelY;
	float m_AccX;
	float m_AccY;

	float m_ForX;
	float m_ForY;

	float m_Mass;

	float m_FrictionCoef;
};