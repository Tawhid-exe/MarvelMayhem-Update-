#include "iGraphics.h"
#include "menu.hpp"

int loadingScreen;


int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;

void iDraw()
{
	iClear();

	if (!goToMainMenu) {
		// Show loading screen
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		// Loading bar frame and fill
		iSetColor(255, 255, 255);
		iRectangle(390, 100, 500, 30);
		iFilledRectangle(390, 100, loadingBarWidth, 30);

		// Loading text
		if (loadingDone) {
			iText(530, 150, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iText(390, 140, "Loading...", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else {
		// Show the actual menu screen
		showMenu();
	}
}

void iMouseMove(int mx, int my)
{
	
}

void iPassiveMouseMove(int mx, int my)
{
	
}

void iMouse(int button, int state, int mx, int my) {
	if (goToMainMenu) {
		handleMenuClick(button, state, mx, my); // Handle clicks only after loading
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
	
	if (!loadingDone) {
		loadingBarWidth += 5;

		if (loadingBarWidth >= 500) {
			loadingBarWidth = 500;
			loadingDone = true;
		}
	}
	else {
		// Wait for SPACE to continue to menu
		if (isKeyPressed(' ')) {
			goToMainMenu = true;

			// Load menu assets only once
			if (mainMenuScreen == -1) {
				loadMenuAssets();
			}
		}
	}

}


int main()
{
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Marvel Mayhem");

	// Load the loading screen background image
	loadingScreen = iLoadImage("Images/LScreen.jpg");

	// Start the update timer
	iSetTimer(30, fixedUpdate);

	iStart(); // Start the graphics engine

	return 0;
}
