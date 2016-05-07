#include "TheGame.h"

TheGame::TheGame() : currentWindow(nullptr),
currentState(GameState::PLAY), jimHeight(50), jimWidth(50), eventMade(0), jim(nullptr),
gravity(10), gameFloor(nullptr)
{}


TheGame::~TheGame()
{}

/* TODO
*/

void TheGame::run() {
	initGame();

	//const int SKIPFRAMES = 1000 / FPS;
	//const int MAXFRAMESKIP = 5;

	float timeBehind = 0.0f;
	float lastTime = SDL_GetTicks();

	//unsigned int nextframe = SDL_GetTicks();
	//int loops;
	//float interpolation;
	//int i = 0;
	//numberOfFrames = 0;
	//game loop
	while (currentState != GameState::EXIT) {
		timeBehind += SDL_GetTicks() - lastTime;
		processInput();
		update();
		while (timeBehind >= WorldConstants::UPDATE_TICK) {
			update();
			timeBehind -= WorldConstants::UPDATE_TICK;
		}
		//interpolation = float(SDL_GetTicks() + SKIPFRAMES - nextframe) / float(SKIPFRAMES);
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

	return win;
}

int TheGame::processInput() {
	int size;
	keyState = SDL_GetKeyboardState(&size);

	return eventMade = SDL_PollEvent(&currentEvent);
}

void TheGame::update() {
	int mouseX = 0;
	int mouseY = 0;

	Uint32 a = SDL_GetMouseState(&mouseX, &mouseY);
	world.setMousePosition();

	//controllableObjects[0]->addMovement(Movements::RIGHT);

	jim->addMovement(Movements::RIGHT);
	if (keyState[SDL_SCANCODE_D]){
		jim->addMovement(Movements::RIGHT);
	}

	if (keyState[SDL_SCANCODE_A]){
		jim->addMovement(Movements::LEFT);
	}
	if (keyState[SDL_SCANCODE_W]){
		jim->addMovement(Movements::JUMP);
	}
	if (keyState[SDL_SCANCODE_P]){
		jim->addMovement(Movements::PATROL);
	}
	if (jim->getCurrentMovements().size() == 0) {
		jim->addMovement(Movements::NONE);
	}
	if (SDL_BUTTON(SDL_BUTTON_LEFT) & a){
		std::cout << "(" + std::to_string(jim->getX()) + ", " + std::to_string(jim->getY()) + ")\n";
	}
	if (SDL_BUTTON(SDL_BUTTON_RIGHT) & a){
		std::cout << "{ " + std::to_string(jim->getMotionVectorX());
		std::cout << ", " + std::to_string(jim->getMotionVectorY()) << " }\n";
	}


	world.putInMotion();

	//detectCollisions();
	//objectManager->setTextures();
	// make sure characters don't exit screen
	//keepInScreen();
}

void TheGame::draw() {
	world.drawAllObjects();
}

//void TheGame::calcGravity() {
//	world.applyGravity(gravity);
//}

//void TheGame::detectCollisions(){
//	objectManager->detectCollisions();
//}

void TheGame::instantiateLevelObjects() {
	Position position;
	position.x = 0;
	position.y = 0;
	position.h = WorldConstants::WINDOW_HEIGHT;
	position.w = WorldConstants::WINDOW_WIDTH;
	world.createObject(Character::BACKGROUND, ObjectPhysicalPropertiesService::objectPhysicalProperties(ObjectBodies::ObjectBodies::NONE, position), true);
	jim = dynamic_cast<MainCharacter*>(world.createObject(Character::JIM, ObjectPhysicalPropertiesService::objectPhysicalProperties(ObjectBodies::ObjectBodies::EXAMPLE), true));
	controllableObjects.push_back(jim);
}