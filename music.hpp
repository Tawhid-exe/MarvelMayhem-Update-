#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <windows.h>
#include <mmsystem.h>

// Main Menu Music
void startMainMenuMusic() {
	mciSendString("open \"Audios//mainMenuMusic.mp3\" alias mainMenu", nullptr, 0, nullptr);
	mciSendString("play mainMenu repeat", nullptr, 0, nullptr);
}

void stopMainMenuMusic() {
	mciSendString("stop mainMenu", nullptr, 0, nullptr);
	mciSendString("close mainMenu", nullptr, 0, nullptr);
}

// Character Selection Music
void startCharSelectionMusic() {
	mciSendString("open \"Audios//charSelectionMusic.mp3\" alias charSelection", nullptr, 0, nullptr);
	mciSendString("play charSelection repeat", nullptr, 0, nullptr);
}

void stopCharSelectionMusic() {
	mciSendString("stop charSelection", nullptr, 0, nullptr);
	mciSendString("close charSelection", nullptr, 0, nullptr);
}

// Arena Music
void startArenaMusic() {
	mciSendString("open \"Audios//arenaMusic.mp3\" alias arenaMusic", nullptr, 0, nullptr);
	mciSendString("play arenaMusic repeat", nullptr, 0, nullptr);
}

void stopArenaMusic() {
	mciSendString("stop arenaMusic", nullptr, 0, nullptr);
	mciSendString("close arenaMusic", nullptr, 0, nullptr);
}

// Character Click sound
void playCharClickSound() {
	static bool musicLoaded = false;

	if (musicLoaded == false) { // Loading music everytime for multiple click
		mciSendString("open \"Audios//charClickSound.mp3\" alias charClick", nullptr, 0, nullptr);
		musicLoaded = true;
	}

	mciSendString("play charClick from 0", nullptr, 0, nullptr);
}

// Click sound
void playClickSound() {
	static bool musicLoaded = false;

	if (musicLoaded == false) { // Loading music everytime for multiple click
		mciSendString("open \"Audios//click.mp3\" alias click", nullptr, 0, nullptr);
		musicLoaded = true;
	}

	mciSendString("play click from 230", nullptr, 0, nullptr);
}

#endif MUSIC_HPP