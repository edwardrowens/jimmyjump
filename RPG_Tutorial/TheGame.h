#pragma once
#include <SDL2.0/SDL.h>
#include <SDL2.0\SDL_image.h>
#include <string>
#include <iostream>
#include "Errors.h"
#include "MainCharacter.h"
#include "ObjectManager.h"
#include <ctime>
#include <vector>
#include "Platform.h"
#include "CollisionDetector.h"
#include "Movements.h"
#include "Utility.h"
#include "Position.h"

enum class GameState {PLAY,EXIT};

ObjectManager* objectManager;

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
	int gravity;
	GameState currentState;
	SDL_Window* currentWindow;
	SDL_Event currentEvent;
	SDL_Renderer* context;
	Utility utility;
	Platform* gameFloor;
	int jimWidth, jimHeight, jimStartY;
	MainCharacter* jim;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	const int FPS;
	//processes input
	const Uint8* keyState;
	int eventMade;
	
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

