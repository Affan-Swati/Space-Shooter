#include "enemy.h"
using namespace sf;

class Monster: public Enemy
{
	public:

	bool center , left , right;

	Monster()
	{
		tex.loadFromFile("img/monster1.png");
		//tex.loadFromFile("img/adil.jpeg");
		lightning.loadFromFile("img/PNG/lightning1.png");
		sprite.setTexture(tex);
		Lightning.setTexture(lightning);
		Lightning.setScale(1,1.8);
		sprite.setPosition(1000,1000);
		//sprite.setScale(0.1,0.1);
		sprite.setScale(0.3,0.3);
		center = true;
		right = false;
		left = false;

	}

	void move()
	{
		//std::cout<<sprite.getPosition().x << sprite.getPosition().y << ""<<std::endl;
		if(center)
		{	
			sprite.move(0.1,0);
			center = false;
			right = true;
			left = false;
		}

		else if (right)
		{
			if(sprite.getPosition().x >= 580)
			{
				right = center =  false;
				left = true;
			}

			else
			{
				sprite.move(0.1,0);
			}
		}

		else if (left)
		{
			if(sprite.getPosition().x <= 0)
			{
				left = center =  false;
				right = true;
			}

			else
			{
				sprite.move(-0.1,0);
			}

		}


	}

	void fire()
	{	
		Lightning.setPosition(sprite.getPosition().x -130 , sprite.getPosition().y + 80);
	}

	bool getRight()
	{return right;}

	bool getLeft()
	{return left;}

	string getDirection () {return "l";}
	void setDirection(string d) {}






};
