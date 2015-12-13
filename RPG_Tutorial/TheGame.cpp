#include "TheGame.h"


TheGame::TheGame() : currentWindow(nullptr), WINDOW_HEIGHT(600), WINDOW_WIDTH(768), FPS(10),
currentState(GameState::PLAY), jimHeight(50), jimWidth(50), eventMade(0), jim(nullptr), 
gravity(10), gameFloor(nullptr)
{}


TheGame::~TheGame()
{
}

/* TODO
1. implement safety checks for background and platform objects so only the appropriate textures
may be assigned to them
2. improve walkcycles to be more generalizable
3. institute collision detection
3.5 make gamefloor
*/

void TheGame::run(){
	initGame();

	Object background(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	Platform platform(125, WINDOW_HEIGHT - 210, 100, 100);
	Platform platform2(0, WINDOW_HEIGHT - 150, 100, 100);

	background.load(Character::BACKGROUND, currentRenderContext);
	platform2.load(Character::LIGHT_GRAY_PLATFORM, currentRenderContext);
	platform.load(Character::LIGHT_GREEN_PLATFORM, currentRenderContext);
	jim->load(Character::JIM, currentRenderContext);

	levelObjects.push_back(&background);
	levelObjects.push_back(&platform);
	levelObjects.push_back(&platform2);
	levelObjects.push_back(jim);
	levelObjects.push_back(gameFloor);

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
	currentRenderContext = SDL_CreateRenderer(currentWindow, -1, SDL_RENDERER_ACCELERATED);

	gameFloor = new Platform();
	gameFloor->setIsRenderable(false);
	gameFloor->setX(0);
	gameFloor->setY(WINDOW_HEIGHT - ((2.0 / 23)*WINDOW_HEIGHT));
	gameFloor->setHeight(15);
	gameFloor->setWidth(WINDOW_WIDTH);

	int startingY = gameFloor->getY() - jimHeight;
	jim = new MainCharacter(150, 0, jimWidth, jimHeight);
}

SDL_Window* TheGame::WindowInitialization(){
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);

	SDL_Window* win = SDL_CreateWindow("The Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );

	if (win == nullptr){
		PrintErrors("Failed to create SDL window!", SDL_GetError);
	}

	return win;
}

int TheGame::processInput(){
	int size;
	keyState = SDL_GetKeyboardState(&size);
	return eventMade = SDL_PollEvent(&currentEvent);
}

void TheGame::update(){
	jim->setPreviousMovement(jim->getCurrentMovement());
	jim->setPreviousXY(jim->getX(), jim->getY());
	calcGravity();

	//change walkcycles!!!
	if (keyState[SDL_SCANCODE_D] && !keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::right);
		jim->moveRight();
	}

	else if (keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::left);
		jim->moveLeft();
	}
	else if (keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::jump);
		jim->jump();
	}
	else{
		jim->setCurrentMovement(MovableObject::Movements::none);
	}

	// make sure jim doesn't exit screen
	if ((jim->getX() + jim->getWidth()) > WINDOW_WIDTH)
		jim->setX(WINDOW_WIDTH - jim->getWidth());

	if (jim->getX() < 0)
		jim->setX(0);

	if (jim->getY() < 0)
		jim->setY(0);

	if ((jim->getY() + jim->getHeight()) > WINDOW_HEIGHT)
		jim->setY(WINDOW_HEIGHT - jim->getY());

	detectCollisions();
}

void TheGame::draw(){
	if (SDL_RenderClear(currentRenderContext)){
		PrintErrors("Renderer failed to clear", SDL_GetError);
	}

	std::vector<Object*>::iterator iter = levelObjects.begin();
	for (iter; iter != levelObjects.end(); ++iter){
		if ((*iter)->getIsRenderable())
			(*iter)->draw(currentRenderContext);
	}

	SDL_RenderPresent(currentRenderContext);
}

void TheGame::calcGravity(){
	std::vector<Object*>::iterator iter = levelObjects.begin();
	for (iter; iter != levelObjects.end(); ++iter){
		if ((*iter)->getIsMovable()){
			(*iter)->setY((*iter)->getY() + gravity);
		}
	}
}

void TheGame::detectCollisions(){
	std::vector<Object*>::iterator i = levelObjects.begin();
	for (i; i != levelObjects.end(); ++i){
		if ((*i)->getIsMovable()){
			MovableObject* tempObject = dynamic_cast<MovableObject*>(*i);
			CollisionDetector::detectStaticCollisions(tempObject, levelObjects);
			CollisionDetector::detectDynamicCollisions(tempObject, levelObjects);
		}
	}
}