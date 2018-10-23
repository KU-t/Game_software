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
	m_TestObj = new Object;
	m_TestObj->SetPosition(0.f, 0.f, 0.f);
	m_TestObj->SetVelocity(0.f, 0.f);
	m_TestObj->SetAcc(0.f, 0.f);
	m_TestObj->SetForce(0.f, 0.f);
	m_TestObj->SetSize(1.f, 1.f);
	m_TestObj->SetMass(0.1f);
	m_TestObj->SetFrictionCoef(50.f);

	for (int i = 0; i < MAX_OBJECT; i++) {

		/*m_Objects[i] = new Object;
		m_Objects[i]->SetPosition((float)(rand()%400/100) - 2.f, (float)(rand() % 400/100) - 2.f, 0.f);
		m_Objects[i]->SetVelocity(0.f, 0.f);
		m_Objects[i]->SetAcc(0.f, 0.f);
		m_Objects[i]->SetForce(0.f, 0.f);
		m_Objects[i]->SetSize(1.f, 1.f);
		m_Objects[i]->SetMass(0.1f);
		m_Objects[i]->SetFrictionCoef(50.f);*/
	}
}


ScnMgr::~ScnMgr()
{
	delete m_Renderer;
	delete m_TestObj;
	//delete m_Objects[MAX_OBJECT];
}


void ScnMgr::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	float x, y, z;
	m_TestObj->GetPosition(&x, &y, &z);

	float width, height;
	m_TestObj->GetSize(&width, &height);

	float vx, vy;
	m_TestObj->GetVelocity(&vx, &vy);

	//m_TestObj->SetAcc((rand() / RAND_MAX)*10.f, (rand() / RAND_MAX)*10.f);
	// Renderer Test
	//m_Renderer->DrawSolidRect(x * 100.f, y * 100.f, 0, width * 100.f,height * 100, 0.5f, 0.5f, 0.5f, 1);

	//m_Renderer->DrawTextureRect(x * 100.f, y * 100.f, 0, width * 100.f, height * 100, 1.f, 1.f, 1.f, 1, m_TestTexture);
	/*for (int i = 0; i < MAX_OBJECT; i++) {
		float x, y, z;
		m_Objects[i]->GetPosition(&x, &y, &z);

		float width, height;
		m_Objects[i]->GetSize(&width, &height);

		float vx, vy;
		m_Objects[i]->GetVelocity(&vx, &vy);

		m_Renderer->DrawTextureRectHeight(x * 100.f, y * 100.f, 0, width * 100.f, height * 100, 1.f, 1.f, 1.f, 1, m_TestTexture, z*100.f);
	}*/
	m_Renderer->DrawTextureRectHeight(x * 100.f, y * 100.f, 0, width * 100.f, height * 100, 1.f, 1.f, 1.f, 1, m_TestTexture, z*100.f);
}

float temp = 10.f;

void ScnMgr::Update(float eTimeInSec)
{
	m_TestObj->Update(eTimeInSec);
}

void ScnMgr::ApplyForce(float x, float y, float eTime) {
	m_TestObj->ApplyForce(x, y, eTime);
}