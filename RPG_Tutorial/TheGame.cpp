#include "TheGame.h"

TheGame::TheGame() : currentWindow(nullptr),
currentState(GameState::PLAY), jimHeight(50), jimWidth(50), eventMade(0), jim(nullptr),
gravity(10), gameFloor(nullptr) {
}


TheGame::~TheGame() {
}

void TheGame::run() {
	initGame();

	float timeElapsedSinceLastUpdate = 0.0f;
	float timeOfLastUpdate = SDL_GetTicks();

	while (currentState != GameState::EXIT) {
		timeElapsedSinceLastUpdate = SDL_GetTicks() - timeOfLastUpdate;
		while (timeElapsedSinceLastUpdate >= WorldConstants::UPDATE_TICK_IN_SECONDS) {
			processInput();
			update();
			timeOfLastUpdate = SDL_GetTicks();
			timeElapsedSinceLastUpdate -= WorldConstants::UPDATE_TICK_IN_SECONDS;
		}
		draw();
	}
}

void TheGame::initGame() {
	currentWindow = WindowInitialization();
	context = SDL_CreateRenderer(currentWindow, -1, SDL_RENDERER_ACCELERATED);
	world.setContext(context);

	instantiateLevelObjects();
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

int TheGame::processInput() {
	int size;
	keyState = SDL_GetKeyboardState(&size);

	return eventMade = SDL_PollEvent(&currentEvent);
}

void TheGame::update() {
	//jim->addMovement(Movements::RIGHT);
	if (keyState[SDL_SCANCODE_D]){
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
		position.w = 20;
		position.h = 20;
		world.createObject(Character::LIGHT_GRAY_PLATFORM, ObjectPhysicalPropertiesService::objectPhysicalProperties(ObjectBodies::EXAMPLE, position), true);
	}

	world.step();
}

void TheGame::draw() {
	world.drawAllObjects();
}


void TheGame::instantiateLevelObjects() {
	Position position;
	position.x = 100;
	position.y = 250;
	position.h = 50;
	position.w = 100;
	//world.createObject(Character::BACKGROUND, ObjectPhysicalPropertiesService::objectPhysicalProperties(ObjectBodies::ObjectBodies::NONE, position), true);
	jim = dynamic_cast<MainCharacter*>(world.createObject(Character::JIM, ObjectPhysicalPropertiesService::objectPhysicalProperties(ObjectBodies::ObjectBodies::EXAMPLE), true));
	world.createObject(Character::LIGHT_GREEN_PLATFORM, ObjectPhysicalPropertiesService::objectPhysicalProperties(ObjectBodies::ObjectBodies::PLATFORM), true);
	controllableObjects.push_back(jim);
}