#pragma once
#include <SDL2.0/SDL.h>
#include <SDL2.0\SDL_image.h>
#include "Box2D\Box2D.h"
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
#include "World.h"
#include "ObjectPhysicalPropertiesService.h"
#include "ObjectBodies.h"
#include <thread>

enum class GameState {PLAY,EXIT};

class TheGame {
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
	MainCharacter* jim;
	int  eventMade;
	std::vector<MovableObject*> controllableObjects;
	float gravity, keyPressLength;
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
	void step();
	void draw();
	std::thread updateThread;

	World world;
};

