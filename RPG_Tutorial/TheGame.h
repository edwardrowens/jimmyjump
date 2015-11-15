#pragma once
#include <SDL2.0/SDL.h>
#include <SDL2.0\SDL_image.h>
#include <string>
#include <iostream>
#include "Errors.h"
#include "MainCharacter.h"
#include "Object.h"
#include <ctime>
#include <vector>
#include "Platform.h"

enum class GameState {PLAY,EXIT};

class TheGame
{
public:
	TheGame();
	~TheGame();

	void run();

private:
	SDL_Window* WindowInitialization();
	void initGame();
	
	int _gravity;
	void calcGravity();
	void detectStaticCollisions(MovableObject* object);
	void detectDynamicCollisions(MovableObject* object);
	void detectCollisions();
	int calcDepthOfPenetration(const SDL_Rect &smalerRect, const SDL_Rect &i);
	std::string generateResolutionErrorMessage(const Object &a, const Object &b, const SDL_Rect &i);

	GameState _currentState;
	SDL_Window* _currentWindow;
	SDL_Renderer* _currentRenderContext;
	SDL_Event _currentEvent;

	//processes input
	const Uint8* _keyState;
	int _eventMade;

	/*vector that contains all objects but the main character. the background of a level should
	always be pushed first*/
	std::vector<Object*> _levelObjects;
	Platform* _gameFloor;

	//game loop
	int processInput();
	void update();
	void draw();

	int jimWidth, jimHeight, jimStartY;
	MainCharacter* jim;

	const std::string BACKGROUND_FNAME;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	const int FPS;
};

