#include "TheGame.h"

TheGame::TheGame() : currentWindow(nullptr), WINDOW_HEIGHT(600), WINDOW_WIDTH(768), FPS(10),
currentState(GameState::PLAY), jimHeight(50), jimWidth(50), eventMade(0), jim(nullptr),
gravity(10), gameFloor(nullptr)
{}


TheGame::~TheGame()
{
}

/* TODO
*/

void TheGame::run(){
	initGame();

	const int SKIPFRAMES = 1000 / FPS;
	const int MAXFRAMESKIP = 5;

	unsigned int nextframe = SDL_GetTicks();
	int loops;
	float interpolation;
	int i = 0;

	//game loop
	while (currentState != GameState::EXIT){
		loops = 0;


		while (SDL_GetTicks() > nextframe && loops < MAXFRAMESKIP){
			processInput();

			update();

			nextframe += SKIPFRAMES;
			++loops;
		}
		interpolation = float(SDL_GetTicks() + SKIPFRAMES - nextframe) / float(SKIPFRAMES);
		draw();
	}
}

void TheGame::initGame(){
	currentWindow = WindowInitialization();
	context = SDL_CreateRenderer(currentWindow, -1, SDL_RENDERER_ACCELERATED);

	int startingY = WINDOW_HEIGHT - ((2.0 / 23)*WINDOW_HEIGHT);
	jim = new MainCharacter(Position(50, 504, jimWidth, jimHeight), Character::JIM);
	objectManager = new ObjectManager(context, jim);

	instantiateLevelObjects();
}

SDL_Window* TheGame::WindowInitialization(){
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

	SDL_Window* win = SDL_CreateWindow("The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (win == nullptr){
		PrintErrors("Failed to create SDL window!", SDL_GetError);
	}

	return win;
}

int TheGame::processInput(){
	int size;
	keyState = SDL_GetKeyboardState(&size);
	fakeKeyState = new Uint8[size];
	fakeKeyState[SDL_SCANCODE_D] = 1;
	fakeKeyState[SDL_SCANCODE_W] = 0;

	return eventMade = SDL_PollEvent(&currentEvent);
}

void TheGame::update(){
	int mouseX = 0;
	int mouseY = 0;

	Uint32 a = SDL_GetMouseState(&mouseX, &mouseY);
	objectManager->updatePreviousPositions();
	objectManager->setMousePosition();

	if (keyState[SDL_SCANCODE_D]){
		jim->moveRight();
	}

	if (keyState[SDL_SCANCODE_A]){
		jim->moveLeft();
	}
	if (keyState[SDL_SCANCODE_W]){
		jim->jump();
	}
	if (SDL_BUTTON(SDL_BUTTON_LEFT) & a){
		std::cout << "(" + std::to_string(jim->getX()) + ", " + std::to_string(jim->getY()) + ")\n";
	}
	if (SDL_BUTTON(SDL_BUTTON_RIGHT) & a){
		std::cout << "Y velocity = " + std::to_string(jim->getMotionVectorY()) << std::endl;
	}

	// make sure jim doesn't exit screen
	if ((jim->getX() + jim->getWidth()) > WINDOW_WIDTH)
		jim->setX(WINDOW_WIDTH - jim->getWidth());

	if (jim->getX() < 0)
		jim->setX(0);

	if (jim->getY() < 0)
		jim->setY(0);

	if ((jim->getY() + jim->getHeight()) > WINDOW_HEIGHT)
		jim->setY(WINDOW_HEIGHT - jim->getHeight());

	calcGravity();
	detectCollisions();
	objectManager->setTextures();
}

void TheGame::draw(){
	objectManager->drawAllObjects();
}

void TheGame::calcGravity(){
	objectManager->applyGravity(gravity);
}

void TheGame::detectCollisions(){
	objectManager->detectCollisions();
}

void TheGame::instantiateLevelObjects(){
	objectManager->createObject(Character::BACKGROUND, Position(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), true);
	objectManager->createObject(Character::LIGHT_GRAY_PLATFORM, Position(125, WINDOW_HEIGHT - 210, 100, 100), true);
	objectManager->createObject(Character::LIGHT_GREEN_PLATFORM, Position(0, WINDOW_HEIGHT - 50, WINDOW_WIDTH, 50), true);
	objectManager->createObject(Character::FLYING_HEART_LARGE, Position(300, 504, 100, 100), true);
}