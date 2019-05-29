#include "stdafx.h"
#include "ScnMgr.h"
#include "LoadPng.h"
#include "Global.h"

float g_Time = 0;
float temp = 10;
int g_Seq = 0;

ScnMgr::ScnMgr(){
	//Init Object list
	for (int i = 0; i < MAX_OBJECT; ++i) m_Objects[i] = NULL;

	//Create HeroObj
	m_Objects[HERO_ID] = new Object();
	m_Objects[HERO_ID]->Setpos(0, 0, 0.f);
	m_Objects[HERO_ID]->SetHight(0.f);
	m_Objects[HERO_ID]->SetVelocity(0, 0, 0);
	m_Objects[HERO_ID]->SetKind(KIND_HERO);
	m_Objects[HERO_ID]->SetAcc(0, 0, 0);
	m_Objects[HERO_ID]->SetForce(0, 0);
	m_Objects[HERO_ID]->SetSize(0.5f, 0.5f);
	m_Objects[HERO_ID]->SetMass(1.f);
	m_Objects[HERO_ID]->SetColor(1.f, 1.f, 1.f);
	m_Objects[HERO_ID]->SetFrictionCoef(0.2f);
	m_Objects[HERO_ID]->Setstate(STATE_GROUND);

	//TEST ADDOBJ
	AddObject(-4.f * 2, 0.f * 2, 0.f, 0.f, 0.4f * 2, 0.4f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(-2.5f * 2, 0.4f * 2, 0.f, 0.f, 0.35f * 2, 0.35f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(-1.6f * 2, -1.f * 2, 0.f, 0.f, 0.5f * 2, 0.5f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(-5.6f * 2, -1.6f * 2, 0.f, 0.f, 0.5f * 2, 0.5f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(-1.f * 2, 0.f * 2, 0.f, 1.f, 0.4f * 2, 0.4f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(-0.8f * 2, -2.3f * 2, 0.f, 1.f, 0.5f * 2, 0.5f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(2.f * 2, -1.55f * 2, 0.f, 1.f, 0.5f * 2, 0.5f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(1.f * 2, 1.f * 2, 0.f, 1.f, 0.35f * 2, 0.35f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(4.3f * 2, 0.8f * 2, 0.f, 0.f, 0.35f * 2, 0.35f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(5.9f * 2, -1.55f * 2, 0.f, 0.f, 0.5f * 2, 0.5f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	AddObject(0.23f * 2, 8.5f, 0.f, 0.f, 0.25f * 2, 0.25f * 2, 0.f, 0.f, 0.f, KIND_BUILDING, 10, STATE_GROUND);
	

	m_Renderer = new Renderer(WINDOW_SIZE_X, WINDOW_SIZE_Y);

	m_Sound = new Sound();
	m_SoundBG = m_Sound->CreateSound("./sound/BG_BGM.mp3");
	m_SoundFire = m_Sound->CreateSound("./sound/bell.wav");
	m_SoundEX = m_Sound->CreateSound("./sound/laugh.mp3");

	if (!m_Renderer->IsInitialized()) {
		std::cout << "Renderer could not be initialized.. \n";
	}
	m_Sound->PlaySoundW(m_SoundBG, true, 20.f);

	m_santa = m_Renderer->CreatePngTexture("santa.png"); //클래스나 구조체 형식으로 넘길 수 있게
	m_house = m_Renderer->CreatePngTexture("house.png"); //클래스나 구조체 형식으로 넘길 수 있게
	m_gift = m_Renderer->CreatePngTexture("gift.png"); //클래스나 구조체 형식으로 넘길 수 있게
	m_village = m_Renderer->CreatePngTexture("village.png"); //클래스나 구조체 형식으로 넘길 수 있게
	m_explosionTexture = m_Renderer->CreatePngTexture("spritesheet1.png"); //클래스나 구조체 형식으로 넘길 수 있게
	m_particle = m_Renderer->CreatePngTexture("particles.png");
}

ScnMgr::~ScnMgr()
{
}

void ScnMgr::RenderScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //바탕색 바꾸기

	m_Renderer->DrawTextureRectHeight(0, 0 - 225, 0, 2 * WINDOW_SIZE_X, 2 * WINDOW_SIZE_Y, 1, 1, 1, 1, m_village, 0); // 네모 속성 바꾸기 가능

	if (g_Seq > 80) g_Seq = 0;

	for (int i = 0; i < MAX_OBJECT; ++i)
	{
		if (m_Objects[i] != NULL)
		{
			float x, y, z;
			m_Objects[i]->Getpos(&x, &y, &z);

			float width, height;
			m_Objects[i]->GetSize(&width, &height);

			float r, g, b;
			m_Objects[i]->GetColor(&r, &g, &b);

			KIND kind;
			m_Objects[i]->GetKind(&kind);

			float newX = x * 100.f;
			float newY = y * 100.f;
			float newZ = z * 100.f;
			float newH = height * 100;
			float newW = width * 100;

			if (kind == KIND_HERO) {
				//m_Renderer->DrawTextureRectHeight(newX, newY, 0, 10, 10, r, g, b, 1.f, m_village, newZ);
				m_Renderer->SetCameraCenterPos(newX, newY);
				//m_Renderer->DrawSolidRectGauge(newX, newY + newH * 100.f, 0, newW * 30.f, 10.f, 1, 1, 1, 1, newZ, 1.f);
			}

			//스프라이트 이미지
			int seqX = 0;
			int seqY = 0;
			seqX = g_Seq % 9;
			seqY = (int)g_Seq / 9;
			g_Seq ++;
			if (g_Seq > 80) g_Seq = 0;

			//if (kind == KIND_BULLET)		m_Renderer->DrawTextureRectSeqXY(x*100.f, y*100.f + 50.f, newZ, newH, newW, r, g, b, 1, m_explosionTexture, seqX, seqY, 9, 9);
			//if (kind == KIND_BULLET)		m_Renderer->DrawTextureRectHeight(x*100.f, y*100.f, 0, width * 100.f, height * 100.f, r, g, b, 1, m_santa, z * 100.f); // 네모 속성 바꾸기 가능
			if (kind == KIND_HERO)		m_Renderer->DrawTextureRectHeight(x*100.f, y*100.f - 50.f, 0, width * 100.f, height * 100.f, r, g, b, 1, m_santa, z * 100.f); // 네모 속성 바꾸기 가능
			if (kind == KIND_BULLET)		m_Renderer->DrawTextureRectHeight(x*100.f, y*100.f - 50.f, 0, width * 100.f, height * 100.f, r, g, b, 1, m_gift, z * 100.f); // 네모 속성 바꾸기 가능
			if (kind == KIND_BUILDING) {
				m_Renderer->DrawTextureRectHeight(x*100.f, y*100.f - 50.f, 0, width * 100.f, height * 100.f, r, g, b, 1, m_house, z * 100.f); // 네모 속성 바꾸기 가능
				m_Renderer->DrawSolidRectGauge(newX, newY + newH * 8.f, 0, 3000.f, 1000.f, 1, 1, 1, 1, newZ, 0.5f);

			}
		}
	}
}

void ScnMgr::Update(float fTimeElapsed){
	for (int i = 0; i < MAX_OBJECT; ++i)
	{
		if (m_Objects[i]) {
			m_Objects[i]->Update(fTimeElapsed);		
		}
	}

	{
		float hero_x, hero_y, hero_z;
		m_Objects[HERO_ID]->Getpos(&hero_x, &hero_y, &hero_z);
		hero_y = (hero_y - 15.f) * -0.05f;
		
		float hero_size_x, hero_size_y;
		hero_size_x = hero_y;
		hero_size_y = hero_y;

		m_Objects[HERO_ID]->SetSize(hero_size_x, hero_size_y);
	}
}

void ScnMgr::UpdateCollision(){

	for (int i = 0; i < MAX_OBJECT; i++) {
		int collisionCount = 0;
		if (m_Objects[i] == nullptr)
			continue;
		float minX, maxX, minY, maxY = 0.f;
		float pX, pY, pZ, sX, sY = 0.f;
		m_Objects[i]->Getpos(&pX, &pY, &pZ);
		m_Objects[i]->GetSize(&sX, &sY);

		minX = pX - sX / 2.f;
		maxX = pX + sX / 2.f;
		minY = pY - sY / 2.f;
		maxY = pY + sY / 2.f;

		for (int j = 1; j < MAX_OBJECT; j++) {
			if (m_Objects[j] == nullptr)
				continue;

			if (i == j)
				continue;


			float minX1, maxX1, minY1, maxY1 = 0.f;

			m_Objects[j]->Getpos(&pX, &pY, &pZ);
			m_Objects[j]->GetSize(&sX, &sY);

			minX1 = pX - sX / 2.f;
			maxX1 = pX + sX / 2.f;
			minY1 = pY - sY / 2.f;
			maxY1 = pY + sY / 2.f;

			if (RRCollision(minX, maxX, minY, maxY, minX1, maxX1, minY1, maxY1)) {
				collisionCount++;
				processCollision(i, j);
			}
		}
		if (collisionCount > 0) {//맞으면 빨강으로 색전환
			KIND kind;
			m_Objects[i]->GetKind(&kind);
			if (kind != KIND_BULLET && kind != KIND_HERO) {
				//m_Objects[i]->SetColor(1.f, 0.f, 0.f);
				m_Sound->PlaySoundW(m_SoundFire, false, 3.f);
			}
		}
		else {//안맞으면 원래으로 색전환
			/*KIND kind;
			m_Objects[i]->GetKind(&kind);
			if (kind != KIND_BULLET)
				m_Objects[i]->SetColor(1.f, 1.f, 1.f);*/
		}
	}
}
void ScnMgr::ApplyForce(float x, float y,float z, DWORD eTime){
	STATE state;
	m_Objects[HERO_ID]->Getstate(&state);

	if (state == STATE_AIR) {
		z = 0.f;
	}
	m_Objects[HERO_ID]->ApplyForce(x, y, z, eTime);
}

void ScnMgr::DoGarbagecollet(){
	for (int i = 0; i < MAX_OBJECT; i++) {
		if (m_Objects[i] == NULL)
			continue;

		int hp;
		KIND kind;
		float vel, vx, vy, vz, px, py, pz;
		m_Objects[i]->GetHP(&hp);
		m_Objects[i]->GetKind(&kind);

		m_Objects[i]->GetVelocity(&vx, &vy, &vz);
		m_Objects[i]->Getpos(&px, &py, &pz);

		vel = sqrtf(vx*vx + vy * vy + vz * vz);

		//check velocity
		if (vel < FLT_EPSILON && kind == KIND_BULLET) {
			DeleteObject(i);
			continue;
		}

		//check HP
		if (hp <= 0 && kind && (kind == KIND_BULLET || kind == KIND_BUILDING)) {
			if(kind == KIND_BUILDING)				m_Sound->PlaySoundW(m_SoundEX, false, 3.f);
			DeleteObject(i);
			continue;
		}

		if (px < -BULLET_ACCESS_X || BULLET_ACCESS_X < px || py < -BULLET_ACCESS_Y || BULLET_ACCESS_Y < py) {
			if (kind == KIND_BULLET) {
				DeleteObject(i);
				continue;
			}
		}
	}
}

void ScnMgr::AddObject(float pX, float pY, float pZ, float hight, float sX, float sY, float vX, float vY,float vZ, KIND kind, int hp, STATE state){

	int index = FindObjectSlot();
	if (index < 0)	{
		cout << "Can't create object with minus index" << endl;
		return ;
	}
	m_Objects[index] = new Object();
	m_Objects[index]->Setpos(pX, pY, pZ);
	m_Objects[index]->SetHight(hight);
	m_Objects[index]->SetVelocity(vX, vY, vZ);
	m_Objects[index]->SetKind(kind);
	m_Objects[index]->SetAcc(0, 0, 0);
	m_Objects[index]->SetForce(0, 0);
	m_Objects[index]->SetSize(sX, sY);
	m_Objects[index]->SetMass(3.f);
	m_Objects[index]->SetFrictionCoef(5.f);
	m_Objects[index]->SetColor(1.f, 1.f, 1.f);
	m_Objects[index]->SetHP(hp);
	m_Objects[index]->Setstate(state);
}

void ScnMgr::DeleteObject(unsigned int id){
	if (m_Objects[id])	{
		delete m_Objects[id];
		m_Objects[id] = NULL;
	}
}

int ScnMgr::FindObjectSlot(){
	for (int i = 0; i < MAX_OBJECT; ++i)	{
		if (m_Objects[i] == NULL) return i;
	}

	cout << "objectList is full" << endl;
	return -1;
}

void ScnMgr::Shoot(int shootID, DWORD fTimeElapsed) {
	if (shootID == SHOOT_NONE)		return;
	Create_Bullet_sum += fTimeElapsed;
	if (Create_Bullet_sum < SHOOTING_TIME)	return;
	Create_Bullet_sum -= SHOOTING_TIME;
	
	float px, py, pz;
	float size_x, size_y;
	float hight;
	float sx, sy;
	float vx, vy, vz;

    //m_Objects 
	m_Objects[HERO_ID]->Getpos(&px, &py,&pz);
	m_Objects[HERO_ID]->GetSize(&size_x, &size_y);
	m_Objects[HERO_ID]->GetHight(&hight);
	m_Objects[HERO_ID]->GetVelocity(&vx, &vy, &vz);

	// 총알속도
	float amount = 15.f;
	
	switch (shootID){
	case SHOOT_LEFT:
			vx -= amount;
			vy += 0.f;
			break;
	case SHOOT_RIGHT:
		vx += amount;
		vy += 0.f;
		break;
	case SHOOT_UP:
		vx += 0.f;
		vy += amount;
		break;
	case SHOOT_DOWN:
		vx += 0.f;
		vy -= amount;
		break;
	}

	sx =  size_x * 3 / 5;
	sy =  size_x * 3 / 5;

	AddObject(px, py + size_y / 4, 0.1, hight, sx, sy, vx, vy, vz, KIND_BULLET, 1, STATE_GROUND);
	//m_Sound->PlaySoundW(m_SoundFire, false, 1.f);
}

bool ScnMgr::RRCollision(float minX, float maxX, float minY, float maxY, float minX1, float maxX1, float minY1, float maxY1){
	if (minX > maxX1) return false;
	if (maxX < minX1) return false;
	if (minY > maxY1) return false;
	if (maxY < minY1) return false;
	return true;
}

bool ScnMgr::IsCollision(float minx, float miny, float maxx, float maxy, float minx1, float miny1, float maxx1, float maxy1){
	if (maxx <= minx1)	return false;
	if (minx >= maxx1)	return false;
	if (maxy <= maxy1)	return false;
	if (miny >= maxy1)	return false;
	return true;
}

void ScnMgr::processCollision(int i, int j){
	
	Object* obj1 = m_Objects[i];
	Object* obj2 = m_Objects[j];

	if (obj1 == NULL || obj2 == NULL)	{
		std::cout << "obj" << i << " ,obj" << j << "\n";
	}

	KIND Kindobj1, kindobj2;
	obj1->GetKind(&Kindobj1);
	obj2->GetKind(&kindobj2);

	if (Kindobj1 == KIND_HERO || kindobj2 == KIND_HERO)	return;

	if (Kindobj1 == KIND_BUILDING && kindobj2 == KIND_BULLET){
		int hp1, hp2;
		obj1->GetHP(&hp1);
		obj2->GetHP(&hp2);
		int newHP = hp1 - hp2;
		obj1->SetHP(newHP);
		obj2->SetHP(0);
	}

	if (Kindobj1 == KIND_BULLET && kindobj2 == KIND_BUILDING) {
		int hp1, hp2;
		obj1->GetHP(&hp1);
		obj2->GetHP(&hp2);
		int newHP = hp2 - hp1;
		obj1->SetHP(0);
		obj2->SetHP(newHP);
	}
}