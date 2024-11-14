#include "enemy.h"
#include <string>

using namespace std;
using namespace sf;

class Dragon: public Enemy
{
	public:

	string direction; // c , l ,r

	Dragon()
	{
		tex.loadFromFile("img/dragon.png");
		blaze.loadFromFile("img/firebullet.png");
		sprite.setTexture(tex);
		Blaze.setTexture(blaze);
		sprite.setPosition(1000,1000);
		sprite.setScale(1.3,1.3);
		Blaze.setScale(1.1,2.0);
		direction = "";
		//sprite.setScale(0.3,0.3);

	}

	void fire()
	{
		
		
		if(direction == "c")
		{
			Blaze.setRotation(0);
			Blaze.setPosition(sprite.getPosition().x + 80, sprite.getPosition().y + 285);
		}

		else if(direction == 'l')
		{
			Blaze.setRotation(40);
			Blaze.setPosition(sprite.getPosition().x  + 125 , sprite.getPosition().y + 255);
		}

		else if(direction == 'r')
		{
			Blaze.setRotation(-40);
			Blaze.setPosition(sprite.getPosition().x + 85  , sprite.getPosition().y + 350);
		}
	}

	
	string getDirection ()
	{return direction;}

	void setDirection(string d)
	{direction = d;}


	void move ()  {}
	bool getRight() {return true;}
	bool getLeft(){return true;}

};
