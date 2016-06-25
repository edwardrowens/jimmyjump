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
#include <algorithm>
#include <time.h>
#include <map>

enum class GameState { PLAY, EXIT };
static int sdlRenderThreadWrapper(void* param);
static int sdlUpdateThreadWrapper(void* param);

class TheGame {
public:
	// Constructors and destructor
	TheGame();

	// Functions
	void run();
	void draw();
	void addInput(Uint8 input);
	int startUpdateLoop();
	World& getWorld();
	std::map<DWORD, std::vector<Uint8>> getKeyPressByFrame();

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
	std::unique_ptr<Uint8> keyPressBuffer;
	std::set<Uint8> inputs;
	std::mutex mutey;
	DWORD updateTick;
	std::map<DWORD, std::vector<Uint8>> keyPressByFrame;


	// Functions
	void processInput();
	void step();
	SDL_Window* WindowInitialization();
	void initGame();
	void calcGravity();
	void detectCollisions();
	void instantiateLevelObjects();
	SDL_Thread* renderThread;
	SDL_Thread* updateThread;

	World world;
};

