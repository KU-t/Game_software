#pragma once
#include "stdafx.h"
#include "Object.h"
#include <math.h>
#include <float.h>
#include <iostream>

using namespace std;

Object::Object()
{

}

Object::~Object()
{

}


void Object::GetPosition(float * x, float * y, float *z)
{
	*x = m_PosX;
	*y = m_PosY;
	*z = m_PosZ;
}

void Object::SetPosition(float x, float y, float z)
{
	m_PosX = x;
	m_PosY = y;
	m_PosZ = z;
}

void Object::GetSize(float * width, float * height)
{
	*width = m_SizeWidth;
	*height = m_SizeHeight;
}

void Object::SetSize(float width, float height)
{
	m_SizeWidth = width;
	m_SizeHeight = height;
}

void Object::GetVelocity(float * x, float * y)
{
	*x = m_VelX;
	*y = m_VelY;
}

void Object::SetVelocity(float x, float y)
{
	this->m_VelX = x;
	this->m_VelY = y;
}

void Object::GetAcc(float * x, float * y)
{
	*x = m_AccX;
	*y = m_AccY;
}

void Object::SetAcc(float x, float y)
{
	m_AccX = x;
	m_AccY = y;
}

void Object::GetForce(float * sx, float * sy) {
	*sx = m_ForX;
	*sy = m_ForY;
}

void Object::SetForce(float sx, float sy) {
	this->m_ForX = sx;
	this->m_ForY = sy;
}

void Object::GetMass(float * x) {
	*x = m_Mass;
}

void Object::SetMass(float x) {
	this->m_Mass = m_Mass;
}

void Object::GetFrictionCoef(float * x) {
	*x = m_FrictionCoef;
}

void Object::SetFrictionCoef(float x){
	this->m_FrictionCoef = x;
}

void Object::Update(float eTimeinsec) 
{
	float gz = m_Mass * 9.8;
	float friction = m_FrictionCoef * gz;

	float velmag = sqrtf(m_VelX * m_VelX + m_VelY * m_VelY);
	
	// float 연산 의미 없음.
	if (velmag < FLT_EPSILON) {	
		m_VelX = 0.f;
		m_VelY = 0.f;
	}

	else {
		float fx = m_FrictionCoef * m_VelX / velmag;
		float fy = m_FrictionCoef * m_VelY / velmag;

		float accX = fx / m_Mass;
		float accY = fy / m_Mass;

		float newVelX = m_VelX + accX * eTimeinsec;
		float newVelY = m_VelY + accY * eTimeinsec;

		if (newVelX*m_VelX < 0.f) {
			m_VelX = 0.f;
		}
		else {
			m_VelX = newVelX;
		}

		if (newVelY*m_VelY < 0.f) {
			m_VelY = 0.f;
		}
		else {
			m_VelY = newVelY;
		}
		m_VelX = newVelX;
		m_VelY = newVelY;
	}

	//Calc velocity
	m_VelX = m_VelX + m_AccX * eTimeinsec;
	m_VelY = m_VelY + m_AccY * eTimeinsec;

	//Calc location
	m_PosX = m_PosX + m_VelX * eTimeinsec;
	m_PosY = m_PosY + m_VelY * eTimeinsec;

	cout << m_VelX << " // " << m_VelY << endl;

}

void Object::ApplyForce(float x, float y, float eTime) {

	float elapsedTime = eTime;

	m_AccX = x / m_Mass;
	m_AccY = y / m_Mass;

	m_VelX = m_VelX + m_AccX * elapsedTime;
	m_VelY = m_VelY + m_AccY * elapsedTime;

	m_AccX = 0.f;
	m_AccY = 0.f;

	//m_PosX = m_PosX + m_VelX * elapsedTime;
	//m_PosY = m_PosY + m_VelY * elapsedTime;

}