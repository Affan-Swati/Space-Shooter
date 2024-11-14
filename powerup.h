#ifndef POWERUP_H_
#define POWERUP_H_

#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include "addon.h"

using namespace std;
using namespace sf;
class Powerup : public Addon
{
	public:
	
	Powerup()
	{
		tex.loadFromFile("img/PNG/Power-ups/bolt_gold.png");
		sprite.setTexture(tex);
	}


	void launch ()
	{
		srand(time(0));
		if(!active)
		{
			float x = 10  + rand()%750;
			sprite.setPosition(x,0);	
			active = true;
		}


	}


	void move()
	{
		if(sprite.getPosition().y >=0 && sprite.getPosition().y <= 780 && active)
		{
			sprite.move(0,0.1f);
		}

		else if(sprite.getPosition().y > 780)
		{
			sprite.setPosition(1000,1000);
			active = false;
		}

	}

	void move(int &score) {};

};
#endif