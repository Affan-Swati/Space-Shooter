#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string.h>
#include <iostream>
#include <cmath>
#include "bullet.h"
using namespace sf;
using namespace std;

class Player
{
	public:

	Texture tex , tex45 , tex_45 , tex_black , fire_tex , tex_flame , tex_flame45 , tex_flame315;
	Sprite sprite , fire_sprite , flame , flame45 , flame315;
    Music hit  , powerup;

    bool fire_ball = false , Powerup = false;

	float speed=0.2;
	int x,y;

    int addon_count = 0;
	Bullet* bullets;
	int bullets_count = 0;

	Sprite kill_sprite;
	Texture kill_tex;

Player(std::string png_path)
{

	tex.loadFromFile(png_path);
    tex45.loadFromFile("img/player_ship_45.png");
    tex_45.loadFromFile("img/player_ship_-45.png");
    kill_tex.loadFromFile("img/explosion1.png");
    tex_black.loadFromFile("img/play_ship_bw.png");
    fire_tex.loadFromFile("img/PNG/Lasers/laserRed01.png");
    tex_flame.loadFromFile("img/jettflame.png");
    tex_flame45.loadFromFile("img/jettflame_45.png");
    tex_flame315.loadFromFile("img/jettflame_-45.png");
    fire_sprite.setTexture(fire_tex);
    flame.setTexture(tex_flame);
    flame45.setTexture(tex_flame45);
    flame315.setTexture(tex_flame315);
    hit.openFromFile("sounds/hit.wav");
    powerup.openFromFile("sounds/powerup.wav");
    powerup.setVolume(150.0f);
	hit.setVolume(100.0f);
	sprite.setTexture(tex);
	x=340;y=700;
	sprite.setPosition(x,y);
	sprite.setScale(0.75,0.75);
    flame.setScale(0.25,0.25);
    flame45.setScale(0.25,0.25);
    flame315.setScale(0.25,0.25);
    flame.setColor(Color(255,255,255,150));
    flame45.setColor(Color(255,255,255,150));
    flame315.setColor(Color(255,255,255,150));
}

float get_x()
{

    return sprite.getPosition().x;
}

float get_y()
{
    return sprite.getPosition().y;
}

void fire(bool u, bool d , bool l , bool r)
{
    if(!Powerup) // condition for powerup integrated in fire function so we can fire in 7 directions using the same function call
    {
        if(bullets_count == 0 )
        bullets = new Bullet[1];

        else
        {
            Bullet *temp = new Bullet [bullets_count + 1 ];

            for(int i=0 ; i <bullets_count ; i++)
            {
                temp[i] = bullets [i];
            }

            delete[] bullets;
            bullets = temp;

        }

        if(fire_ball) // fireball is basically the fire_tex i.e the red bullet 
        {
            bullets[bullets_count].fire_ball = true;
            bullets[bullets_count].sprite.setTexture(fire_tex);
            bullets[bullets_count].sprite.setScale(1,0.5);
        }

        else
        {
            bullets[bullets_count].fire_ball = false;
            bullets[bullets_count].sprite.setTexture(bullets[bullets_count].tex);
            bullets[bullets_count].sprite.setScale(1,0.5);
        }

        
    
        if( ( u && r ) ||  (d && l))
        {
            bullets[bullets_count].right_tilt = true;
            bullets[bullets_count].left_tilt = false;
            bullets[bullets_count].vertical = false;
            bullets[bullets_count].sprite.setPosition(sprite.getPosition().x + 100 , sprite.getPosition().y - 30);
            bullets[bullets_count].rotate_bullet(45 , bullets[bullets_count]);
        
        }

        else if (( u && l ) ||  (d && r))
        {
            bullets[bullets_count].right_tilt = false;
            bullets[bullets_count].left_tilt = true;
            bullets[bullets_count].vertical = false;
            bullets[bullets_count].sprite.setPosition(sprite.getPosition().x - 25, sprite.getPosition().y - 10);
            bullets[bullets_count].rotate_bullet(-45 , bullets[bullets_count]);

        }

        else
        {
            bullets[bullets_count].right_tilt = false;
            bullets[bullets_count].left_tilt = false;
            bullets[bullets_count].vertical = true;
            bullets[bullets_count].sprite.setPosition(sprite.getPosition().x + 30 , sprite.getPosition().y - 40);

        }

        bullets_count++;
    }

    else
    {
        float diff = -67.5f;

            if(addon_count == 0)
            {
                bullets = new Bullet [7];
                bullets_count = 7;
                addon_count ++;

                for(int i=0 ; i< 7; i++)
                {
                    bullets[i].fire_ball = true;
                    bullets[i].sprite.setTexture(fire_tex);
                    bullets[i].sprite.setScale(1,0.5);
                    bullets[i].sprite.setPosition(sprite.getPosition().x + 30 + diff, sprite.getPosition().y - 40) ;
                    bullets[i].sprite.setRotation(diff);
                    diff += 22.5f;
                    
                }
                
            }

            else 
            {
                Bullet *temp = new Bullet [bullets_count + 7];
                for(int i=0 ; i < bullets_count ; i++)
                {
                    temp[i] = bullets[i];
                }

                float diff = -67.5f;

                for(int i=bullets_count ; i<bullets_count + 7; i++)
                {
                    temp[i].fire_ball = true;
                    temp[i].sprite.setTexture(fire_tex);
                    temp[i].sprite.setScale(1,0.5);
                    temp[i].sprite.setPosition(sprite.getPosition().x + 30 + diff , sprite.getPosition().y - 40);
                    temp[i].sprite.setRotation(diff);
                    diff+=22.5f;



                }

                bullets_count +=7;
                delete [] bullets;
                bullets = temp;
                addon_count++;


            }

            




    }
}

void update_fire()
{

    if(!Powerup) // powerup is integrated here aswell so we dont have to make multiple function calls
    {
        int index = -1;
        for(int i=0 ; i < bullets_count ; i++)
        {
            if(bullets[i].sprite.getPosition().x == -1000 || bullets[i].sprite.getPosition().y  == -1000)
            {
                index = i;
            }

            else
            {
                bullets[i].update_bullet();
            }
        }

        if(index != -1)
        {
            Bullet *temp = new Bullet [bullets_count - 1];

            int j=0;
            for(int i=0 ; i <bullets_count ; i++)
            {
                if(i!=index)
                {
                    temp[j] = bullets[i];
                    j++;
                }

            }

            delete[]bullets;
            bullets = temp;
            bullets_count--;
        }
    }

    else
    {
        for(int i=0 ; i < bullets_count ; i++)
        {
            if(bullets[i].sprite.getPosition().y < 0 || bullets[i].sprite.getPosition().x > 780 || bullets[i].sprite.getPosition().x < 0 )
            {
                bullets[i].sprite.setPosition(-2000,-2000);
            }

            if(bullets[i].sprite.getRotation() == 337.5)
            bullets[i].sprite.move(-0.08f,-0.20f);

            else if(bullets[i].sprite.getRotation() == 315)
            bullets[i].sprite.move(-0.20f,-0.20f);

            else if(bullets[i].sprite.getRotation() == 292.5)
            bullets[i].sprite.move(-0.36f,-0.20f);

            else if(bullets[i].sprite.getRotation() == 0)
            bullets[i].sprite.move(0.0f,-0.20f);

            else if(bullets[i].sprite.getRotation() == 22.5)
            bullets[i].sprite.move(0.08f,-0.20f);

            else if(bullets[i].sprite.getRotation() == 45)
            bullets[i].sprite.move(0.20f,-0.20f);

            else if(bullets[i].sprite.getRotation() == 67.5)
            bullets[i].sprite.move(0.36f,-0.20f);

        }
    }

}

//-----------------------DETECTIG PLAYER COLLISIONS WITH BOMBS AND ADDONS------////////////////

bool detect_collisions(float bombX, float bombY, bool friendly)
{
    FloatRect spaceship = sprite.getGlobalBounds();

    //Getting top left corner of space ship
    float topleftX = get_x() - spaceship.width / 2;
    float topleftY = get_y() - spaceship.height / 2;

    // Checking  if the bomb's coordinates fall within the bounds of the player sprite
    if (bombX >= topleftX  && bombX <= topleftX +  spaceship.width + 20 &&
        bombY >= topleftY && bombY <= topleftY + spaceship.height + 20)
    {
        if (!friendly)
        {
            hit.stop();
            hit.play();
            kill_effect(bombX, bombY);
        }
        else
        {
            powerup.stop();
            powerup.play();
        }
        return true;
    }

    return false;
}


//------------------------DETECTING PLAYER COLLISIONS WITH MONSTER'S LIGHTNING--------------//
bool detect_collision(float x)
{
    FloatRect playerBounds = sprite.getGlobalBounds();
    float playerX = playerBounds.left;

    float lightningWidth = 250.f;

    if( (x + lightningWidth >= playerX) && (x <= playerX + playerBounds.width))
    {
        kill_effect(sprite.getPosition().x , sprite.getPosition().y);
        hit.stop();
        hit.play();
        return true;
    }

    else
    return false;
}


//----------------------- DETETCTING PLAYER'S COLLISIONS WITH DRAGON'S FIRE ------------------//
//CONCEPT OF NATHEMATICS y = mx + c used here

bool dragon_collision(std::string direction)
{
    if(direction == "l")
    {
        
        if((round(780.0f-sprite.getPosition().y)) == round(sprite.getPosition().x))
        {
            hit.stop();
            hit.play();
            return true;
        }

    }

    else if ( direction == "r")
    {
        if((round(sprite.getPosition().y) == round(sprite.getPosition().x)))
        {
            hit.stop();
            hit.play();
            return true;
        }
    }

    else if( direction == "c")
    {
        if(sprite.getPosition().x >=340 && sprite.getPosition().x <=420)
         {
            hit.stop();
            hit.play();
            return true;
        }
    }

    return false;

}




void kill_effect(float bombX, float bombY)
{		
	kill_sprite.setTexture(kill_tex);
	
	kill_sprite.setPosition(get_x() -60 ,get_y() - 70);
	kill_sprite.setScale(0.3,0.3);		

}

void black_color()
{
    sprite.setTexture(tex_black);
}

void move(std::string s)
{
    float delta_x = 0, delta_y = 0;
    float width = 780;
    float height = 780;
	
    if (s == "u") 
	{
        flame.setPosition(sprite.getPosition().x + 15 , sprite.getPosition().y + 70);
        delta_y = -1;
    }
    else if (s == "d") 
	{
        delta_y = 1;
        
    }
    else if (s == "r") 
	{
        delta_x = 1;
    }
    else if (s == "l") 
	{
        delta_x = -1;
    }
    else if (s == "lu") 
	{
        sprite.setTexture(tex_45);
        flame315.setPosition(sprite.getPosition().x + 45 , sprite.getPosition().y + 47);
        delta_x = -1;
        delta_y = -1;
    }
    else if (s == "rd") 
	{
        sprite.setTexture(tex_45);
        delta_x = 1;
        delta_y = 1;
    }
    else if (s == "ru") 
	{
        sprite.setTexture(tex45);
        flame45.setPosition(sprite.getPosition().x -10  , sprite.getPosition().y + 45);
        delta_x = 1;
        delta_y = -1;
    }
    else if (s == "ld") 
	{
        sprite.setTexture(tex45);
        delta_x = -1;
        delta_y = 1;
    }

    delta_x *= speed;
    delta_y *= speed;

    sprite.move(delta_x, delta_y);




	//-------------------Wrap Around---------------//

	float sprite_width = sprite.getGlobalBounds().width;
	float sprite_height = sprite.getGlobalBounds().height;

	if (sprite.getPosition().x  + sprite_width < 0)
        sprite.setPosition(780,sprite.getPosition().y);

    else if (sprite.getPosition().x - sprite_width  > 780)
        sprite.setPosition(0,sprite.getPosition().y);

    if (sprite.getPosition().y + sprite_height < 0)
        sprite.setPosition(sprite.getPosition().x,780);

    else if (sprite.getPosition().y - sprite_height > 780)
        sprite.setPosition(sprite.getPosition().x,0);

    //----------------------------------------------//


}


};
