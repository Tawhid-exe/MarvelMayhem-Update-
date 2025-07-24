#include "iGraphics.h"

int loadingScreen;
int mainMenuScreen;

int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;

void iDraw()
{
	iClear();

	if (!goToMainMenu){
		// Show loading screen background
		iShowImage(0, 0, 1280, 720, loadingScreen);
		

		// Draw loading bar fill (white)
		iSetColor(255, 255, 255);
		iRectangle(390, 100, 500, 30);
		iFilledRectangle(390, 100, loadingBarWidth, 30);

		// If loading done, show text prompt
		if (loadingDone){
			iSetColor(255, 255, 255);
			iText(530, 150, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
		}
		else{
			iSetColor(255, 255, 255);
			iText(390, 140, "Loading...", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else{
		// Show main menu screen background after loading completes and user presses SPACE
		iShowImage(0, 0, 1280, 720, mainMenuScreen);
	}
}

void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

void fixedUpdate()
{
	if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP))
	{

	}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
	{

	}
	if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN))
	{

	}
	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
	{

	}
	
	if (!loadingDone){

		loadingBarWidth += 5;
		if (loadingBarWidth >= 500){
			loadingBarWidth = 500;
			loadingDone = true;
		}
	}

	else{
		if (isKeyPressed(' ')){
			goToMainMenu = true;
		}
	}

}


int main()
{
	iInitialize(1280, 720, "Marvel Mayhem");

	loadingScreen = iLoadImage("BG/loading.png");

	mainMenuScreen = iLoadImage("BG/main.png");

	iSetTimer(30, fixedUpdate);

	iStart();

	return 0;
}
