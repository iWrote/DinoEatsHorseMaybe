#pragma once 
#ifndef LOADANIMATIONS_H
#define LOADANIMATIONS_H

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <SFML/Graphics.hpp>

#include "TextureHolder.h"
#include "GlobalSettings.h"
#include "CAnimation.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

void LoadAnimations(CAnimation& animComponent, TextureHolder& th, string sspngPath, string ssjsonPath, AnimState animState = AnimState::IDLE) //if it isn't an animation the names won't have a number appended to them
{
    ifstream ssinfo(ssjsonPath);
    json ssi;
    ssinfo >> ssi;

    for (auto i : ssi.items())
    {
        string animationName = i.key();
        char directionLetter = animationName[animationName.size() - 4];
        if (animationName[animationName.size() - 5] == '_') //ignores the ..._NE_00 kind of entries, takes only _N_00 kind
        {
            vector<IntRect>& frames = animComponent.animFrameCoords[animState][AnimDir(directionLetter)];
            int x = i.value()["frame"]["x"];
            int y = i.value()["frame"]["y"];
            int w = i.value()["frame"]["width"];
            int h = i.value()["frame"]["height"];
            frames.push_back(IntRect(x, y, w, h));

#if _DEBUG
            cout << "assigned " << i.key() << "to " << directionLetter << endl;
#endif
        }// a whole animation for one direction is now saved


    }
    ssinfo.close();

    animComponent.spritesheet = th.GetTexture(sspngPath);
    animComponent.frameNum = 0;

}


#endif // !LOADANIMATIONS_H