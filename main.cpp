#include "Horse.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

#include "src_anim/TextureHolder.h"
#include "src_anim/GlobalSettings.h"
#include "src_anim/CAnimation.h"
#include "src_anim/LoadAnimations.h"



int main()
{
	bool gameOver = false;

	SoundBuffer nublyatB;
	nublyatB.loadFromFile("sound/death.wav");
	Sound nublyat; nublyat.setBuffer(nublyatB);
	//WINDOW
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "GMTK20", Style::Default);

	//SCENE INIT	
	

	const float SWCDN = .3f;
	TextureHolder th; //singleton holding all spritesheets
	CAnimation horseAnim;
	CAnimation trexAnim;
	CAnimation horseDeadAnim;
	CAnimation grassAnim;
	LoadAnimations(horseAnim, th, "graphics/horse/horseSheet.png", "graphics/horse/horseSheet.json", AnimState::RUN);
	LoadAnimations(trexAnim, th, "graphics/trex/trexSheet.png", "graphics/trex/trexSheet.json", AnimState::RUN);
	LoadAnimations(horseDeadAnim, th, "graphics/horseDead/horseDeadSheet.png", "graphics/horseDead/horseDeadSheet.json", AnimState::RUN);
	LoadAnimations(grassAnim, th, "graphics/grass/grassSheet.png", "graphics/grass/grassSheet.json", AnimState::IDLE);
	horseAnim.fps = 9; trexAnim.fps = 10; horseDeadAnim.fps = 3; grassAnim.fps = 4;
	
	vector<Vector2f> grassDrawPos;
	Sprite grassSprite; grassSprite.setTexture(*grassAnim.spritesheet);

	Horse horse(1920 / 2, 1080 - 100);
	horse.canim = horseAnim;
	horse.setSpeed(1000.0f);
	horse.getSprite().setScale(2,2);

	Horse horse2(1920 / 2, 100);
	horse2.canim = horseAnim;
	horse2.setSpeed(1000.0f);
	horse2.getSprite().setScale(2, 2);

	float randomSwitchTimer = 10;
	

	Text hud;
	Font font;
	font.loadFromFile("fonts/consola.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);
	string contextstr = "joeypuggy";

	Clock clock;

	while (window.isOpen())
	{

		//INPUT & Switching
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

		}
		horse.input();
		horse2.inputWASD();

		if (randomSwitchTimer <= 0 && !gameOver)
		{
			randomSwitchTimer = (rand() % 5 + 5);
			if (horse.amHorse && horse.switchCooldownSeconds <= 0)
			{
				horse.canim = trexAnim;
				horse.setSpeed(400.0f);
				horse.amHorse = false;
				cout << "changine to trex\n";
				horse.switchCooldownSeconds = SWCDN;

			}

			if (!horse.amHorse && horse.switchCooldownSeconds <= 0)
			{
				horse.canim = horseAnim;
				horse.setSpeed(1000.0f);
				horse.amHorse = true;
				cout << "changine to horse\n";
				horse.switchCooldownSeconds = SWCDN;

			}

			if (horse2.amHorse && horse2.switchCooldownSeconds <= 0)
			{
				horse2.canim = trexAnim;
				horse2.setSpeed(400.0f);
				horse2.amHorse = false;
				cout << "changine 2  to trex\n";
				horse2.switchCooldownSeconds = SWCDN;

			}

			if (!horse2.amHorse && horse2.switchCooldownSeconds <= 0)
			{
				horse2.canim = horseAnim;
				horse2.setSpeed(1000.0f);
				horse2.amHorse = true;
				cout << "changine 2 to horse2\n";
				horse2.switchCooldownSeconds = SWCDN;

			}

			switch (1)
			{
			case 1:
				grassDrawPos.push_back(Vector2f((rand() % 1820) + 50, (rand() % 980) + 50));
			default:
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Slash))
		{
			if (horse.amHorse && horse.switchCooldownSeconds <= 0)
			{
				horse.canim = trexAnim;
				horse.setSpeed(400.0f);
				horse.amHorse = false;
				cout << "changine to trex\n";
				horse.switchCooldownSeconds = SWCDN;

			}

			if (!horse.amHorse && horse.switchCooldownSeconds <= 0)
			{
				horse.canim = horseAnim;
				horse.setSpeed(1000.0f);
				horse.amHorse = true;
				cout << "changine to horse\n";
				horse.switchCooldownSeconds = SWCDN;

			}
		}

		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			if (horse2.amHorse && horse2.switchCooldownSeconds <= 0)
			{
				horse2.canim = trexAnim;
				horse2.setSpeed(400.0f);
				horse2.amHorse = false;
				cout << "changine 2  to trex\n";
				horse2.switchCooldownSeconds = SWCDN;

			}

			if (!horse2.amHorse && horse2.switchCooldownSeconds <= 0)
			{
				horse2.canim = horseAnim;
				horse2.setSpeed(1000.0f);
				horse2.amHorse = true;
				cout << "changine 2 to horse2\n";
				horse2.switchCooldownSeconds = SWCDN;

			}
		}



		//COLLISIONS


		sf::RectangleShape rectangle1;
		rectangle1.setOutlineColor(sf::Color::Red);
		rectangle1.setOutlineThickness(1);
		rectangle1.setFillColor(Color(0, 0, 0, 0));
		FloatRect hr = horse.getHeadPosRect();
		rectangle1.setPosition(Vector2f(hr.left, hr.top));
		rectangle1.setSize(Vector2f(hr.width, hr.height));

		sf::RectangleShape rectangle2;
		rectangle2.setOutlineColor(sf::Color::Blue);
		rectangle2.setOutlineThickness(1);
		rectangle2.setFillColor(Color(0, 0, 0, 0));
		FloatRect hr2 = horse2.getHeadPosRect();
		rectangle2.setPosition(Vector2f(hr2.left, hr2.top));
		rectangle2.setSize(Vector2f(hr2.width, hr2.height));

		if (!gameOver)
		{
			if (rectangle1.getGlobalBounds().intersects(horse2.getSprite().getGlobalBounds()) && !horse.amHorse && horse2.amHorse)
			{
				rectangle1.setOutlineColor(sf::Color::Green);

				contextstr = "player1 IS EATING player2 !?!?\n(Hit escape to quit.)";
				nublyat.play();
				horse2.amDead = true;
				horse2.canim = horseDeadAnim;
				horse.setSpeed(0);
				horse2.setSpeed(0);
				horse.setExtraSpeed(0);
				horse2.setExtraSpeed(0);

				gameOver = true;

			}

			if (rectangle2.getGlobalBounds().intersects(horse.getSprite().getGlobalBounds()) && horse.amHorse && !horse2.amHorse)
			{
				rectangle2.setOutlineColor(sf::Color::Green);


				contextstr = "player2 IS EATING player1!?!?\n(Hit escape to quit.)";
				nublyat.play();
				horse.amDead = true;
				horse.canim = horseDeadAnim;
				horse.setSpeed(0);
				horse.setExtraSpeed(0);
				horse2.setSpeed(0);
				horse2.setExtraSpeed(0);
				gameOver = true;
			}
			for (auto grassPos : grassDrawPos)
			{
				if (rectangle1.getGlobalBounds().contains(grassPos) && horse.amHorse)
				{
					horse.addSpeed(40);
					int i = 0;
					for (auto delPos : grassDrawPos)
					{ 
						if (grassPos == delPos)
						{
							grassDrawPos.erase(grassDrawPos.begin() + i);
							break;
						}
						i++;

					}
				}
				if (rectangle2.getGlobalBounds().contains(grassPos) && horse2.amHorse)
				{
					horse2.addSpeed(40);
					int i = 0;
					for (auto delPos : grassDrawPos)
					{
						if (grassPos == delPos)
						{
							grassDrawPos.erase(grassDrawPos.begin() + i);
							break;
						}
						i++;

					}
				}
			}
		}



		//UPDATE 
		Time dt = clock.restart();
		randomSwitchTimer -= dt.asSeconds();
		horse.update(dt);
		horse2.update(dt);

		std::stringstream ss;
		ss << contextstr << " " << int(randomSwitchTimer);
		hud.setString(ss.str());



		//draw

		window.clear();

		for (auto grassPos : grassDrawPos)
		{
			grassSprite.setTextureRect(grassAnim.animFrameCoords[AnimState::IDLE][AnimDir::N][rand() % 5]);
			grassSprite.setPosition(grassPos);
			window.draw(grassSprite);
		}
		
		window.draw(horse.getSprite());
		window.draw(horse2.getSprite());

		window.draw(hud);

	
		window.draw(rectangle1);
		window.draw(rectangle2);


		window.display();
	}


	return 0;
}

