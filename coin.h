#ifndef COIN_H_
#define COIN_H_

#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include "addon.h"

using namespace std;
using namespace sf;
class Coin : public Addon
{
	public:

	Texture tex2 , tex3 , tex4 , tex5 , tex6;
	Sprite sp2 , sp3 , sp4 , sp5 , sp6;
	bool one , two , three ,four , five , six;
	
	Coin()
	{
		tex.loadFromFile("img/PNG/Power-ups/coin.png");
		tex2.loadFromFile("img/PNG/Power-ups/coin2.png");
		tex3.loadFromFile("img/PNG/Power-ups/coin3.png");
		tex4.loadFromFile("img/PNG/Power-ups/coin4.png");
		tex5.loadFromFile("img/PNG/Power-ups/coin5.png");
		tex6.loadFromFile("img/PNG/Power-ups/coin6.png");
		sprite.setTexture(tex);
		sp2.setTexture(tex2);
		sp3.setTexture(tex3);
		sp4.setTexture(tex4);
		sp5.setTexture(tex5);
		sp6.setTexture(tex6);
		sprite.setScale(0.025,0.025);
		sp2.setScale(0.025,0.025);
		sp3.setScale(0.025,0.025);
		sp4.setScale(0.025,0.025);
		sp5.setScale(0.025,0.025);
		sp6.setScale(0.025,0.025);
		one = true;
		two = three = four = five = six = false;
	}


	void launch ()
	{
		srand(time(0));
		if(!active)
		{
			float x = 30  + rand()%700;
			sprite.setPosition(x,0);
			sp2.setPosition(x,0);
			sp3.setPosition(x,0);
			sp4.setPosition(x,0);
			sp5.setPosition(x,0);
			sp6.setPosition(x,0);	
			active = true;
		}


	}

	float gety()
	{
		return sprite.getPosition().y;
	}

	void move()
	{
		if(sprite.getPosition().y >=0 && sprite.getPosition().y <= 780 && active)
		{
			sprite.move(0,0.1f);
			sp2.move(0,0.1f);
			sp3.move(0,0.1f);
			sp4.move(0,0.1f);
			sp5.move(0,0.1f);
			sp6.move(0,0.1f);

		}

		else if(sprite.getPosition().y > 780)
		{
			sprite.setPosition(1000,0);
			sp2.setPosition(1000,0);
			sp3.setPosition(1000,0);
			sp4.setPosition(1000,0);
			sp5.setPosition(1000,0);
			sp6.setPosition(1000,0);	
			active = false;
		}

		if(gety() >= 32.5 && gety() < 65 )
		{
			one = false; two = true;
		}

		else if(gety() >= 65 && gety() < 97.5)
		{	
			two = false ; three = true;
		}

		else if(gety() >= 97.5 && gety() < 130)
		{	
			three = false ; four = true;
		}

		else if(gety() >= 130 && gety() < 162.5)
		{	
			four = false ; five = true;
		}

		else if(gety() >= 162.5 && gety() < 195)
		{	
			five = false ; six = true;
		}

		else if(gety() >= 195 && gety() < 227.5 )
		{
			one = true; six = false;
		}

		else if(gety() >= 227.5 && gety() < 260)
		{	
			one = false ; two = true;
		}

		else if(gety() >=  260 && gety() < 292.5)
		{	
			two = false ; three = true;
		}

		else if(gety() >= 292.5 && gety() < 325)
		{	
			three = false ; four = true;
		}

		else if(gety() >= 325 && gety() < 357.5)
		{	
			four = false ; five = true;
		}

		else if(gety() >= 357.5 && gety() < 390)
		{	
			five = false ; six = true;
		}

		else if (gety() >= 390 && gety() <= 422.5)
		{
			six = false ; one = true;
		}

		if(gety() >= 422.5 && gety() < 455 )
		{
			one = false; two = true;
		}

		else if(gety() >= 455 && gety() < 487.5)
		{	
			two = false ; three = true;
		}

		else if(gety() >= 487.5 && gety() < 520)
		{	
			three = false ; four = true;
		}

		else if(gety() >= 520 && gety() < 552.5)
		{	
			four = false ; five = true;
		}

		else if(gety() >= 552.5 && gety() < 585)
		{	
			five = false ; six = true;
		}

		else if(gety() >= 585 && gety() < 617.5 )
		{
			one = true; six = false;
		}

		else if(gety() >= 617.5 && gety() < 650)
		{	
			one = false ; two = true;
		}

		else if(gety() >=  650  && gety() < 682.5)
		{	
			two = false ; three = true;
		}

		else if(gety() >= 682.5 && gety() < 715)
		{	
			three = false ; four = true;
		}

		else if(gety() >= 715 && gety() < 747.5)
		{	
			four = false ; five = true;
		}

		else if(gety() >= 747.5 && gety() < 780)
		{	
			five = false ; six = true;
		}

		else if (gety()>=780)
		{
			six = false ; one = true;
		}


	}

	void move(int &score) {};

};
#endif