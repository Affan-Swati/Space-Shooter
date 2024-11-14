#ifndef DANGER_H_
#define DANGER_H_

#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include "addon.h"

using namespace std;
using namespace sf;
class Danger : public Addon
{
	public:
	
	Danger()
	{
		tex.loadFromFile("img/PNG/Power-ups/danger.png");
		sprite.setTexture(tex);
		sprite.setScale(0.1,0.1);
	}


	void launch ()
	{
		srand(time(0));
		if(!active)
		{
			float x = 30  + rand()%700;
			sprite.setPosition(x,0);	
			active = true;
		}


	}


	void move(int &score)
	{
		if(sprite.getPosition().y >=0 && sprite.getPosition().y <= 780 && active)
		{
			sprite.move(0,0.1f);
		}

		else if(sprite.getPosition().y > 780)
		{
			sprite.setPosition(1000,1000);
			active = false;
			score+=5;
		}

	}

	void move() {};

};
#endif