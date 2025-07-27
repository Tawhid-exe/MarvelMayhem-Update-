#ifndef MENU_HPP
#define MENU_HPP

#define BUTTON_COUNT 4
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Global variables
int mainMenuScreen;
int buttonImages[BUTTON_COUNT];
char* buttonNames[BUTTON_COUNT] = { "Play", "Settings", "About", "Exit" };
int currentScreen = -1;

struct Button {
	int x;
	int y ;
	int width;
	int height;
} buttons[BUTTON_COUNT];

// Draw menu or selected screen

void showMenu() {
	if (currentScreen == -1) {
		iShowImage(0, 0, 1280, 720, mainMenuScreen);
		for (int i = 0; i < BUTTON_COUNT; i++) {
			iShowImage(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, buttonImages[i]);
		}
	}
	else {
		iSetColor(255, 255, 255);
		iFilledRectangle(0, 0, 1280, 720);
		iSetColor(0, 0, 0);
		iText(1280 / 2 - 50, 720 / 2, buttonNames[currentScreen], GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

// Mouse handler

void handleMenuClick(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && currentScreen == -1) {
		for (int i = 0; i < BUTTON_COUNT; i++) {
			if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
				my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
				currentScreen = i;
			}
		}
	}
}

// Load all images and set button positions

void loadMenuAssets() {
	mainMenuScreen = iLoadImage("Images/ModeSelection.png");

	char path[100];
	int startY = 500;

	for (int i = 0; i < BUTTON_COUNT; i++) {
		//sprintf(path, "Images/s1.png", i + 1);
		buttonImages[i] = iLoadImage("Images/s1.png");

		buttons[i].x = 50;
		buttons[i].y = startY - i * 120;
		buttons[i].width = 200;
		buttons[i].height = 100;
	}
}

#endif
