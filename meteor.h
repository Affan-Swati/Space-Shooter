#ifndef METEOR_H_
#define METEOR_H_

#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>

using namespace std;
using namespace sf;
class Meteor
{
	public:

	Sprite sprite;
	Texture tex;
	float speed;
	bool active = false;
	
	Meteor(std::string pngpath , float s)
	{
		tex.loadFromFile(pngpath);
		sprite.setTexture(tex);
		sprite.setScale(0.6,0.6);
		sprite.setColor(Color(255,255,255,75));
		speed = s;
	}


	void launch ()
	{
		//srand(time(0));
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
			sprite.move(0,speed);
		}

		else if(sprite.getPosition().y > 780)
		{
			sprite.setPosition(1000,1000);
			active = false;
		}

	}

};
#endif