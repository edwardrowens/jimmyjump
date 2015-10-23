#include "TheGame.h"


TheGame::TheGame() : _currentWindow(nullptr), WINDOW_HEIGHT(600), WINDOW_WIDTH(768), FPS(15),
_currentState(GameState::PLAY), jimHeight(50), jimWidth(50), _eventMade(0), jim(nullptr)
, BACKGROUND_FNAME("Background.png"), _gravity(-5), _gameFloor(nullptr)
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
	Platform platform(50, 50, 100, 100);
	Platform platform2(400, 100, 100, 100);

	background.setTexturePath("Background.png");
	background.setObjectTexture(_currentRenderContext);

	platform2.setTexturePath("LandPiece_LightGray.png");
	platform2.setObjectTexture(_currentRenderContext);

	platform.setTexturePath("LandPiece_LightGreen.png");
	platform.setObjectTexture(_currentRenderContext);

	jim->setTexturePath("CharacterLeft_Standing.png");
	jim->setObjectTexture(_currentRenderContext);

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

	//_gameFloor = new Platform(0,WINDOW_HEIGHT - ((2.0/23)*WINDOW_HEIGHT)),10,WINDOW_WIDTH);
	_gameFloor = new Platform();
	_gameFloor->setIsRenderable(false);
	_gameFloor->setX(0);
	_gameFloor->setY(WINDOW_HEIGHT - ((2.0 / 23)*WINDOW_HEIGHT));
	_gameFloor->setHeight(10);
	_gameFloor->setWidth(WINDOW_WIDTH);

	int startingJimHeight = WINDOW_HEIGHT - (jimHeight - 7) - ((2.0 / 23)*WINDOW_HEIGHT);
	jim = new MainCharacter(0, startingJimHeight, jimWidth, jimHeight);
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
	_keyState = SDL_GetKeyboardState(&size);
	return _eventMade = SDL_PollEvent(&_currentEvent);
}

void TheGame::update(){
	jim->setPreviousMovement(jim->getCurrentMovement());
	jim->setPreviousXY(jim->getX(), jim->getY());
	calcGravity();
	jim->moveLeft();

	//change walkcycles!!!
	if (_keyState[SDL_SCANCODE_D] && !_keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::right);
		jim->moveRight();

		if (jim->getTexturePath().find("Left", 0) != jim->getTexturePath().npos){
			jim->setTexturePath("CharacterRight_Standing.png");
		}
		else if (jim->getTexturePath().find("2", 0) != jim->getTexturePath().npos){
			jim->setTexturePath("CharacterRight_Walk1.png");
		}
		else{
			jim->setTexturePath("CharacterRight_Walk2.png");
		}
	}

	else if (_keyState[SDL_SCANCODE_A] && !_keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::left);
		jim->moveLeft();

		if (jim->getTexturePath().find("Right", 0) != jim->getTexturePath().npos){
			jim->setTexturePath("CharacterLeft_Standing.png");
		}
		else if (jim->getTexturePath().find("2", 0) != jim->getTexturePath().npos){
			jim->setTexturePath("CharacterLeft_Walk1.png");
		}
		else{
			jim->setTexturePath("CharacterLeft_Walk2.png");
		}
	}
	else if (_keyState[SDL_SCANCODE_W]){
		jim->setCurrentMovement(MovableObject::Movements::jump);
		if (jim->getY() == (WINDOW_HEIGHT - (jimHeight - 7) - ((2.0 / 23)*WINDOW_HEIGHT)))
			jim->jump();

		if (_keyState[SDL_SCANCODE_D]){
			jim->setTexturePath("CharacterRight_Jump.png");
		}
		else{
			jim->setTexturePath("CharacterLeft_Jump.png");
		}
	}
	else{
		jim->setCurrentMovement(MovableObject::Movements::none);
	}

	if (jim->getY() > (WINDOW_HEIGHT - (jimHeight - 7) - ((2.0 / 23)*WINDOW_HEIGHT))){
		if (jim->getTexturePath().find("Right", 0) != jim->getTexturePath().npos)
			jim->setTexturePath("CharacterRight_Jump.png");
		else
			jim->setTexturePath("CharacterLeft_Jump.png");
	}
	// make sure jim doesn't exit screen
	if ((jim->getX() + jim->getWidth()) > WINDOW_WIDTH)
		jim->setX(WINDOW_WIDTH - jim->getWidth());

	if (jim->getX() < 0)
		jim->setX(0);

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
		if ((*iter)->getIsMovable())
			(*iter)->setObjectTexture(_currentRenderContext);
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
			detectStaticCollisions(tempObject);
			detectDynamicCollisions(tempObject);
		}
	}
}

void TheGame::detectDynamicCollisions(MovableObject* object){

}

// detects collisions between static objects
void TheGame::detectStaticCollisions(MovableObject* object){
	std::vector<Object*>::iterator i = _levelObjects.begin();
	for (i; i != _levelObjects.end(); ++i){
		float angle = object->calcAngleOfMovement();
		if ((*i)->getIsPlatform()){
			SDL_Rect intersection;
			float angle = 0.0f;
			if (SDL_IntersectRect((*i)->getSDLRect(), object->getSDLRect(),&intersection)){
				//float angle = object->calcAngleOfMovement();
				//(*i)->setX((*i)->getX() - )

				/*switch (object->getCurrentMovement()){
				case MovableObject::Movements::right:
					object->setX(object->getX() - intersection.x);
					break;
				case MovableObject::Movements::left:
					object->setX(object->getX() + intersection.x);
					break;
				case MovableObject::Movements::jump:
					break;
				case MovableObject::Movements::down:
					break;
				}*/
			}
		}
	}
}