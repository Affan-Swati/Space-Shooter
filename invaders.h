#ifndef INVADERS_H_
#define INVADERS_H_
#include "enemy.h"
#include <SFML/Audio.hpp>
using namespace sf;
class Invaders : public Enemy
{
	public:

	float delay;
	Bomb *bombs;
	int num_bombs;
	bool bombs_active = false;

	Invaders()
	{
		sprite.setScale(0.6,0.6);
	}


	bool detect_collisions(float X, float Y)
	{
		FloatRect BOMB = sprite.getGlobalBounds();

		float topleftX = sprite.getPosition().x - BOMB.width / 2.0f;
		float topleftY = sprite.getPosition().y - BOMB.height / 2.0f;

		// Check if the coordinates fall within the bounds of the player sprite
		if (X >= topleftX + 5 && X <= topleftX + BOMB.width + 20 &&
			Y >= topleftY && Y <= topleftY + BOMB.height + 10)
		{
			return true;
		}

		return false;
	}

	virtual void bomb()  = 0;
	virtual void update_bomb() =0;
	virtual void move ()  {}
	virtual void fire ()  {}
	virtual bool getRight() {return true;}
	virtual bool getLeft() {return true;}
	virtual string getDirection () {return "l";}
	virtual void setDirection(string d) {}

	


};
#endif