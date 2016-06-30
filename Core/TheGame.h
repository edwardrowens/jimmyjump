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
	void addInput(uint8_t input);
	int startUpdateLoop();
	World& getWorld();
	std::map<uint32_t, std::vector<uint8_t>> getKeyPressByFrame();

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
	const uint8_t* keyState;
	std::unique_ptr<uint8_t> keyPressBuffer;
	std::set<uint8_t> inputs;
	std::mutex mutey;
	uint32_t updateTick;
	std::map<uint32_t, std::vector<uint8_t>> keyPressByFrame;


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

