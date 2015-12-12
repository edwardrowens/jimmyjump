#include "TheGame.h"


TheGame::TheGame() : _currentWindow(nullptr), WINDOW_HEIGHT(600), WINDOW_WIDTH(768), FPS(10),
_currentState(GameState::PLAY), jimHeight(50), jimWidth(50), _eventMade(0), jim(nullptr)
, BACKGROUND_FNAME("Background.png"), _gravity(10), _gameFloor(nullptr)
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

	background.setObjectTexture(_currentRenderContext, "Background.png");
	platform2.setObjectTexture(_currentRenderContext, "LandPiece_LightGray.png");
	platform.setObjectTexture(_currentRenderContext, "LandPiece_LightGreen.png");
	jim->setObjectTexture(_currentRenderContext, "CharacterLeft_Standing.png");

	_levelObjects.push_back(&background);
	_levelObjects.push_back(&platform);
	_levelObjects.push_back(&platform2);
	_levelObjects.push_back(jim);
	_levelObjects.push_back(_gameFloor);

	const int SKIP_FRAMES = 1000 / FPS;
	const int MAX_FRAMESKIP = 5;

	unsigned int next_frame = SDL_GetTicks();
	int loops;
	float interpolation;
	int i = 0;

	//game loop
	while (_currentState != GameState::EXIT){
		loops = 0;


		while (SDL_GetTicks() > next_frame && loops < MAX_FRAMESKIP){
			processInput();

			update();

			next_frame += SKIP_FRAMES;
			++loops;
		}
		interpolation = float(SDL_GetTicks() + SKIP_FRAMES - next_frame) / float(SKIP_FRAMES);
		draw();
	}
}

void TheGame::initGame(){
	_currentWindow = WindowInitialization();
	_currentRenderContext = SDL_CreateRenderer(_currentWindow, -1, SDL_RENDERER_ACCELERATED);

	_gameFloor = new Platform();
	_gameFloor->setIsRenderable(false);
	_gameFloor->setX(0);
	_gameFloor->setY(WINDOW_HEIGHT - ((2.0 / 23)*WINDOW_HEIGHT));
	_gameFloor->setHeight(15);
	_gameFloor->setWidth(WINDOW_WIDTH);

	int startingY = _gameFloor->getY() - jimHeight;
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
	_keyState = SDL_GetKeyboardState(&size);
	return _eventMade = SDL_PollEvent(&_currentEvent);
}

void TheGame::update(){
	jim->setPreviousMovement(jim->getCurrentMovement());
	jim->setPreviousXY(jim->getX(), jim->getY());
	calcGravity();

	//change walkcycles!!!
	if (_keyState[SDL_SCANCODE_D] && !_keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::right);
		jim->moveRight();
	}

	else if (_keyState[SDL_SCANCODE_A] && !_keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::left);
		jim->moveLeft();
	}
	else if (_keyState[SDL_SCANCODE_W]){
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
	if (_levelObjects[0]->getTexturePath() != "Textures/jimmyJump_pack/PNG/" + BACKGROUND_FNAME){
		PrintErrors("The background should be rendered first", SDL_GetError);
	}

	if (SDL_RenderClear(_currentRenderContext)){
		PrintErrors("Renderer failed to clear", SDL_GetError);
	}

	std::vector<Object*>::iterator iter = _levelObjects.begin();
	for (iter; iter != _levelObjects.end(); ++iter){
		if ((*iter)->getIsRenderable())
			(*iter)->draw(_currentRenderContext);
	}

	SDL_RenderPresent(_currentRenderContext);
}

void TheGame::calcGravity(){
	std::vector<Object*>::iterator iter = _levelObjects.begin();
	for (iter; iter != _levelObjects.end(); ++iter){
		if ((*iter)->getIsMovable()){
			(*iter)->setY((*iter)->getY() + _gravity);
		}
	}
}

void TheGame::detectCollisions(){
	std::vector<Object*>::iterator i = _levelObjects.begin();
	for (i; i != _levelObjects.end(); ++i){
		if ((*i)->getIsMovable()){
			MovableObject* tempObject = dynamic_cast<MovableObject*>(*i);
			CollisionDetector::detectStaticCollisions(tempObject, _levelObjects);
			CollisionDetector::detectDynamicCollisions(tempObject, _levelObjects);
		}
	}
}