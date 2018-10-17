/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "ScnMgr.h"

using namespace std;

ScnMgr *g_ScnMgr = NULL;

DWORD g_PrevRenderTime = 0;

bool g_KeyW = false;
bool g_KeyA = false;
bool g_KeyS = false;
bool g_KeyD = false;


void RenderScene(void)
{

	if (g_PrevRenderTime == 0) //Initialize
	{
		g_PrevRenderTime = timeGetTime();
	}
	//Elapsed Time
	DWORD currentTime = timeGetTime();
	DWORD elapseTime = currentTime - g_PrevRenderTime;
	g_PrevRenderTime = currentTime;
	float eTime = (float)elapseTime; //convert to second

	float forcex = 0.f, forcey = 0.f;
	float amount = 100.0f;

	if (g_KeyW)	forcey -= amount;
	if (g_KeyS)	forcey += amount;
	if (g_KeyA)	forcex += amount;
	if (g_KeyD)	forcex -= amount;

	g_ScnMgr->ApplyForce(forcex, forcey, eTime);

	g_ScnMgr->RenderScene();
	g_ScnMgr->Update(eTime);


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene(); // 1초에 60번이상 동작해야함.
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}

void KeyDownInput(unsigned char key, int x, int y) {

	switch (key) {
	case 'w': case'W':
		g_KeyW = true;

		break;

	case 'a': case'A':
		g_KeyA = true;

		break;

	case 's': case'S':
		g_KeyS = true;

		break;

	case 'd': case'D':
		g_KeyD = true;

		break;
	}
}

void KeyUpInput(unsigned char key, int x, int y) {
	switch (key) {
	case 'w': case'W':
		g_KeyW = false;

		break;

	case 'a': case'A':
		g_KeyA = false;

		break;

	case 's': case'S':
		g_KeyS = false;

		break;

	case 'd': case'D':
		g_KeyD = false;

		break;
	}
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

	g_ScnMgr = new ScnMgr;

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();


	delete g_ScnMgr;

    return 0;
}

