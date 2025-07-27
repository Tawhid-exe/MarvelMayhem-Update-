#include "iGraphics.h"
#include "menu.hpp"

int loadingScreen;

int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;

bool blinkTextWhite = true;

void iDraw()
{
	iClear();

	if (!goToMainMenu){
		// Show loading screen background
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		// Draw loading bar fill (white)
		iSetColor(255, 255, 255);
		iRectangle(390, 100, 500, 30);
		iFilledRectangle(390, 100, loadingBarWidth, 30);

		// If loading done, show text prompt
		if (loadingDone){
			if (blinkTextWhite) {
				iSetColor(255, 255, 255); // white
			}
			else {
				iSetColor(0, 0, 0); // black
			}
			iText(530, 150, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
		}
		else{
			iSetColor(255, 255, 255);
			iText(390, 140, "Loading...", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else{
		// Show main menu screen background after loading completes and user presses SPACE
		hoverAnimation();
	}
}

void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{

	hover(mx, my);
}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (goToMainMenu){
			handleMenuClick(mx, my);
		}
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

}

void loadingBar(){
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

void toggleBlinkColor() {
	blinkTextWhite = !blinkTextWhite;
}


int main()
{
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Marvel Mayhem");

	loadingScreen = iLoadImage("BG/loading.png");

	loadMenuAssets();

	iSetTimer(350, toggleBlinkColor); // 350 ms = 0.35 sec toggle

	iSetTimer(10, loadingBar);

	iStart();

	return 0;
}
