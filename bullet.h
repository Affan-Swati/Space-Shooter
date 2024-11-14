#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include <cmath>
using namespace sf;

class Bullet 
{
public:
    Texture tex , tex_right , tex_left , fire_tex;
    Sprite sprite , sprite_45 , sprite_135;
    bool vertical , right_tilt , left_tilt , fire_ball = false;

    Bullet()
    {
        tex.loadFromFile("img/PNG/Lasers/laserGreen11.png");
        tex_right.loadFromFile("img/PNG/Lasers/laserGreen11_45.png");
        tex_right.loadFromFile("img/PNG/Lasers/laserGreen11_-45.png");
        fire_tex.loadFromFile("img/PNG/Lasers/laserRed01.png");
        sprite.setTexture(tex);
        sprite_45.setTexture(tex_right);
        sprite_135.setTexture(tex_left);
        sprite.setPosition(1000,1000);
        sprite.setScale(1,0.5);
        sprite_45.setPosition(1000,1000);
        sprite_45.setScale(1,0.5);
        sprite_135.setPosition(1000,1000);
        sprite_135.setScale(1,0.5);

    }

    Bullet(bool u , bool d , bool l , bool r , float X , float Y)
    {

        tex.loadFromFile("img/PNG/Lasers/laserGreen11.png");
        sprite.setTexture(tex);
        sprite.setScale(1,0.5);

        if( (u && r) || (d && l))
        {
            vertical = left_tilt = false;
            right_tilt = true;
            sprite.setPosition(X + 80 , Y - 40);
            rotate_bullet (45 , *this);
        }

        else if( (u && l) || (d && r))
        {
            vertical = right_tilt = false;
            left_tilt = true;
            rotate_bullet(45 , *this);
            sprite.setPosition(X - 40 , Y - 40);
        }

        else 
        {
            left_tilt = right_tilt = false;
            sprite.setPosition(X + 80 , Y - 40);
            vertical = true;
        }

        

    }

    void rotate_bullet(float degree , Bullet& bullet)
    {
        bullet.sprite.setRotation(degree);
    }

    Bullet& operator=(Bullet& other)
    {
        if(other.vertical)
        {
            sprite.setRotation(0);
            vertical = true;
            right_tilt = left_tilt = false;
        }
        else if(other.right_tilt)
        {
            rotate_bullet(45, *this);
            right_tilt = true;
            left_tilt = vertical = false;
        }
        else if(other.left_tilt)
        {
            rotate_bullet(-45, *this);
            left_tilt = true;
            right_tilt = vertical = false;
        }

        if(other.fire_ball)
        {
            fire_ball = true;
            sprite.setTexture(fire_tex);
        }

        sprite.setRotation(other.sprite.getRotation());
        sprite.setPosition(other.sprite.getPosition().x , other.sprite.getPosition().y);

        return *this;
    }

    void update_bullet()
    {
        if(sprite.getPosition().y < 0 || sprite.getPosition().x < 0 || sprite.getPosition().x > 780 )
        {
            sprite.setPosition(1000,1000);
        }

        else
        {
            if(vertical)
            sprite.move(0,-0.2);

            else if(right_tilt)
            sprite.move(0.2,-0.2);

            else if(left_tilt)
            sprite.move(-0.2,-0.2);
        }

    }
    
};

