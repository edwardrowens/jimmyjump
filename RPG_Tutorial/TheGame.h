#pragma once
#include <SDL2.0/SDL.h>
#include <SDL2.0\SDL_image.h>
#include <string>
#include <iostream>
#include <vector>
#include "Errors.h"
#include "MainCharacter.h"
#include "Platform.h"
#include "CollisionDetector.h"
#include "Movements.h"
#include "Utility.h"
#include "Position.h"
#include "ObjectManager.h"

enum class GameState {PLAY,EXIT};

class TheGame
{
public:
	// Constructors and destructor
	TheGame();
	~TheGame();

	// Functions
	void run();

private:
	// Fields
	GameState currentState;
	SDL_Window* currentWindow;
	SDL_Event currentEvent;
	SDL_Renderer* context;
	Utility utility;
	Platform* gameFloor;
	MainCharacter* jim;
	ObjectManager* objectManager;
	int jimWidth, jimHeight, jimStartY, eventMade, gravity;
	const int WINDOW_WIDTH = 768;
	const int WINDOW_HEIGHT = 600;
	const int FPS = 10;
	//processes input
	const Uint8* keyState;
	
	// Functions
	SDL_Window* WindowInitialization();
	void initGame();
	void calcGravity();
	void detectCollisions();
	void instantiateLevelObjects();
	//game loop
	int processInput();
	void update();
	void draw();
};

