#pragma once
#include <SDL2.0/SDL.h>
#include <SDL2.0\SDL_image.h>
#include <string>
#include <iostream>
#include "Errors.h"
#include "MainCharacter.h"
#include "Object.h"
#include <ctime>
#include <vector>
#include "Platform.h"
#include "CollisionDetector.h"
#include "Movements.h"
#include "Utility.h"
#include "Position.h"

enum class GameState {PLAY,EXIT};

class TheGame
{
public:
	TheGame();
	~TheGame();

	void run();

private:
	SDL_Window* WindowInitialization();
	void initGame();

	int gravity;
	void calcGravity();
	void detectCollisions();
	void instantiateLevelObjects();

	GameState currentState;
	SDL_Window* currentWindow;
	SDL_Event currentEvent;
	SDL_Renderer* context;

	//processes input
	const Uint8* keyState;
	int eventMade;

	/*vector that contains all objects but the main character. the background of a level should
	always be pushed first*/
	std::vector<Object*> levelObjects;
	Utility utility;
	Platform* gameFloor;

	//game loop
	int processInput();
	void update();
	void draw();

	int jimWidth, jimHeight, jimStartY;
	MainCharacter* jim;

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	const int FPS;
};

