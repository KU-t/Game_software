/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "ScnMgr.h"

//ScnMgr* a;
//int a;
//int a = 50;
DWORD g_prevElipsedTime = 0.f;
ScnMgr *g_ScnMgr = NULL;
bool g_KeyW = false;
bool g_KeyA = false;
bool g_KeyS = false;
bool g_KeyD = false;


void RenderScene(void)
{
	if (g_prevElipsedTime == 0.f) g_prevElipsedTime = timeGetTime(); //Init

	//get ElipsedTime
	DWORD cur_fimeElapsed = timeGetTime();
	DWORD fTimeElapsed = cur_fimeElapsed - g_prevElipsedTime;// timeGetTime() - g_prevElipsedTime;
	g_prevElipsedTime = cur_fimeElapsed;
	float eTiME = (float)fTimeElapsed / 1000.f; // convet to sec

	//g_ScnMgr->ApplyForce()
	float forceX= 0.f, forceY = 0.f;
	float amount = 0.002f;
	if (g_KeyW)
	{
		forceY += amount;
	}
	if (g_KeyD)
	{
		forceX += amount;
	}
	if (g_KeyA)
	{
		forceX -= amount;
	}
	if (g_KeyS)
	{
		forceY -= amount;
	}
	g_ScnMgr->ApplyForce(forceX, forceY, fTimeElapsed);
	g_ScnMgr->RenderScene();
	g_ScnMgr->Update(eTiME);
	//cout << "elapsedTime" << eTiME << endl;
	/*float fimeElapsed = timeGetTime();*/
	glutSwapBuffers();

}

void Idle(void)
{
	// 아무것도 안했을 때 계속 렌더씬 불러줌
	//float fTimeElapsed = timeGetTime();
	//if (g_prevElipsedTime < 0.f) g_prevElipsedTime = timeGetTime(); //Init

	//																//get ElipsedTime
	//float cur_fimeElapsed = timeGetTime();
	//float fTimeElapsed = cur_fimeElapsed - g_prevElipsedTime;// timeGetTime() - g_prevElipsedTime;
	//g_prevElipsedTime = cur_fimeElapsed;
	//fTimeElapsed /= 1000.f; // convet to sec

	//g_ScnMgr->Update(fTimeElapsed);
	// 1초에 60번이상 동작해야함.
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyDownInput(unsigned char key, int x, int y)
{
	//key 값과 그때의 마우스값
	//if (key == 'w') cout << "지금 w가 눌렸음 이때 x, y " << x << ", " << y<<")";
	/*int amount = 5;
	switch (key)
	{
	case 'W':
	case 'w':
		cout << "w" << endl;
		cur_y += 5;
		break;
	case 'S':
	case 's':
		cout << "s" << endl;

		cur_y -= 5;
		break;
	case 'D':
	case 'd':
		cout << "d" << endl;
		cur_x += 5;
		break;
	case 'A':
	case 'a':
		cout << "a" << endl;
		cur_x -= 5;
		break;
	}*/

	switch (key)
	{
	case 'w':
	case 'W':
		g_KeyW = true;
		cout << "W: " << g_KeyW << "A: " << g_KeyA << "S: " << g_KeyS << "D: " << g_KeyD << endl;

		//g_ScnMgr->ApplyForce(0.f, amount);
		break;
	case 'a':
	case 'A':
		g_KeyA = true;
		cout << "W: " << g_KeyW << "A: " << g_KeyA << "S: " << g_KeyS << "D: " << g_KeyD << endl;

		//g_ScnMgr->ApplyForce(-amount, 0.f);
		break;
	case 's':
	case 'S':
		g_KeyS = true;
		cout << "W: " << g_KeyW << "A: " << g_KeyA << "S: " << g_KeyS << "D: " << g_KeyD << endl;

		//g_ScnMgr->ApplyForce(0.f, -amount);
		break;
	case 'd':
	case 'D':
		g_KeyD = true;
		cout << "W: " << g_KeyW << "A: " << g_KeyA << "S: " << g_KeyS << "D: " << g_KeyD << endl;

		//g_ScnMgr->ApplyForce(amount, 0.f);
		break;
	}
	
	//RenderScene();
}
void KeyUpInput(unsigned char key, int x, int y)
{
	//key 값과 그때의 마우스값
	//if (key == 'w') cout << "지금 w가 눌렸음 이때 x, y " << x << ", " << y<<")";
	/*int amount = 5;
	switch (key)
	{
	case 'W':
	case 'w':
	cout << "w" << endl;
	cur_y += 5;
	break;
	case 'S':
	case 's':
	cout << "s" << endl;

	cur_y -= 5;
	break;
	case 'D':
	case 'd':
	cout << "d" << endl;
	cur_x += 5;
	break;
	case 'A':
	case 'a':
	cout << "a" << endl;
	cur_x -= 5;
	break;
	}*/


	//float amount = 4.f;
	switch (key)
	{
	case 'w':
	case 'W':
		g_KeyW = false;
		break;
	case 'a':
	case 'A':
		g_KeyA = false;
		break;
	case 's':
	case 'S':
		g_KeyS = false;
		break;
	case 'd':
	case 'D':
		g_KeyD = false;
		break;
	}

	//RenderScene();
}
void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize ScnMgr
	//ScnMnr.Init();

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_ScnMgr = new ScnMgr;
	glutMainLoop();
	//timeGettime
	delete g_ScnMgr;

    return 0;
}

