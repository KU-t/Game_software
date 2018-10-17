#include "stdafx.h"
#include "ScnMgr.h"
#include "time.h"

ScnMgr::ScnMgr()
{
	// Initialize Renderer
	m_Renderer = new Renderer(500, 500);

	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	m_TestTexture = m_Renderer->CreatePngTexture("./cat.png");

	//initialize
	for (int i = 0; i < MAX_OBJECT; i++) {
		m_Objects[i] = NULL;
	}
	m_Objects[HERO_ID] = new Object;
	m_Objects[HERO_ID]->SetPosition(0.f, 0.f, 0.f);
	m_Objects[HERO_ID]->SetVelocity(0.f, 0.f);
	m_Objects[HERO_ID]->SetAcc(0.f, 0.f);
	m_Objects[HERO_ID]->SetForce(0.f, 0.f);
	m_Objects[HERO_ID]->SetSize(1.f, 1.f);
	m_Objects[HERO_ID]->SetMass(0.1f);
	m_Objects[HERO_ID]->SetFrictionCoef(50.f);

	AddObject(1.f, 0.f, 1.f, 1.f, 1.f, 0.f, 0.f);
}


ScnMgr::~ScnMgr()
{
	delete m_Renderer;
	delete m_Objects[HERO_ID];
	delete m_Objects[MAX_OBJECT];
}


void ScnMgr::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	float x, y, z;
	m_Objects[HERO_ID]->GetPosition(&x, &y, &z);

	float width, height;
	m_Objects[HERO_ID]->GetSize(&width, &height);

	float vx, vy;
	m_Objects[HERO_ID]->GetVelocity(&vx, &vy);

	//m_TestObj->SetAcc((rand() / RAND_MAX)*10.f, (rand() / RAND_MAX)*10.f);
	// Renderer Test
	//m_Renderer->DrawSolidRect(x * 100.f, y * 100.f, 0, width * 100.f,height * 100, 0.5f, 0.5f, 0.5f, 1);

	//m_Renderer->DrawTextureRect(x * 100.f, y * 100.f, 0, width * 100.f, height * 100, 1.f, 1.f, 1.f, 1, m_TestTexture);
	
	m_Renderer->DrawTextureRectHeight(x * 100.f, y * 100.f, 0, width * 100.f, height * 100, 1.f, 1.f, 1.f, 1, m_TestTexture, z*100.f);

	for (int i = 1; i < MAX_OBJECT; i++) {
		if (m_Objects) {
			float x, y, z;
			m_Objects[i]->GetPosition(&x, &y, &z);

			float width, height;
			m_Objects[i]->GetSize(&width, &height);

			float vx, vy;
			m_Objects[i]->GetVelocity(&vx, &vy);

			//m_TestObj->SetAcc((rand() / RAND_MAX)*10.f, (rand() / RAND_MAX)*10.f);
			// Renderer Test
			//m_Renderer->DrawSolidRect(x * 100.f, y * 100.f, 0, width * 100.f,height * 100, 0.5f, 0.5f, 0.5f, 1);

			//m_Renderer->DrawTextureRect(x * 100.f, y * 100.f, 0, width * 100.f, height * 100, 1.f, 1.f, 1.f, 1, m_TestTexture);

			m_Renderer->DrawTextureRectHeight(x * 100.f, y * 100.f, 0, width * 100.f, height * 100, 1.f, 1.f, 1.f, 1, m_TestTexture, z*100.f);
		}
	}
}

float temp = 10.f;

void ScnMgr::Update(float eTimeInSec)
{
	for (int i = 0; i < MAX_OBJECT; i++) {
	
			m_Objects[i]->Update(eTimeInSec);
	}
	
}

void ScnMgr::ApplyForce(float x, float y, float eTime) {
	for (int i = 0; i < MAX_OBJECT; i++) {

		if (m_Objects)
			m_Objects[i]->ApplyForce(x, y, eTime);
	}
}

void ScnMgr::AddObject(float px, float py, float pz, float sx, float sy, float vx, float vy) {
	int index = FindEmptyObjectSlot();
	
	if (index < 0) {
		std::cout << " Can't create object";
		return;
	}

	// 여기만 바꾸면 되
	m_Objects[HERO_ID] = new Object;
	m_Objects[HERO_ID]->SetPosition(px, py, pz);
	m_Objects[HERO_ID]->SetVelocity(vx, vy);
	m_Objects[HERO_ID]->SetAcc(0.f, 0.f);
	m_Objects[HERO_ID]->SetForce(0.f, 0.f);
	m_Objects[HERO_ID]->SetSize(sx, sy);
	m_Objects[HERO_ID]->SetMass(0.1f);
	m_Objects[HERO_ID]->SetFrictionCoef(50.f);
}

void ScnMgr::DeleteObject(unsigned int id) {
	if (m_Objects[id]) {
		delete m_Objects[id];
		m_Objects[id] = NULL; // 중요 !!!!!!!!!!!!!!!!!!!!!!!
	}
}

int ScnMgr::FindEmptyObjectSlot() {
	for (int i = 0; i < MAX_OBJECT; i++) {
		if (m_Objects[i] == NULL)
			return i;
	}
	std::cout << "Object list if full. \n";
	return -1;
}