#include "invaders.h"

using namespace sf;
class Gamma : public Invaders
{
	public:	
	Gamma()
	{
		tex.loadFromFile("img/PNG/Enemies/enemyGreen4.png");
		//tex.loadFromFile("img/enemy_3.png");
		sprite.setTexture(tex);
		delay = 4;
		num_bombs = 0;
		bombs = new Bomb[4] { Bomb("img/PNG/Lasers/laserGreen14.png") , Bomb("img/PNG/Lasers/laserGreen14.png"),Bomb("img/PNG/Lasers/laserGreen14.png") , Bomb("img/PNG/Lasers/laserGreen14.png")};
		//bombs = new Bomb[1] { Bomb("img/PNG/Lasers/laserGreen14.png") };
	}

	void bomb()
	{
		//std::cout<< " im in gamma \n";
		if(sprite.getPosition().x < 0 || sprite.getPosition().y > 780 || sprite.getPosition().x > 780)
		return;

		bombs[num_bombs].sprite.setPosition(sprite.getPosition().x , sprite.getPosition().y + 40);
		num_bombs++;
		//std::cout<< " out of gamma \n";
	}
	void update_bomb()
	{
		for(int i=0 ; i < num_bombs ; i++)
		{
			if(bombs[i].sprite.getPosition().x < 0 || bombs[i].sprite.getPosition().y > 780 || bombs[i].sprite.getPosition().x > 780)
			{
				for(int j = i ; j < num_bombs; j++)
				{
					bombs[j] = bombs[j+1]; 
					bombs[j].sprite.setTexture(bombs[j].tex);
					bombs[j].sprite.setPosition(bombs[j+1].sprite.getPosition().x , bombs[j+1].sprite.getPosition().y );
				}
				i--;
				num_bombs--;
			}

			else
			bombs[i].update_bomb();
		}
		bombs_active = false;
		for(int i=0 ; i < num_bombs ; i++)
		{

			if(bombs[i].sprite.getPosition().y <= 780 && bombs[i].sprite.getPosition().y >=0 && bombs[i].sprite.getPosition().x <= 780 && bombs[i].sprite.getPosition().x >=0  )
			bombs_active = true;
		}
	}

	/*Gamma& operator =(Gamma& other)
	{
		this->sprite.setPosition(other.sprite.getPosition().x , other.sprite.getPosition().y );
		
		delete[] bombs;
		this-> num_bombs = other.num_bombs;

	 	bombs = other.bombs;
		return *this; 

	}*/
};