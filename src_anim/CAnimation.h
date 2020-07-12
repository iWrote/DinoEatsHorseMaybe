#pragma once
#ifndef CANIMATION_H
#define CANIMATION_H
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "GlobalSettings.h"

using namespace std;
using namespace sf;



struct CAnimation
{
	Texture* spritesheet;
	map<AnimState, map<AnimDir, vector<IntRect>>> animFrameCoords; //intended usage: animFrameCoords[RUN][E][3]
	unsigned int frameNum; //just a counter
	float fps = 9;
};

#endif // !CANIMATION_H
