#include "stdafx.h"
#include "Object.h"
#include <math.h>
#include <float.h>

Object::Object(){
}


Object::~Object(){
}

void Object::Update(float ElipsedTime){
	//마찰력은 항시 작용
	//friction.
	float gz = m_mass * GRAVITY;
	float friction = m_coefFriction * gz;
	float velMag = sqrtf(m_velX * m_velX + m_velY * m_velY + m_velZ * m_velZ);

	if (velMag < FLT_EPSILON){ //마찰력x == 속도 0
		m_velX = 0.f;
		m_velY = 0.f;
		m_velZ = 0.f;
	}

	else	{ 
		float fx = -friction * m_velX/ velMag;
		float fy = -friction * m_velY/ velMag;

		//가속도
		float accX = fx / m_mass;
		float accY =  fy / m_mass;

		float newVelX = m_velX + (accX) * ElipsedTime;
		float newVelY = m_velY + (accY) * ElipsedTime;

		//그대로쓰면 망함.
		if (newVelX * m_velX < 0.f) m_velX = 0.f;
		else m_velX = newVelX;

		if (newVelY * m_velY < 0.f) m_velY = 0.f;
		else m_velY = newVelY;

		//gravity calculation
		m_velZ =  m_velZ - GRAVITY * ElipsedTime;
	}
	//Calc velocity
	m_velX = m_velX + m_accX * ElipsedTime;
	m_velY = m_velY + m_accY * ElipsedTime;
	m_velZ = m_velZ + m_accZ * ElipsedTime;

	//Calc location
	m_fposX = m_fposX + m_velX * ElipsedTime;
	m_fposY = m_fposY + m_velY * ElipsedTime;
	m_fposZ = m_fposZ + m_velZ * ElipsedTime;

	if (m_fposZ > 0.f) {
		m_state = STATE_AIR;
	}
	else {
		m_state = STATE_GROUND;
		m_fposZ = 0.f;
		m_velZ = 0.f;
		if (m_Kind == KIND_HERO)
			m_velZ = 3.f;
	}
}

void Object::ApplyForce(float x, float y, float z, DWORD eTime) {
	float elapsedTime = eTime;
	// 가속도 계산
	m_accX = x / m_mass;
	m_accY = y / m_mass;
	m_accZ = z / m_mass;

	// 속도 계산
	m_velX = m_velX + m_accX * elapsedTime;
	m_velY = m_velY + m_accY * elapsedTime;
	m_velZ = m_velZ + m_accZ * elapsedTime;

	m_accX = 0.f;
	m_accY = 0.f;
	m_accZ = 0.f;
}

void Object::GetAcc(float* x, float* y, float *z){
	*x = m_accX;
	*y = m_accY;
	*z = m_accZ;
}

void Object::SetAcc(float x, float y, float z){
	m_accX = x;
	m_accY = y;
	m_accZ = z;
}

void Object::GetFrictionCoef(float* fric){
	*fric = m_coefFriction;
	
}

void Object::SetFrictionCoef(float fric){
	m_coefFriction = fric;
}

void Object::Getpos(float* x, float* y, float* z){
	*x = m_fposX;
	*y = m_fposY;
	*z = m_fposZ;
}

void Object::Setpos(float x, float y, float z){
	m_fposX = x;
	m_fposY = y;
	m_fposZ = z;
}

void Object::GetHight(float *hight) {
	*hight = m_hight;
}

void Object::SetHight(float hight) {
	m_hight = hight;
}

void Object::SetSize(float width, float height){
	m_sizeWidth = width;
	m_sizeHeight = height;
}

void Object::GetSize(float* width, float* height){
	*width = m_sizeWidth;
	*height = m_sizeHeight;
}

void Object::GetVelocity(float* x, float* y, float* z){
	*x = m_velX;
	*y = m_velY;
	*z = m_velZ;
}

void Object::SetVelocity(float velX, float velY, float velZ){
	m_velX = velX; 
	m_velY = velY;
	m_velZ = velZ;
};

void Object::GetForce(float* x, float* y){
	*x = m_forceX;
	*y = m_forceY;
}

void Object::SetForce(float x, float y){
	m_forceX = x;
	m_forceY = y;
}

void Object::GetMass(float* m){
	*m = m_mass;
}

void Object::SetMass(float m){
	m_mass = m;
}

void Object::GetKind(KIND *kind){
	*kind = m_Kind;
}

void Object::SetKind(KIND kind){
	m_Kind = kind;
}

void Object::GetColor(float *R, float *G, float *B) {
	*R = m_R;
	*G = m_G;
	*B = m_B;
}

void Object::SetColor(float R, float G, float B) {
	m_R = R;
	m_G = G;
	m_B = B;
}

void Object::SetHP(int hp){
	m_hp = hp;
}

void Object::GetHP(int * hp){
	*hp = m_hp;
}

void Object::Setstate(STATE state){
	m_state = state;
}

void Object::Getstate(STATE * state){
	*state = m_state;
}
