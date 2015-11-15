#pragma once

#include <iostream>
#include <string>

//currently takes a function pointer to whatever get error function you want to use but it seems
//IMG_GetError() and SDL_GetError() are the same thing. I'm leaving this in for now
extern void PrintErrors(std::string error, const char* (*errorFcn)());

extern void PrintErrors(std::string error);
