#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "entt/entt.hpp"
#include "nlohmann/json.hpp"


#include "TextureHolder.h"
#include "GlobalSettings.h"
#include "CAnimation.h"
#include "LoadAnimations.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;





int main()
{

	entt::registry Registry; //GAME REGISTRY

    TextureHolder th; //singleton holding all spritesheets


    //this is how we can initialize animation components
	CAnimation deerAnimComponent;
    LoadAnimations(deerAnimComponent, th, "gooTest/sizeAbove.png", "gooTest/sizeAbove.json", AnimState::RUN); 
    
    //assigning it to an entity
    const auto enttdeer = Registry.create();
    Registry.emplace<CAnimation>(enttdeer, deerAnimComponent);

    
    
    //DEMO GAME LOOP USING ANIMATION COMPONENT
    VideoMode vm = VideoMode(240, 180);
    RenderWindow window(vm, "Test", Style::Default);
    Clock clock;
    float fps = 6.0f; 
    while (window.isOpen())
    {
        if (clock.getElapsedTime().asSeconds() > (1/fps))
        {
            clock.restart();
            window.clear();
            
            
            //this part can go into a SAnamationSystem.h
            Registry.view<CAnimation>().each([&] (auto Entity, CAnimation& animComponent)
                {   
                    int totalFrameNum = animComponent.animFrameCoords[AnimState::RUN][AnimDir::E].size();
                                        
                    Sprite sprite;
                    sprite.setTexture(*(animComponent.spritesheet));
                    sprite.setTextureRect(animComponent.animFrameCoords[AnimState::RUN][AnimDir::N][animComponent.frameNum++ % totalFrameNum]);
                    sprite.setPosition(240 / 2 - sprite.getLocalBounds().width/2  , 180 / 2 - sprite.getLocalBounds().height/2);

                    

                    window.draw(sprite);
                });
            
            
            
            window.display();
        }
    }

    
    return 0;
}