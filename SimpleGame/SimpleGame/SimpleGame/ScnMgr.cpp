#include "stdafx.h"
#include "ScnMgr.h"

float g_Time = 0;
float temp = 10;
int g_Seq = 0;
ScnMgr::ScnMgr()
{


	//Initialize Renderer
	/*m_TestObj = new Object();
	m_TestObj->Setpos(0.f, 0.f, 0.5f);
	m_TestObj->SetVelocity(0, 0);
	m_TestObj->SetAcc(0, 0);
	m_TestObj->SetForce(0, 0);
	m_TestObj->SetSize(1.f, 1.f);
	m_TestObj->SetMass(3.f);
	m_TestObj->SetFrictionCoef(5.f);*/

	//Init Object list
	for (int i = 0; i < MAX_OBJECT; ++i) m_Objects[i] = NULL;


	//Create HeroObj
	m_Objects[HERO_ID] = new Object();
	m_Objects[HERO_ID]->Setpos(0, 0, 0.f);
	m_Objects[HERO_ID]->SetVelocity(0, 0);
	m_Objects[HERO_ID]->SetAcc(0, 0);
	m_Objects[HERO_ID]->SetForce(0, 0);
	m_Objects[HERO_ID]->SetSize(1.f, 1.f);
	m_Objects[HERO_ID]->SetMass(1.f);
	m_Objects[HERO_ID]->SetFrictionCoef(0.2f);
	m_Objects[HERO_ID]->SetKind(KIND_HERO);

	/*for (int i = 0; i < MAX_OBJECT; ++i)
	{
		x = rand() % 500;
		y = rand() % 500;
		m_Objects[i].Setpos(x, y, z);
		m_Objects[i].SetVelocity(0, 0);
		m_Objects[i].SetAcc(0, 0);
		m_Objects[i].SetForce(0, 0);
		m_Objects[i].SetSize(1.f, 1.f);
		m_Objects[i].SetMass(3.f);
		m_Objects[i].SetFrictionCoef(5.f);
	}*/
	//TEST ADDOBJ
	AddObject(1.0f, 0.0f, 0.f, 1.f, 1.f, 0.f, 0.f);

	m_Renderer = new Renderer(500, 500);

	if (!m_Renderer->IsInitialized()) {
		std::cout << "Renderer could not be initialized.. \n";
	}

	m_testTexture = m_Renderer->CreatePngTexture("cat.png"); //클래스나 구조체 형식으로 넘길 수 있게
	m_explosionTexture = m_Renderer->CreatePngTexture("spritesheet1.png"); //클래스나 구조체 형식으로 넘길 수 있게


}


ScnMgr::~ScnMgr()
{
}

void ScnMgr::RenderScene()
{
	
	//g_TestObj->Getpos(&x, &y);
	//g_TestObj->GetSize(&width, &height);

	// dirty: 더러워졌을때 업뎃
	// 실시간으로 그리는건 무조건 1초에 60번씩. 계속update해야함. 1초에 60번 이상.
	// 27.5프레임 영사기 영화가. 현재 하드웨어는 60정도. 휴대폰도 60. 60최초로 한회사는 애플의아이폰.
	// 60번이상 호출이 되어야. 렌더씬 안에선 16밀리세컨안에 작업완료되어야. 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f); 
	//바탕색 바꾸기

	// 센터 0,0 -250 ~ 250
	// Renderer Test

	//static 불리고 안불리고의 차이?
	//원그리기
	//x = sin(g_Time)*100.f;
	//y = cos(g_Time)*100.f;
	//g_Time += 0.01f;
	//float cur_y = 0, cur_x = 0;
	//float x, y, z;
	//m_TestObj->Getpos(&x, &y, &z);
	//float width , height;
	//m_TestObj->GetSize(&width, &height);
	//1m --> 100pixel
	//m_Renderer->DrawSolidRect(x, y, 0, 1, 10, 0, 1, 1); // 네모 속성 바꾸기 가능

	//m_Renderer->DrawSolidRect(x*100.f, y*100.f, 0, width*100.f,height*100.f, 1, 1, 1, 1); // 네모 속성 바꾸기 가능
	//m_Renderer->DrawTextureRect(x*100.f, y*100.f, 0, width*100.f, height*100.f, 1, 1, 1, 1, m_testTexture); // 네모 속성 바꾸기 가능

	if (g_Seq > 80) g_Seq = 0;

	for (int i = 0; i < MAX_OBJECT; ++i)
	{
		if (m_Objects[i] != NULL)
		{
			float x, y, z;
			m_Objects[i]->Getpos(&x, &y, &z);
			
			float width, height;
			m_Objects[i]->GetSize(&width, &height);
			
			
			float newZ = z * 100;
			float newH = height * 100;
			float newW = width * 100;

			int seqX = 0;
			int seqY = 0;
			seqX = g_Seq % 9;
			seqY = (int)g_Seq / 9;
			g_Seq++;
			if (g_Seq > 80) g_Seq = 0;

			m_Renderer->DrawTextureRectHeight(x*100.f, y*100.f, 0, width*100.f, height*100.f, 1, 1, 1, 1, m_testTexture, z * 100.f); // 네모 속성 바꾸기 가능

			m_Renderer->DrawTextureRectSeqXY(x*100.f, y*100.f + 100.f, newZ, newH, newW, 1, 1, 1, 1, m_explosionTexture, seqX, seqY, 9, 9);
		}
	}
	//cout << x << y << width << height << endl;
	//cout<<m_TestObj->Getpos<<m_TestObj->GetSize<<
	//set하기 x그리는곳에선 그리는거만. 
	//걷는건 3000 m/s
}
void ScnMgr::Update(float fTimeElapsed)
{
	// 업데이트에서 현재 속도 겟한다음
	// 현재 포지션 + 속도 * 시간
	// 속도 set
	// 시간: 1/60f
	for (int i = 0; i < MAX_OBJECT; ++i)
	{
		if(m_Objects[i]) m_Objects[i]->Update(fTimeElapsed);
	}
	/*float x = 0, y = 0;
	m_TestObj->Getpos(&x, &y);
	float vx = 0, vy = 0;
	m_TestObj->GetVelocity(&vx, &vy);
	float dstx, dsty;
	dstx = x + vx * (1.f / 60.0f);
	dsty = y + vy * (1.f / 60.0f);*/
	//dstx = dstx * 100.0f;
	//dsty = dsty * 100.0f;

	// 왜 프레임이 달라? 코드상에서 제약 걸어놓지 않아도 유지가 되기도 한다. 노트북마다 다달라
	// 이걸 어떻게 해결? 1. 업데이트or 렌더씬을 강제로 1/60에만 그려지게 막는다. 
	// 5더하는거 5근본없음. 업데이트안에서 시간고려하지 않는거 별로. 
	// 노트북은 적당한 속도 튜닝해도 강의실pc랑은 다르고.
	// 유근본 --> 공통적으로 적용되는 법칙. 물리법칙. 
	//m_TestObj->SetSize(10, 10);
	////m_TestObj->Setpos(x + t * tempSpeed, y + t * tempSpeed);
	//m_TestObj->Setpos(dstx, dsty);

	//if (temp > 100.f) 
	//	temp = 0.0f;
	// 한 픽셀은 1cm 픽셀단위로 받게 되어 있음. 좌표가 00인 미터단위의 위치
	//속도도 m/s, 위치도 m 현재위치에서 계산된게 1m다 하면 
}
void ScnMgr::ApplyForce(float x, float y, DWORD eTime)
{
	//for (int i = 0; i<MAX_OBJECT; ++i)
	//	m_Objects[i]->ApplyForce(x, y, eTime);
	m_Objects[HERO_ID]->ApplyForce(x, y, eTime);

	//m_TestObj->ApplyForce(x, y, eTime);
}

void ScnMgr::AddObject(float pX, float pY, float pZ, float sX, float sY, float vX, float vY)
{

	int index = FindObjectSlot();

	if (index < 0)
	{
		cout << "Can't create object with minus index" << endl;
		return ;
	}
	//m_Objects[index] = new Object();

	m_Objects[index] = new Object();
	m_Objects[index]->Setpos(pX, pY, pZ);
	m_Objects[index]->SetVelocity(vX, vY);
	m_Objects[index]->SetAcc(0, 0);
	m_Objects[index]->SetForce(0, 0);
	m_Objects[index]->SetSize(sX, sY);
	m_Objects[index]->SetMass(3.f);
	m_Objects[index]->SetFrictionCoef(5.f);

}

void ScnMgr::DeleteObject(unsigned int id)
{
	if (m_Objects[id])
	{
		delete m_Objects[id];
		m_Objects[id] = NULL;
	}
}

int ScnMgr::FindObjectSlot()
{
	for (int i = 0; i < MAX_OBJECT; ++i)
	{
		if (m_Objects[i] == NULL) return i;
	}

	cout << "objectList is full" << endl;
	return -1;
}

void ScnMgr::Shoot(int shootID) {
	if (shootID == SHOOT_NONE)		return;
	float px, py, pz;
	float sx, sy;
	float vx, vy;

//	m_Objects
	m_Objects[HERO_ID]->Getpos(&px, &py,&pz);
	sx = 0.1f;
	sy = 0.1f;

	m_Objects[HERO_ID]->GetVelocity(&vx, &vy);
	// 총알속도
	float amount = 10.f;
	switch (shootID){
	case SHOOT_LEFT:
			vx -= amount;
			vy += amount;
			break;
	case SHOOT_RIGHT:
		vx += amount;
		vy += amount;
		break;
	case SHOOT_UP:
		vx += amount;
		vy += amount;
		break;
	case SHOOT_DOWN:
		vx += amount;
		vy -= amount;
		break;
	}


	AddObject(px, py, pz, sx, sy, vx, vy);
}

