#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "src_anim/GlobalSettings.h"
#include "src_anim/CAnimation.h"

using namespace sf;
using namespace std;
class Horse
{
private:
	Vector2f m_Position;

	Sprite m_Sprite;

	float m_Speed = 1000.0f;
	float m_ExtraSpeed = 0.0f;

	float timeSinceAnimUpdate = 0;

	

	bool m_MovingRight = false;
	bool m_MovingLeft = false;
	bool m_MovingUp = false;
	bool m_MovingDown = false;

	void setAnimation(Time dt);

public:
	Horse(float startX, float startY);

	FloatRect getPosition();
	FloatRect getHeadPosRect();

	Sprite& getSprite();

	CAnimation canim;

	bool amHorse = true;
	bool amDead = false;

	float switchCooldownSeconds = 0.1f;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void stopLeft();
	void stopRight();
	void stopUp();
	void stopDown();

	void setSpeed(float s);
	void setExtraSpeed(float s);
	void addSpeed(float s);

	void update(Time dt);
	void input();
	void inputWASD();
};