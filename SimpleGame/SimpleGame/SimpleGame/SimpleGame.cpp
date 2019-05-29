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
#include "Global.h"

DWORD g_prevElipsedTime = 0.f;
ScnMgr *g_ScnMgr = NULL;

bool g_KeyW = false;
bool g_KeyA = false;
bool g_KeyS = false;
bool g_KeyD = false;
bool g_KeySP = false;

// bullet
SHOOT_ g_Shoot = SHOOT_NONE;
int type = 0;
bool exist = false;

void RenderScene(void){
	if (g_prevElipsedTime == 0.f) g_prevElipsedTime = timeGetTime(); //Init

	//get ElipsedTime
	DWORD cur_fimeElapsed = timeGetTime();
	DWORD fTimeElapsed = cur_fimeElapsed - g_prevElipsedTime;// timeGetTime() - g_prevElipsedTime;
	g_prevElipsedTime = cur_fimeElapsed;
	float eTiME = (float)fTimeElapsed / 1000.f; // convet to sec

	//g_ScnMgr->ApplyForce()
	float forceX= 0.f, forceY = 0.f, forceZ = 0.f;
	float amount = 0.003f;
	float amountz = 0.5f;

	if (g_KeyW)	forceY += amount;
	if (g_KeyD)	forceX += amount;
	if (g_KeyA)	forceX -= amount;
	if (g_KeyS)	forceY -= amount;
	if (g_KeyS)	forceY -= amount;
	//if (g_KeySP) forceZ += amountz;
	
	g_ScnMgr->ApplyForce(forceX, forceY, forceZ, fTimeElapsed);
	g_ScnMgr->RenderScene();
	g_ScnMgr->Shoot(g_Shoot, fTimeElapsed);
	g_ScnMgr->Update(eTiME);
	g_ScnMgr->UpdateCollision();
	g_ScnMgr->DoGarbagecollet();

	glutSwapBuffers();
}

void Idle(void){
	RenderScene();
}

void MouseInput(int button, int state, int x, int y){
	RenderScene();
}

void KeyDownInput(unsigned char key, int x, int y){
	switch (key)	{
	case 'w':	case 'W':		 g_KeyW = true;
		break;
	case 'a':	case 'A':		 g_KeyA = true;
		break;
	case 's':	case 'S':		 g_KeyS = true;
		break;
	case 'd':	case 'D':		 g_KeyD = true;
		break;
	case ' ':	

			g_KeySP = true;

		break;
	}
}

void KeyUpInput(unsigned char key, int x, int y){
	switch (key)	{
	case 'w':	case 'W':		 g_KeyW = false;
		break;
	case 'a':	case 'A':		 g_KeyA = false;
		break;
	case 's':	case 'S':		 g_KeyS = false;
		break;
	case 'd':	case 'D':		 g_KeyD = false;
		break;
	case ' ':		g_KeySP = false;
		break;
	}
}

void SpecialKeyDownInput(int key, int x, int y){
	switch (key){
	case GLUT_KEY_LEFT:		 g_Shoot = SHOOT_LEFT;
		break;
	case GLUT_KEY_RIGHT:		 g_Shoot = SHOOT_RIGHT;
		break;
	case GLUT_KEY_UP:		 g_Shoot = SHOOT_UP;
		break;
	case GLUT_KEY_DOWN:	 g_Shoot = SHOOT_DOWN;
		break;
	}
}

void SpecialKeyUpInput(int key, int x, int y){
	g_Shoot = SHOOT_NONE;
}

int main(int argc, char **argv){
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else	{
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
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);


	g_ScnMgr = new ScnMgr;

	glutMainLoop();
	//timeGettime

	delete g_ScnMgr;

    return 0;
}

