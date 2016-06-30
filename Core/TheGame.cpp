#include "TheGame.h"

TheGame::TheGame() : currentWindow(nullptr),
currentState(GameState::PLAY),
eventMade(0),
jim(nullptr),
renderThread(nullptr),
keyPressBuffer(new uint8_t[SDL_NUM_SCANCODES]{0}) {
}


void TheGame::run() {
	initGame();

	renderThread = SDL_CreateThread(&sdlRenderThreadWrapper, "RenderThread", this);
	startUpdateLoop();
}


void TheGame::initGame() {
	currentWindow = WindowInitialization();
	context = SDL_CreateRenderer(currentWindow, -1, SDL_RENDERER_ACCELERATED);
	world.setContext(context);
}


SDL_Window* TheGame::WindowInitialization() {
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

	SDL_Window* win = SDL_CreateWindow("The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WorldConstants::WINDOW_WIDTH, WorldConstants::WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (win == nullptr) {
		PrintErrors("Failed to create SDL window!", SDL_GetError);
	}

	if (TTF_Init()) {
		PrintErrors("Failed to initialize the true type font", SDL_GetError);
	}

	return win;
}


void TheGame::processInput() {
	if (inputs.size() == 0 && context) {
		SDL_PumpEvents();
		int size;
		keyState = SDL_GetKeyboardState(&size);
	}
	else {
		mutey.lock();

		// remove all previous inputs
		for (uint8_t input : inputs)
			keyPressBuffer.get()[input] = 0;

		// add new inputs
		for (uint8_t input : inputs)
			keyPressBuffer.get()[input] = 1;

		keyState = keyPressBuffer.get();

		inputs.clear();
		mutey.unlock();
	}
}


void TheGame::step() {
	std::vector<uint8_t> keyPresses;
	if (keyState[SDL_SCANCODE_D]) {
		jim->addMovement(Movements::RIGHT);
	}
	if (keyState[SDL_SCANCODE_A]) {
		jim->addMovement(Movements::LEFT);
	}
	if (keyState[SDL_SCANCODE_W]) {
		jim->addMovement(Movements::JUMP);
	}
	if (keyState[SDL_SCANCODE_P]) {
		jim->addMovement(Movements::PATROL);
	}
	if (jim->getCurrentMovements().size() == 0) {
		jim->addMovement(Movements::NONE);
	}

	if (keyState[SDL_SCANCODE_T]) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		Position position;
		position.x = mouseX;
		position.y = mouseY;
		position.w = 5;
		position.h = 5;
		world.createObject(Character::LIGHT_GRAY_PLATFORM, ObjectBodies::PLAYER, position, true);
	}

	keyPressByFrame.insert({ updateTick, keyPresses });
	world.step();
}


void TheGame::draw() {
	while (currentState != GameState::EXIT) {
		world.drawAllObjects();
	}
}


void TheGame::instantiateLevelObjects() {
	Position position;
	position.x = 100;
	position.y = 350;
	position.h = 50;
	position.w = 100;

	jim = dynamic_cast<MainCharacter*>(world.createObject(Character::JIM, ObjectBodies::PLAYER, true));
	world.createObject(Character::LIGHT_GREEN_PLATFORM, ObjectBodies::STATIONARY, true);
	world.createObject(Character::LIGHT_GRAY_PLATFORM, ObjectBodies::STATIONARY, position, true);
	controllableObjects.push_back(jim);
}


static int sdlUpdateThreadWrapper(void* param) {
	((TheGame*)param)->startUpdateLoop();
	return 0;
}


static int sdlRenderThreadWrapper(void* param) {
	((TheGame*)param)->draw();
	return 0;
}

int TheGame::startUpdateLoop() {
	instantiateLevelObjects();
	unsigned long timeElapsedSinceLastUpdate = 0.0f;
	unsigned long timeOfLastUpdate = GetTickCount();

	while (currentState != GameState::EXIT) {
		timeElapsedSinceLastUpdate = GetTickCount() - timeOfLastUpdate;
		while (timeElapsedSinceLastUpdate >= WorldConstants::UPDATE_TICK_IN_SECONDS) {
			processInput();
			step();
			timeOfLastUpdate = GetTickCount();
			timeElapsedSinceLastUpdate -= WorldConstants::UPDATE_TICK_IN_SECONDS;
			++updateTick;
		}
	}
	return 0;
}


void TheGame::addInput(uint8_t input) {
	mutey.lock();
	inputs.insert(input);
	mutey.unlock();
}


World& TheGame::getWorld() {
	return world;
}


std::map<uint32_t, std::vector<uint8_t>> TheGame::getKeyPressByFrame() {
	std::map<uint32_t, std::vector<uint8_t>> copy = keyPressByFrame;
	keyPressByFrame.clear();
	return copy;
}