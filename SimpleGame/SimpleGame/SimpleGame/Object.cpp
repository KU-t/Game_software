#include "stdafx.h"
#include "Object.h"
#include <math.h>
#include <float.h>

Object::Object()
{
	
}


Object::~Object()
{
}
void Object::Update(float ElipsedTime)
{

	//�������� �׽� �ۿ�
	//friction.
	float gz = m_mass * 9.8;
	float friction = m_coefFriction * gz;

	float velMag = sqrtf(m_velX*m_velX + m_velY * m_velY);

	//if������ ���°� ����. ������ �ִ� �� ==�� ������.  float���� == �������� 
	//�۽Ƿ� �����ΰ����� ���̰� ������쿣 ���� ���ٰ��� �����Ϸ��ȿ��� �ƿ��ٲ��ֱ��ұ״� ���������� �����鰰�������κ��ش�
	// float ���� �ǹ� ����.
	if (velMag < FLT_EPSILON) //������x == �ӵ� 0
	{
		m_velX = 0.f;
		m_velY = 0.f;
	}
	else
	{ 
		//�츮�� �ӵ� ũ�� ���ʿ��� ���⸸�ʿ� ���⸸�����ͼ� �����¸������ٰž� ũ�Ⱑ 1��. 
		//�� ����ȭ�� ������Ѵ� velmag�γ�����.
		float fx = -friction * m_velX / velMag;
		float fy = -friction * m_velY / velMag;
		
		//�����ָ鸶�����̵� �ӵ�. �߷°��ӵ��� �������� �����׷¿��ٰ� ������������� ����ũ����� �ݿ���Ű�� �������� �������� ��������. 
	
		//���ӵ�
		float accX = fx / m_mass;
		float accY = fy / m_mass;

		float newVelX = m_velX + m_accX * ElipsedTime;
		float newVelY = m_velY + m_accY * ElipsedTime;

		//�״�ξ��� ����.

		if (newVelX * m_velX < 0.f) m_velX = 0.f;
		else m_velX = newVelX;
		if (newVelY * m_velY < 0.f) m_velY = 0.f;
		else m_velY = newVelY;


	}
	//Calc velocity
	m_velX = m_velX + m_accX * ElipsedTime;
	m_velY = m_velY + m_accY * ElipsedTime;

	//float dstx, dsty;
	/*dstx = m_fposX + m_velX * (1.f / 60.0f);
	dsty = m_fposY + m_velY * (1.f / 60.0f);
	*/
	
	//Calc location
	m_fposX = m_fposX + m_velX * ElipsedTime;
	m_fposY = m_fposY + m_velY * ElipsedTime;
	
	//m_fposX = dstx;
	//m_fposY = dsty;

	/*m_velX = m_velX + m_accX * ElipsedTime;
	m_velY = m_velY + m_accY * ElipsedTime;
	m_accX = 0.f;
	m_accY = 0.f;*/



}
//void Object::SetSize(float width, float height)
//{
//	m_sizeWidth = width;
//	m_sizeHeight = height;
//
//	//m_si
//}
//void Object::Getpos(float x, float y)
//{
//	x = m_fposX;
//	y = m_fposY;
//
//}
//void Object::GetSize(float width, float height)
//{
//	*width = &m_sizeWidth;
//	*height = &m_sizeHeight;
//}
//void Object::GetSize(float* width, float* height)
//{
//	*width = m_sizeWidth;
//	*height = m_sizeHeight;
//}
//void Object::AddForce(float x, float y)
//{
//	float fTimeElapsed = 1.f;
//
//	m_accX = x;
//	m_accY = y;
//
//}
void Object::GetAcc(float* x, float* y)
{
	*x = m_accX;
	*y = m_accY;
}

void Object::SetAcc(float x, float y)
{
	m_accX = x;
	m_accY = y;
}
void Object::GetFrictionCoef(float* fric)
{
	*fric = m_coefFriction;
	
}

void Object::SetFrictionCoef(float fric)
{
	m_coefFriction = fric;
	//m_accY = y;
}
void Object::Getpos(float* x, float* y, float* z)
{
	*x = m_fposX;
	*y = m_fposY;
	*z = m_fposZ;

}

void Object::Setpos(float x, float y, float z)
{
	m_fposX = x;
	m_fposY = y;
	m_fposZ = z;

}
void Object::SetSize(float width, float height)
{
	m_sizeWidth = width;
	m_sizeHeight = height;
}
void Object::GetSize(float* width, float* height)
{
	*width = m_sizeWidth;
	*height = m_sizeHeight;
}
void Object::GetVelocity(float* x, float* y)
{
	*x = m_velX;
	*y = m_velY;

}

void Object::SetVelocity(float velX, float velY){
	m_velX = velX; 
	m_velY = velY;
};


void Object::GetForce(float* x, float* y)
{
	*x = m_forceX;
	*y = m_forceY;
}

void Object::SetForce(float x, float y)
{
	m_forceX = x;
	m_forceY = y;
}

void Object::GetMass(float* m)
{
	*m = m_mass;
}

void Object::SetMass(float m)
{
	m_mass = m;
}
void Object::ApplyForce(float x, float y, DWORD eTime)
{
	float elapsedTime = eTime;
	// ���ӵ� ���
	m_accX = x / m_mass;
	m_accY = y / m_mass;

	// �ӵ� ���
	m_velX = m_velX + m_accX * elapsedTime;
	m_velY = m_velY + m_accY * elapsedTime;

	m_accX = 0.f;
	m_accY = 0.f;

	//m_fposX = m_fposX + m_velX * elapsedTime;
	//m_fposY = m_fposY + m_velY * elapsedTime;
}

