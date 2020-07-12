#include "Horse.h"

Horse::Horse(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setPosition(m_Position);
}

FloatRect Horse::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite& Horse::getSprite()
{

	return m_Sprite;
}

void Horse::moveRight()
{
	m_MovingRight = true;

}void Horse::moveLeft()
{
	m_MovingLeft = true;
}
void Horse::stopLeft()
{
	m_MovingLeft = false;
}
void Horse::stopRight()
{
	m_MovingRight = false;
}
void Horse::moveUp()
{
	m_MovingUp = true;

}void Horse::moveDown()
{
	m_MovingDown = true;
}
void Horse::stopDown()
{
	m_MovingDown = false;
}
void Horse::stopUp()
{
	m_MovingUp = false;
}
void Horse::setSpeed(float s)
{
	m_Speed = s;
}
void Horse::addSpeed(float s)
{
	m_ExtraSpeed += s;
}
void Horse::setExtraSpeed(float s)
{
	m_ExtraSpeed = s;
}

FloatRect Horse::getHeadPosRect()
{
	FloatRect bounds = m_Sprite.getGlobalBounds();
	float top =0, left =0, width=0, height=0;
	if (m_MovingDown)
	{
		top = bounds.top + bounds.height * 0.66;
		left = bounds.left;
		width = bounds.width;
		height = bounds.height * 0.33;
	}

	if (m_MovingUp)
	{
		top = bounds.top;
		left = bounds.left;
		width = bounds.width;
		height = bounds.height * 0.33;
	}

	if (m_MovingLeft)
	{
		top = bounds.top;
		left = bounds.left;
		width = bounds.width * 0.33;
		height = bounds.height * 0.33;
	}

	if (m_MovingRight)
	{
		top = bounds.top;
		left = bounds.left + bounds.width*0.66;
		width = bounds.width * 0.33;
		height = bounds.height * 0.33;
	}


	return FloatRect(left, top, width, height);
}


void Horse::input()
{
	if (!amDead)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			moveLeft();
			stopRight();
			stopDown();
			stopUp();

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			moveRight();
			stopLeft();
			stopDown();
			stopUp();


		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			moveUp();
			stopRight();
			stopLeft();
			stopDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			moveDown();
			stopRight();
			stopLeft();
			stopUp();

		}
	}
	
}

void Horse::inputWASD()
{
	if (!amDead)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			moveLeft();
			stopRight();
			stopDown();
			stopUp();

		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			moveRight();
			stopLeft();
			stopDown();
			stopUp();


		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			moveUp();
			stopRight();
			stopLeft();
			stopDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			moveDown();
			stopRight();
			stopLeft();
			stopUp();

		}
	}
}

void Horse::setAnimation(Time dt)
{
	timeSinceAnimUpdate += dt.asSeconds();

	if (timeSinceAnimUpdate > (1 / canim.fps))
	{
		if (m_MovingLeft)
		{
			int totalFrameNum = canim.animFrameCoords[AnimState::RUN][AnimDir::W].size();


			m_Sprite.setTexture(*(canim.spritesheet));
			m_Sprite.setTextureRect(canim.animFrameCoords[AnimState::RUN][AnimDir::W][canim.frameNum++ % totalFrameNum]);


		}
		if (m_MovingRight)
		{
			int totalFrameNum = canim.animFrameCoords[AnimState::RUN][AnimDir::E].size();


			m_Sprite.setTexture(*(canim.spritesheet));
			m_Sprite.setTextureRect(canim.animFrameCoords[AnimState::RUN][AnimDir::E][canim.frameNum++ % totalFrameNum]);


		}
		if (m_MovingDown)
		{
			int totalFrameNum = canim.animFrameCoords[AnimState::RUN][AnimDir::S].size();


			m_Sprite.setTexture(*(canim.spritesheet));
			m_Sprite.setTextureRect(canim.animFrameCoords[AnimState::RUN][AnimDir::S][canim.frameNum++ % totalFrameNum]);


		}
		if (m_MovingUp)
		{
			int totalFrameNum = canim.animFrameCoords[AnimState::RUN][AnimDir::N].size();


			m_Sprite.setTexture(*(canim.spritesheet));
			m_Sprite.setTextureRect(canim.animFrameCoords[AnimState::RUN][AnimDir::N][canim.frameNum++ % totalFrameNum]);


		}

		timeSinceAnimUpdate = 0;

	}
}


void Horse::update(Time dt)
{
	if (switchCooldownSeconds > 0) switchCooldownSeconds -= dt.asSeconds();

	setAnimation(dt);

	if (m_MovingLeft)
	{
		m_Position.x -= (m_Speed+m_ExtraSpeed) * dt.asSeconds();

	}

	if (m_MovingRight)
	{
		m_Position.x += (m_Speed+m_ExtraSpeed) * dt.asSeconds();
	}

	if (m_MovingDown)
	{
		m_Position.y += (m_Speed+m_ExtraSpeed) * dt.asSeconds();

	}

	if (m_MovingUp)
	{
		m_Position.y -= (m_Speed+m_ExtraSpeed) * dt.asSeconds();
	}


	//keeping horse IN bounds
	if (m_Sprite.getGlobalBounds().left < -m_Sprite.getGlobalBounds().width)
	{
		m_Position.x = 1920;
	}
	if (m_Sprite.getGlobalBounds().left > 1920)
	{
		m_Position.x = -m_Sprite.getGlobalBounds().width;
	}

	if (m_Sprite.getGlobalBounds().top < -m_Sprite.getGlobalBounds().height)
	{
		m_Position.y = 1080;
	}
	if (m_Sprite.getGlobalBounds().top > 1080)
	{
		m_Position.y = -m_Sprite.getGlobalBounds().height;
	}

	m_Sprite.setPosition(m_Position);
	
}

