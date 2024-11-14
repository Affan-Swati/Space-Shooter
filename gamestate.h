#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>

using namespace std;
using namespace sf;
struct GameState 
{
    float playerX;
    float playerY;
    int life;
    int score;
    int level;
    int phase;
    float monster_delay;
    float dragon_delay;
	float monster_time;
    float dragon_time;
    string name;
    string badge;
};
#endif