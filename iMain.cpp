#include "iGraphics.h"
#include "menu.hpp"

int loadingScreen;

// Loading screen variables
int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;


void iDraw()
{
	iClear();

	if (!goToMainMenu)
	{
		// Show loading screen
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		// Loading bar frame and fill
		iSetColor(255, 255, 255);
		iRectangle(390, 100, 500, 30);
		iFilledRectangle(390, 100, loadingBarWidth, 30);

		// Loading text
		if (loadingDone)
		{
			iText(530, 150, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
		}
		else
		{
			iText(390, 140, "Loading...", GLUT_BITMAP_HELVETICA_18);
		}
	}
	else
	{
		// Show the actual menu screen after loading
		showMenu();
	}
}


void iMouseMove(int mx, int my)
{
	
}


void iPassiveMouseMove(int mx, int my)
{
	
	if (goToMainMenu) {
		// By default, assume nothing is hovered
		hoveredButtonIndex = -1;
		hoveredOptionButtonIndex = -1;
		backButtonHover = false;

		if (currentScreen == -1) { // On the main menu
			for (int i = 0; i < BUTTON_COUNT; i++) {
				if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
					my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
					hoveredButtonIndex = i;
					break;
				}
			}
		}
		else if (currentScreen == 0) { // On the Play Sub-Menu
			// hover for the two option buttons
			for (int i = 0; i < 2; i++) {
				if (mx >= optionButtons[i].x && mx <= optionButtons[i].x + optionButtons[i].width &&
					my >= optionButtons[i].y && my <= optionButtons[i].y + optionButtons[i].height) {
					hoveredOptionButtonIndex = i;
					return; // Exit after finding a hover
				}
			}
			//hover for the back button
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				backButtonHover = true;
			}
		}
		else { // On any other sub-screen (Settings, About, Option 1, Option 2)
			// back button hover
			if (mx >= backButton.x && mx <= backButton.x + backButton.width &&
				my >= backButton.y && my <= backButton.y + backButton.height) {
				backButtonHover = true;
			}
		}
	}
}


void iMouse(int button, int state, int mx, int my)
{
	if (goToMainMenu)
	{
		// Handle menu clicks only after the loading screen
		handleMenuClick(button, state, mx, my);
	}
}


void iSpecialKeyboard(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	
}

// This function runs at a fixed interval
void fixedUpdate()
{
	// Game logic can go here for player movement etc.
	if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP)) {}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {}
	if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {}
	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {}

	// Handles the loading bar animation
	if (!loadingDone)
	{
		loadingBarWidth += 5;
		if (loadingBarWidth >= 500)
		{
			loadingBarWidth = 500;
			loadingDone = true;
		}
	}
	else
	{
		// Wait for SPACE bar to continue to the main menu
		if (isKeyPressed(' '))
		{
			goToMainMenu = true;

			// Load menu 
			if (mainMenuScreen == -1)
			{
				loadMenuAssets();
			}
		}
	}
}

int main()
{
	// Initialize the update timer
	iSetTimer(30, fixedUpdate);

	// Initialize graphics window
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Marvel Mayhem");

	//loading screen background image
	loadingScreen = iLoadImage("Images/LScreen.jpg");

	iStart(); // Start the graphics engine

	return 0;
}