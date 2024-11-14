#ifndef ENEMY_H_
#define ENEMY_H_

#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include "bomb.h"

using namespace std;
using namespace sf;
class Enemy
{
	public:
		Sprite sprite ,  Lightning , Blaze;
		Texture tex , lightning , blaze;
		

	virtual void move ()  = 0;
	virtual void fire ()  = 0;
	virtual bool getRight() = 0;
	virtual bool getLeft() = 0;
	virtual string getDirection () = 0;
	virtual void setDirection(string d) = 0;
	

};
#endif