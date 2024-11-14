#ifndef ADDON_H_
#define ADDON_H_

#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include "time.h"
#include "stdlib.h"

using namespace std;
using namespace sf;
class Addon
{
	public:

	Sprite sprite;
	Texture tex;
	bool active = false ;

	virtual void launch() = 0;
	virtual void move() = 0;
	virtual void move(int &score) = 0;




};
#endif