#ifndef BOMB_H_
#define BOMB_H_
#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include <cmath>
using namespace sf;

class Bomb 
{
public:
    Texture tex ;
    Sprite sprite;
    float speed;
    
    Bomb(std::string png_path)
    {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        speed = 0.12f;
    }

    void update_bomb()
    {
        if(sprite.getPosition().x < 0 || sprite.getPosition().y > 780 || sprite.getPosition().x > 780)
        sprite.setPosition(1000,1000);
        
        else
        sprite.move(0,speed);
    }
    
};
#endif
