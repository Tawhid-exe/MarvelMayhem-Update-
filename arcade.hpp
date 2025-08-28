#ifndef ARCADE_HPP
#define ARCADE_HPP

#include "character.hpp"
#include "ai.hpp"
#include "menu.hpp"

// Declare character objects for the arcade mode
Character arcadePlayer;
Character arcadeAI;


 //Loads the player's selected character and the AI opponent

void loadArcadeCharacters() {
	// Load the player's character based on their selection
	switch (selectedCharacterIndexArcade) {
	// case 1: loadIronMan(arcadePlayer);
		//break;
	case 2: // Captain America
		loadCaptainAmerica(arcadePlayer);
		break;
		
	default: // Default to Captain America if selection is invalid
		loadCaptainAmerica(arcadePlayer);
		break;
	}
	// Set the player's starting position
	arcadePlayer.moveX = 200;
	arcadePlayer.facingRight = true;

	// Load the AI's character (currently always Captain America)
	loadCaptainAmerica(arcadeAI);
	// Set the AI's starting position
	arcadeAI.moveX = 980;
	arcadeAI.facingRight = false;
}


//Draws all elements of the arcade fighting scene.

void drawArcadeScene() {
	showArenaImages(); // Draw the background arena
	arcadePlayer.draw(); // Draw the player's character
	arcadeAI.draw();     // Draw the AI's character
}


//Updates the state of both the player and AI characters.

void updateArcadeCharacters() {
	arcadePlayer.update();
	arcadeAI.update();
}

#endif // ARCADE_HPP
