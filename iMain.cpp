#include "iGraphics.h"
#include "menu.hpp"
#include "character.hpp"
#include "pause.hpp"

#include "ai.hpp"	
#include "arcade.hpp" 

Character captainAmericaP1;
Character captainAmericaP2;
int loadingScreen;

// Loading screen variables
int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;
bool blinkTextWhite = true;
static bool assetsLoaded = false;

int previousScreen = -1; // To track screen transitions

// had to declare the function definition here otherwise it was not working 
void loadingScreenText();

void iDraw()
{
	iClear();

	if (!goToMainMenu)
	{
		// Show loading screen
		iShowImage(0, 10, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		startMainMenuMusic(); // Starting Main Menu Music

		// Loading bar frame and fill
		iSetColor(255, 60, 60);
		iRectangle(390, 35, 500, 25);
		iFilledRectangle(390, 35, loadingBarWidth, 25);
		loadingScreenText();
	}
	else
	{
		// Show the actual menu screen after loading
		showMenu();
		
		// On the gameplay screen, render Character
		if (currentScreen == 20){
			showArenaImages();
			if(selectedCharacterIndexP1 == 2) captainAmericaP1.draw();
			if(selectedCharacterIndexP2 == 2) captainAmericaP2.draw();


			// paused button
			iShowImage(pauseButton.x, pauseButton.y, pauseButton.width, pauseButton.height, pauseButtonImage);

			// If the game is paused, show the pause menu
			if (currentGameState == PAUSED) {
				showPauseMenu();
			}
		}
		// Logic for Arcade Mode Screen (30)
		else if (currentScreen == 30) {
			// Check if we just entered the arcade screen to load characters once
			if (previousScreen != 30) {
				loadArcadeCharacters();
			}

			drawArcadeScene();

			// Show pause button in Arcade Mode
			iShowImage(pauseButton.x, pauseButton.y, pauseButton.width, pauseButton.height, pauseButtonImage);

			// If the game is paused, show the pause menu
			if (currentGameState == PAUSED) {
				showPauseMenu();
			}
		}

	}

	// Update previous screen state at the end of the draw call
	previousScreen = currentScreen;
}

void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{
	if (goToMainMenu) {
		// If in game and paused, handle pause menu hover
		if ((currentScreen == 20 || currentScreen == 30) && currentGameState == PAUSED) {
			handlePauseHoverAnimation(mx, my);
		}
		else {
			// Handle main menu hover Animation
			handleHoverAnimation(mx, my);
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (goToMainMenu) {
		if (currentScreen == 20) { // Clicks inside the arena screen
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (currentGameState == PAUSED) {
					// If paused, check for clicks on the pause menu
					int clickedButtonIndex = handlePauseMenuClick(mx, my);
					if (clickedButtonIndex == 0) { // Resume
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 1) { // Restart
						resetCharacters(captainAmericaP1, captainAmericaP2);
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 2) { // Character Selection
						resetCharacters(captainAmericaP1, captainAmericaP2);
						currentScreen = 10; // Go back to character selection
						currentGameState = PLAYING; // Reset state for next time
					}
				}
				else {
					// If playing, check for clicks on the main pause button
					if (mx >= pauseButton.x && mx <= pauseButton.x + pauseButton.width &&
						my >= pauseButton.y && my <= pauseButton.y + pauseButton.height) {
						currentGameState = PAUSED;
					}
				}
			}
		}

			// Clicks inside the Arcade Mode arena screen
		else if (currentScreen == 30) {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (currentGameState == PAUSED) {
					// If paused, check for clicks on the pause menu
					int clickedButtonIndex = handlePauseMenuClick(mx, my);
					if (clickedButtonIndex == 0) { // Resume
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 1) { // Restart
						resetArcadePlayer(arcadePlayer, arcadeAI);
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 2) { // Character Selection
						resetArcadePlayer(arcadePlayer, arcadeAI);
						currentScreen = 11; // Go back to arcade character selection
						currentGameState = PLAYING; // Reset state for next time
					}
				}
				else {
					// If playing, check for clicks on the main pause button
					if (mx >= pauseButton.x && mx <= pauseButton.x + pauseButton.width &&
						my >= pauseButton.y && my <= pauseButton.y + pauseButton.height) {
						currentGameState = PAUSED;
					}
				}
			}
		}
		else {
			// Handle menu clicks only after the loading screen
			handleMenuClick(button, state, mx, my);
		}
	}
}

// This function runs at a fixed interval
// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

void fixedUpdate() {
	if (!goToMainMenu || currentGameState == PAUSED) return;

	// Versus Mode (screen 20) - Both players
	if (currentScreen == 20) {
		// Player 1 controls (WASD + FEQ)
		handleInputMovement(captainAmericaP1, isKeyPressed('d'), isKeyPressed('a'));
		handleDefaultState(captainAmericaP1, isKeyPressed('d'), isKeyPressed('a'));
		handleJump(captainAmericaP1, isKeyPressed('w'));
		handleAttack(captainAmericaP1, isKeyPressed('f'));
		handleUltimate(captainAmericaP1, isKeyPressed('q'));


		// Player 2 controls (Arrow keys + )
		handleInputMovement(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_RIGHT), isSpecialKeyPressed(GLUT_KEY_LEFT));
		handleDefaultState(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_RIGHT), isSpecialKeyPressed(GLUT_KEY_LEFT));
		handleJump(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_UP));
		handleAttack(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_DOWN));
		handleUltimate(captainAmericaP2, isKeyPressed('0'));

	}

	// Arcade Mode Controls
	else if (goToMainMenu && currentScreen == 30 && currentGameState != PAUSED) {
		// Player controls
		handleInputMovement(arcadePlayer, isKeyPressed('d'), isKeyPressed('a'));
		handleDefaultState(arcadePlayer, isKeyPressed('d'), isKeyPressed('a'));
		handleJump(arcadePlayer, isKeyPressed('w'));
		handleAttack(arcadePlayer, isKeyPressed('f'));
		handleUltimate(arcadePlayer, isKeyPressed('q'));
=======
#include "ai.hpp"
#include "arcade.hpp" 

Character captainAmericaP1;
Character captainAmericaP2;

int loadingScreen;

// Loading screen variables
int loadingBarWidth = 0;
bool loadingDone = false;
bool goToMainMenu = false;
bool blinkTextWhite = true;
static bool assetsLoaded = false;

int previousScreen = -1; // To track screen transitions


// had to declare the function definition here otherwise it was not working
void loadingScreenText();


void iDraw()
{
	iClear();

	if (!goToMainMenu)
	{
		// Show loading screen
		iShowImage(0, 10, SCREEN_WIDTH, SCREEN_HEIGHT, loadingScreen);

		// Loading bar frame and fill
		iSetColor(255, 60, 60);
		iRectangle(390, 35, 500, 25);
		iFilledRectangle(390, 35, loadingBarWidth, 25);
		loadingScreenText();
	}
	else
	{
		// Show the actual menu screen after loading
		showMenu();

		// On the 1v1 gameplay screen, render characters
		if (currentScreen == 20){
			showArenaImages();
			if (selectedCharacterIndexP1 == 2) captainAmericaP1.draw();
			if (selectedCharacterIndexP2 == 2) captainAmericaP2.draw();

			// paused button
			iShowImage(pauseButton.x, pauseButton.y, pauseButton.width, pauseButton.height, pauseButtonImage);

			// If the game is paused, show the pause menu
			if (currentGameState == PAUSED) {
				showPauseMenu();
			}

		}
		// Logic for Arcade Mode Screen (30)
		else if (currentScreen == 30) {
			// Check if we just entered the arcade screen to load characters once
			if (previousScreen != 30) {
				loadArcadeCharacters();
			}
 main

			drawArcadeScene();

 test
		// AI Controls
		handleJump(arcadeAI, false);
		handleAI(arcadeAI, arcadePlayer);
	

		updateBackgroundScroll(captainAmericaP1);
=======
			// Show pause button in Arcade Mode
			iShowImage(pauseButton.x, pauseButton.y, pauseButton.width, pauseButton.height, pauseButtonImage);

			// If the game is paused, show the pause menu in Arcade Mode
			if (currentGameState == PAUSED) {
				showPauseMenu();
			}
		}

	}
	// Update previous screen state at the end of the draw call
	previousScreen = currentScreen;
}


// Handles the loading bar animation on loading screen
void loadingBar(){
	if (!loadingDone){
		loadingBarWidth += 10;
		if (loadingBarWidth >= 500){
			loadingBarWidth = 500;
			loadingDone = true;
		}
	}

	else{
		if (isKeyPressed(' ')){
			goToMainMenu = true;
			// Load menu 
			if (mainMenuScreen == -1){
				loadMenuAssets();
				loadCharacterSelectionAssets();
				loadCharacterSelectionAssetsForArcade();
				loadArenaAssets();
				loadPauseAssets();
				loadDynamicArenaBG();
			}
		}
	}
}

void loadingScreenText(){
	// If loading done, show text prompt
	if (loadingDone){
		if (blinkTextWhite) {
			iSetColor(255, 255, 255); // white
		}
		else {
			iSetColor(0, 0, 0); // black
		}
		iText(530, 80, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
	}
	else{
		iSetColor(255, 255, 255);
		iText(390, 70, "Loading...", GLUT_BITMAP_HELVETICA_18);
	}
}

void toggleBlinkColor() {
	blinkTextWhite = !blinkTextWhite;
}

void updateCharacters() {
	// Only update character animations if the game is playing
	if (currentScreen == 20 && currentGameState == PLAYING){
		if(selectedCharacterIndexP1 == 2) captainAmericaP1.update();
		if(selectedCharacterIndexP2 == 2) captainAmericaP2.update();
		// ironMan.update();
	}

	// Update arcade characters' animations	
	else if (currentScreen == 30 && currentGameState == PLAYING){
		updateArcadeCharacters();

	}
}

int main()
{
	// Initialize graphics window
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Marvel Mayhem");

	//loading screen background image
	loadingScreen = iLoadImage("BG/loading3.png");

	loadCaptainAmerica(captainAmericaP1);
	loadCaptainAmerica(captainAmericaP2);

	captainAmericaP1.moveX = 200;        // Player 1 starts on the left
	captainAmericaP1.facingRight = true; // Player 1 faces right

	captainAmericaP2.moveX = 980;         // Player 2 starts on the right  
=======
void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{
	if (goToMainMenu) {
		// If in game and paused, handle pause menu hover
		if ((currentScreen == 20 || currentScreen == 30) && currentGameState == PAUSED) {
			handlePauseHoverAnimation(mx, my);
		}
		else {
			// Handle main menu hover Animation
			handleHoverAnimation(mx, my);
		}
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (goToMainMenu) {
		if (currentScreen == 20) { // Clicks inside the 1v1 arena screen
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (currentGameState == PAUSED) {
					// If paused, check for clicks on the pause menu
					int clickedButtonIndex = handlePauseMenuClick(mx, my);
					if (clickedButtonIndex == 0) { // Resume
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 1) { // Restart
						resetCharacters(captainAmericaP1, captainAmericaP2);
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 2) { // Character Selection
						resetCharacters(captainAmericaP1, captainAmericaP2);
						currentScreen = 10; // Go back to character selection
						currentGameState = PLAYING; // Reset state for next time
					}
				}
				else {
					// If playing, check for clicks on the main pause button
					if (mx >= pauseButton.x && mx <= pauseButton.x + pauseButton.width &&
						my >= pauseButton.y && my <= pauseButton.y + pauseButton.height) {
						currentGameState = PAUSED;
					}
				}
			}
		}
		// Clicks inside the Arcade Mode arena screen
		else if (currentScreen == 30) {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				if (currentGameState == PAUSED) {
					// If paused, check for clicks on the pause menu
					int clickedButtonIndex = handlePauseMenuClick(mx, my);
					if (clickedButtonIndex == 0) { // Resume
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 1) { // Restart
						resetArcadePlayer(arcadePlayer, arcadeAI);
						currentGameState = PLAYING;
					}
					else if (clickedButtonIndex == 2) { // Character Selection
						resetArcadePlayer(arcadePlayer, arcadeAI);
						currentScreen = 11; // Go back to arcade character selection
						currentGameState = PLAYING; // Reset state for next time
					}
				}
				else {
					// If playing, check for clicks on the main pause button
					if (mx >= pauseButton.x && mx <= pauseButton.x + pauseButton.width &&
						my >= pauseButton.y && my <= pauseButton.y + pauseButton.height) {
						currentGameState = PAUSED;
					}
				}
			}
		}
		else {
			// Handle menu clicks only after the loading screen
			handleMenuClick(button, state, mx, my);
		}
	}
}

// This function runs at a fixed interval
void fixedUpdate() {
	// 1v1 Mode Controls
	if (goToMainMenu && currentScreen == 20 && currentGameState != PAUSED) {
		// Player 1 controls (WASD + F)
		handleInputMovement(captainAmericaP1, isKeyPressed('d'), isKeyPressed('a'));
		handleDefaultState(captainAmericaP1, isKeyPressed('d'), isKeyPressed('a'));
		handleJump(captainAmericaP1, isKeyPressed('w'));
		handleAttack(captainAmericaP1, isKeyPressed('f'));

		// Player 2 controls (Arrow keys + Down Arrow)
		handleInputMovement(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_RIGHT), isSpecialKeyPressed(GLUT_KEY_LEFT));
		handleDefaultState(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_RIGHT), isSpecialKeyPressed(GLUT_KEY_LEFT));
		handleJump(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_UP));
		handleAttack(captainAmericaP2, isSpecialKeyPressed(GLUT_KEY_DOWN));
	}
	// Arcade Mode Controls
	else if (goToMainMenu && currentScreen == 30 && currentGameState != PAUSED) {
		// Player controls
		handleInputMovement(arcadePlayer, isKeyPressed('d'), isKeyPressed('a'));
		handleDefaultState(arcadePlayer, isKeyPressed('d'), isKeyPressed('a'));
		handleJump(arcadePlayer, isKeyPressed('w'));
		handleAttack(arcadePlayer, isKeyPressed('f'));

		// AI Controls
		handleJump(arcadeAI, false);
		handleAI(arcadeAI, arcadePlayer);
	}
}

// Handles the loading bar animation on loading screen
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
			// Load menu
			if (mainMenuScreen == -1){
				loadMenuAssets();
				loadCharacterSelectionAssets();
				loadCharacterSelectionAssetsForArcade();
				loadArenaAssets();
				loadPauseAssets();
			}
		}
	}
}

void loadingScreenText(){
	// If loading done, show text prompt
	if (loadingDone){
		if (blinkTextWhite) {
			iSetColor(255, 255, 255); // white
		}
		else {
			iSetColor(0, 0, 0); // black
		}
		iText(530, 80, "Press SPACE to continue", GLUT_BITMAP_HELVETICA_18);
	}
	else{
		iSetColor(255, 255, 255);
		iText(390, 70, "Loading...", GLUT_BITMAP_HELVETICA_18);
	}
}

void toggleBlinkColor() {
	blinkTextWhite = !blinkTextWhite;
}

void updateCharacters() {
	// Only update character animations if the game is playing
	if (currentScreen == 20 && currentGameState == PLAYING){
		if (selectedCharacterIndexP1 == 2) captainAmericaP1.update();
		if (selectedCharacterIndexP2 == 2) captainAmericaP2.update();
	}
	// Update arcade characters' animations
	else if (currentScreen == 30 && currentGameState == PLAYING) {
		updateArcadeCharacters();
	}
}

int main()
{
	// Initialize graphics window
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Marvel Mayhem");

	//loading screen background image
	loadingScreen = iLoadImage("BG/loading3.png");

	loadCaptainAmerica(captainAmericaP1);
	loadCaptainAmerica(captainAmericaP2);

	captainAmericaP1.moveX = 200;        // Player 1 starts on the left
	captainAmericaP1.facingRight = true; // Player 1 faces right

	captainAmericaP2.moveX = 980;         // Player 2 starts on the right

	captainAmericaP2.facingRight = false; // Player 2 faces left

	iSetTimer(350, toggleBlinkColor); // 350 ms = 0.35 sec toggle

	iSetTimer(10, loadingBar);


	iSetTimer(25, fixedUpdate);

	iSetTimer(100, updateCharacters);

	iSetTimer(100, loadArenaAssets);

	iSetTimer(100, loadDynamicArenaBG);
	
	iStart(); // Start the graphics engine

	return 0;
}


	iSetTimer(25, fixedUpdate);

	iSetTimer(100, updateCharacters);

	iSetTimer(100, loadArenaAssets);

	iStart(); // Start the graphics engine

	return 0;
}








/*
void fixedUpdate() {

if (!goToMainMenu || currentScreen != 10) return;

static bool jumpInProgress = false;

bool wPressed = isKeyPressed('w');
bool moveRight = isKeyPressed('d');
bool moveLeft = isKeyPressed('a');

// ? Move left
if (moveLeft) {
captainAmerica.facingRight = false;
captainAmerica.moveX -= 5;
}

// ? Move right
if (moveRight) {
captainAmerica.facingRight = true;
captainAmerica.moveX += 5;
}

// Start jump if W is pressed and not already jumping
if (wPressed && !jumpInProgress) {
captainAmerica.setState(JUMP);
captainAmerica.currentFrame = 0;
jumpInProgress = true;
}

// Handle jump animation movement
if (jumpInProgress){
int f = captainAmerica.currentFrame;

// Y axis arc movement (fake)
if (f == 0) captainAmerica.moveY += 12;
else if (f == 1) captainAmerica.moveY += 8;
else if (f == 2) captainAmerica.moveY += 5;
else if (f == 3) captainAmerica.moveY -= 5;
else if (f == 4) captainAmerica.moveY -= 8;
else if (f == 5) captainAmerica.moveY -= 12;

// When jump ends
int maxJump = captainAmerica.facingRight ? captainAmerica.jumpCount_R : captainAmerica.jumpCount_L;
if (captainAmerica.currentFrame >= maxJump - 1) {
captainAmerica.moveY = captainAmerica.baseY; // go back to ground
jumpInProgress = false;
}
}
// If not jumping, pick proper state
if (!jumpInProgress && captainAmerica.characterState != ATTACK) {
if (moveRight || moveLeft) captainAmerica.setState(WALK);
else captainAmerica.setState(IDLE);
// Safety check � never below ground
if (captainAmerica.moveY < captainAmerica.baseY) {
captainAmerica.moveY = captainAmerica.baseY;
}
}

if (captainAmerica.characterState == ATTACK) {
int maxAtk = captainAmerica.facingRight ? captainAmerica.attackCount_R : captainAmerica.attackCount_L;

if (captainAmerica.currentFrame >= maxAtk - 1) {
if (isKeyPressed('f')) {
captainAmerica.currentFrame = 0; // loop attack
}
else {
captainAmerica.setState(IDLE); // go back to idle
}
}
}
else if (isKeyPressed('f')) {
captainAmerica.setState(ATTACK);
}
if (jumpInProgress && isKeyPressed('f')) {
captainAmerica.setState(ATTACK); // mid-air attack
}


}
*/