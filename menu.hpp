#ifndef MENU_HPP
#define MENU_HPP


#define BUTTON_COUNT 4
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Global variables
int mainMenuScreen;
int buttonImages[BUTTON_COUNT];
bool goToModeSelection = false;



struct Button {
	int x = 100;
	int y = 510;
	int width = 308;
	int height = 117;
	bool hover = false;
} buttons[BUTTON_COUNT];

// Draw menu or selected screen

void showMenu() {
		iShowImage(0, 0, 1280, 720, mainMenuScreen);
		for (int i = 0; i < BUTTON_COUNT; i++) {
			iShowImage(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, buttonImages[i]);
		}
}

//hover animation

void hoverAnimation(){
	iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mainMenuScreen);
	for (int i = 0; i < BUTTON_COUNT; i++){
		
			if (buttons[i].hover) iShowImage(buttons[i].x + 10, buttons[i].y + 10, buttons[i].width - 20, buttons[i].height - 20, buttonImages[i]);
			else iShowImage(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, buttonImages[i]);
		
	}
}

// mouse hover handler

void hover(int mx, int my){
	for (int i = 0; i < BUTTON_COUNT; i++){
		if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
			my >= buttons[i].y && my <= buttons[i].y + buttons[i].height){
			buttons[i].hover = true;
		}
		else buttons[i].hover = false;
	}
}

// Mouse click handler
void handleMenuClick(int mx, int my) {
	for (int i = 0; i < BUTTON_COUNT; i++){
		if (mx >= buttons[i].x && mx <= buttons[i].x + buttons[i].width &&
			my >= buttons[i].y && my <= buttons[i].y + buttons[i].height) {
			goToModeSelection = true;
		}
	}
		
}

// Load all images and set button positions

void loadMenuAssets() {

	mainMenuScreen = iLoadImage("BG/main.png");

	char imageSource[100];
	for (int i = 0; i < BUTTON_COUNT; i++) {
		sprintf_s(imageSource, "UiElements/button%d.png", (i + 1));
		buttonImages[i] = iLoadImage(imageSource);
		buttons[i].x = 100;
		buttons[i].y = 510 - i * 130;
		buttons[i].width = 308;
		buttons[i].height = 117;
		buttons[i].hover = false;
	}
}

#endif


