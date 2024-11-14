
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "player.h"
#include "alpha.h"
#include "beta.h"
#include "gamma.h"
#include "monster.h"
#include "dragon.h"
#include "lives.h"
#include "danger.h"
#include "fire.h"
#include "powerup.h"
#include "meteor.h"
#include "coin.h"
#include <iostream>
#include <cmath>
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;
using namespace std;

class Game
{
	public:

	Sprite background; //Game background sprite
	Texture bg_texture , health;
	Player* p; //player 
	Coin *c;
	Music bullet_sound , monster_theme;
	Music bg_music , button , pop;
	Font font;
	Text text , text2 ,text3 , invincible , danger_sign , fireball , coin;

	Texture one ,two ,three , four , five , six , phs , lvl;
	Sprite LVL , PHS;
	Meteor *M1, *M2 , *M3 , *M4;


	Sprite Gold , Silver , Bronze , Cn ; // badges to be displayed , also coin
	Texture gold , silver , bronze , cn; // for badges
    
	Invaders *alpha;
	Invaders *beta;
	Invaders *gamma;
	Enemy *monster;
	Enemy *dragon;
	Addon *live;
	Addon *danger;
	Addon *fire ;
	Addon *powerup;
	

	Sprite sp;
	Texture t;
	Sprite Pause , Resume , Reset , EndGame ,Instructions , Instructions_;
	Texture pause , resume , reset , endgame , instructions , instructions_;
	bool tex_loaded = false;
	bool updateinvaders  = false;

	 float alpha_bomb_delay = 7;
	 float beta_bomb_delay = 5;
	 float gamma_bomb_delay = 4;
	 int level = 1;
	int phase = 1;
	 int alpha_count , beta_count , gamma_count = 0; // increments decrements in a phase
	 int alpha_alive , beta_alive , gamma_alive = 0; // remains constant , identifies the number of sprites created in a certain phase
	 float x , y  = 1000; // coordinates passed by ref in invader detect collision to determine where to draw the black hole

	Game()
	{
		p=new Player("img/player_ship.png");

		//---------METOR FALLING ANIMATIONS IN BACKGROUND ---------------//
		M1 = new Meteor("img/PNG/Meteors/meteorGrey_big1.png" , 0.6f );
		M2 = new Meteor("img/PNG/Meteors/meteorGrey_med1.png" , 0.7f );
		M3 = new Meteor("img/PNG/Meteors/meteorGrey_tiny1.png" , 0.8f );
		M4 = new Meteor("img/PNG/Meteors/meteorGrey_tiny2.png" , 0.9f );
		
		//-----------------ALPHA BETA & GAMMA INVADERS-------------------//
		alpha = new Alpha;
		beta = new Beta;
		gamma = new Gamma;

		//-----------------------MONSTER & DRAGON-------------------------//
		monster = new Monster;
		dragon = new Dragon;

		//----------------------------ADDONS ------------------------------//
		live = new Lives;
		danger = new Danger;
		fire = new Fire;
		powerup = new Powerup;
		c = new Coin;

		//---------------------LOADING OF TEXTURES AND MUSIC--------------//
		bg_texture.loadFromFile("img/cartoon_galaxy.jpg");
		pause.loadFromFile("img/menu/pause.png");
		resume.loadFromFile("img/menu/resume.png");
		reset.loadFromFile("img/menu/reset.png");
		endgame.loadFromFile("img/menu/pause_endgame.png");
		instructions.loadFromFile("img/menu/pause_instructions.png");
		instructions_.loadFromFile("img/menu/instruction_.png");
		t.loadFromFile("img/PNG/black_hole.png");
		bullet_sound.openFromFile("sounds/laser.wav");
		monster_theme.openFromFile("sounds/Monster.wav");
		bg_music.openFromFile("sounds/background2.wav");
		button.openFromFile("sounds/button.wav");
		pop.openFromFile("sounds/pop.wav");
		health.loadFromFile("img/PNG/health.png");
		one.loadFromFile("img/animation/one.png");
		two.loadFromFile("img/animation/two.png");
		three.loadFromFile("img/animation/three.png");
		four.loadFromFile("img/animation/four.png");
		five.loadFromFile("img/animation/five.png");
		six.loadFromFile("img/animation/six.png");
		lvl.loadFromFile("img/animation/level.png");
		phs.loadFromFile("img/animation/phase.png");
		gold.loadFromFile("img/PNG/badges/gold.png");
		silver.loadFromFile("img/PNG/badges/silver.png");
		bronze.loadFromFile("img/PNG/badges/bronze.png");
		cn.loadFromFile("img/PNG/Power-ups/coin.png");


		LVL.setTexture(lvl);
		PHS.setTexture(phs);
		Gold.setTexture(gold);
		Silver.setTexture(silver);
		Bronze.setTexture(bronze);
		Cn.setTexture(cn);

		font.loadFromFile("3D.ttf");
		text.setFont(font);
		text.setFillColor(Color(0, 191, 255)); 
		text.setOutlineColor(Color(175, 64, 175));
		text.setOutlineThickness(2);
		text.setPosition(600, 5);
		text.setCharacterSize(28);
		text2.setFont(font);
		text2.setFillColor(Color(0, 191, 255)); 
		text2.setOutlineColor(Color(175, 64, 175));
		text2.setOutlineThickness(2);
		text2.setPosition(600, 30);
		text2.setCharacterSize(28);
		text3.setFont(font);
		text3.setFillColor(Color(0, 191, 255)); 
		text3.setOutlineColor(Color(175, 64, 175));
		text3.setOutlineThickness(2);
		text3.setPosition(600, 55);
		text3.setCharacterSize(28);
		invincible.setFont(font);
		invincible.setFillColor(Color::Red);
		invincible.setPosition(150, 700);
		invincible.setCharacterSize(28);
		danger_sign.setFont(font);
		danger_sign.setFillColor(Color::Red);
		danger_sign.setPosition(150, 700);
		danger_sign.setCharacterSize(28);
		fireball.setFont(font);
		fireball.setFillColor(Color::Red);
		fireball.setPosition(220, 700);
		fireball.setCharacterSize(28);
		Gold.setPosition(355,5);
		Silver.setPosition(355,5);
		Bronze.setPosition(355,5);
		coin.setFont(font);
		coin.setFillColor(Color(0, 191, 255)); 
		coin.setOutlineColor(Color(175, 64, 175));
		coin.setOutlineThickness(2);
		coin.setPosition(35,735);
		coin.setCharacterSize(28);
		Cn.setPosition(3,740);

		
	
		button.setVolume(150.f);
		pop.setVolume(50.0f);
		Pause.setTexture(pause);
		Resume.setTexture(resume);
		Reset.setTexture(reset);
		EndGame.setTexture(endgame);
		Instructions.setTexture(instructions);
		Instructions_.setTexture(instructions_);
		Pause.setScale(0.65,0.6);
		Resume.setScale(0.65,0.6);
		Reset.setScale(0.65,0.6);
		EndGame.setScale(0.65,0.6);
		Instructions.setScale(0.65,0.6);
		Instructions_.setScale(0.55,0.58);
        bg_music.setVolume(50.f);
		monster_theme.setVolume(80.f);
		bullet_sound.setVolume(40.f);
		background.setTexture(bg_texture);
		background.setScale(0.5, 0.5);
		Gold.setScale(0.15,0.15);
		Silver.setScale(0.15,0.15);
		Bronze.setScale(0.15,0.15);
		Cn.setScale(0.01,0.01);

	}
	void start_game(RenderWindow& window , string &name , int &score , string& bg)
	{
	    srand(time(0));

		window.setTitle("OOP-Project, Spring-2023");
	    //RenderWindow window(VideoMode(780, 780), title);
	    Clock clock;

	    int life = 3;
	    float timer=0;
		score = 0;
		

		float alpha_bomb_time = 0;
		float beta_bomb_time = 0;
		float gamma_bomb_time = 0;
	    
		bool INSTRUCTIONS = false;
		bool paused = false;
	    bool shoot_cooldown = false;
	    float previous_bullet_time = 1000000; // will store the time when last bullet was fired
		float previous_monster_time = 100000;
		float lightning_draw_time = -100000;
		float monster_remove_time = -10000;
		float life_decrement_cooldown = 100000; // for monster laser spam life decrementer

	   
	    bool rectangle_formation = true;
	    bool triangle_formation = true;
	    bool cross_formation = true;
		bool diamond_formation = true;
	    bool heart_formation = true;
	    bool circle_formation = true;

		bool rectangle_filled_formation = true;
	    bool triangle_filled_formation = true;
	    bool cross_filled_formation = true;
		bool diamond_filled_formation = true;
	    bool heart_filled_formation = true;
	    bool circle_filled_formation = true;

		bool l1p1 , l1p2 , l1p3 , l2p1 , l2p2 , l2p3 , l3p1 , l3p2 , l3p3 , l3p4 , l3p5 , l3p6;
		l1p1 = l1p2 = l1p3 = l2p1 = l2p2=  l2p3 = l3p1 = l3p2 = l3p3 = l3p4 = l3p5 = l3p6 = false;
		

		bool invaders_cleared = false;
		bool monster_colided = false;
		bool monster_active = false;
		bool monster_survived = false;
		bool dragon_active = false;
		bool fire_powerup = false;
		bool powerup_active = false;
		float fire_powerup_time = -10000;
		float powerup_time = 100000;
		float shake_time = 10000; 
		bool shake_cooldown = false;
		bool dragon_survived = false;

	    bool invader_collision = false;
	    bool player_collision = false;

		float time_explosion = 100000;
		float player_destroy_time = 1000;
	    float player_lock_time = 1000;
		float dragon_duration = -100000000000;

		float X_monster;
	  	float danger_warning = -1000000;

	   float monster_spawn_time = 60 + rand()% 40;
	   float monster_delay = monster_spawn_time;

	   float dragon_spawn_time = monster_spawn_time + 45 + rand()%10;
	   float dragon_delay = dragon_spawn_time;

	   float live_power_delay = 20 + rand()%30; 

	   float previous_live_timer = live_power_delay;

	   float danger_power_delay =  15 + rand()%10;

	   float previous_danger_timer = danger_power_delay;

	   float fireball_power_delay =  25 + rand()%20;
	   
	   float previous_fireball_timer = fireball_power_delay;

	   float powerup_delay =  20 + rand()% 40;
	   
	   float previous_powerup_timer = powerup_delay;

	   float previous_coin_timer = 25 + rand()%25;

	   float coin_delay = previous_coin_timer;
	   int coin_count = 0;
	   float invincible_timer = 100000;
	   bool invincibility = false;

	  // std::cout<<"monster spawn time: "<<monster_spawn_time<<std::endl;
	   //std::cout<<"dragon spawn time: "<<dragon_spawn_time<<std::endl;
	  // dragon_spawn_time = monster_spawn_time =1000000;

		starting_animation(window);
		
	    while (window.isOpen() && life >=1 )
	    {
			float time = clock.getElapsedTime().asSeconds(); 
			clock.restart();
			timer += time;  
			Event e;
			while (window.pollEvent(e))
			{  
				if (e.type == Event::Closed) // If cross/close is clicked/pressed
				{
					window.close(); //close the game          
					return;              
				}    
			}
			
			bool right_pressed =  Keyboard::isKeyPressed(Keyboard::Right);
			bool left_pressed  = Keyboard::isKeyPressed(Keyboard::Left);
			bool up_pressed = Keyboard::isKeyPressed(Keyboard::Up);
			bool down_pressed = Keyboard::isKeyPressed(Keyboard::Down);
			bool space_bar_pressed = Keyboard::isKeyPressed(Keyboard::Space);
			
				if (left_pressed && up_pressed) //If left key and up key is pressed
				p->move("lu");   
			
				else if (right_pressed && up_pressed) //If right key and up key is pressed
				p->move("ru");
			
				else if (left_pressed && down_pressed) //If left key and down key is pressed
				p->move("ld");
				
				else if (right_pressed && down_pressed) //If right key and down key is pressed
				p->move("rd");
			
				else if (left_pressed) //If left key is pressed
				p->move("l");    // Player will move to left
				
				else if (right_pressed) // If right key is pressed
				p->move("r");  //player will move to right
				
				else if (up_pressed) //If up key is pressed
				p->move("u");    //player will move upwards
				
				else if (down_pressed) // If down key is pressed
				p->move("d");  //player will move downwards
			
			
			window.clear(Color::Black); //clears the screen
			window.draw(background);  // setting background

			//----------Drawing meteor animation on the screen----------//

			if(!M1->active)
			{
				M1->launch();
			} 

			if(!M2->active)
			{
				M2->launch();
			}

			if(!M3->active)
			{
				M3->launch();
			}

			if(!M4->active)
			{
				M4->launch();
			}

			M1->move();
			M2->move();
			M3->move();
			M4->move();

			window.draw(M1->sprite);
			window.draw(M2->sprite);
			window.draw(M3->sprite);
			window.draw(M4->sprite);
			

			//---------------------------------------------------------//
			
			window.draw(p->sprite);   // setting player on screen
			
			
			////////////////////////////////////////////////
			/////  Call your functions here            ////
			
			//------------------pause_menu--------------------------//
			if(Keyboard::isKeyPressed(Keyboard::P))
			{
				button.play();
				paused = true;
				Clock clk;
      		    float  time_pause =0;
				int counter = 0;
					while (window.pollEvent(e))
					{  
						if (e.type == Event::Closed) // If cross/close is clicked/pressed
						{
							window.close(); //close the game           
						}    
					}  

				while(paused)
				{
					//std::cout<<"aray wah\n";
					if (clk.getElapsedTime().asSeconds() - time_pause >=0.15 &&  Keyboard::isKeyPressed(Keyboard::Up))
        			{
						button.stop();
						button.play();
						if(counter == 1)
						counter = 4;

						else
							counter--;

						time_pause = clk.getElapsedTime().asSeconds();
          			}

					else if (clk.getElapsedTime().asSeconds() - time_pause >=0.15 && Keyboard::isKeyPressed(Keyboard::Down))
					{
						button.stop();
						button.play();

							if(counter == 4)
							counter = 1;

							else
								counter++;
							
							time_pause = clk.getElapsedTime().asSeconds();
					}

					if(Keyboard::isKeyPressed(Keyboard::Enter))
					{
						button.stop();
						button.play();
						while (window.pollEvent(e))
						{  
							if (e.type == Event::Closed) // If cross/close is clicked/pressed
							{
								window.close(); //close the game           
							}    
						}  
						if(counter == 1)
						{
							paused = false;
							break;
						}

						else if(counter == 2)
						{
							INSTRUCTIONS = true;

							while(INSTRUCTIONS)
							{
								while (window.pollEvent(e))
								{  
									if (e.type == Event::Closed) // If cross/close is clicked/pressed
									{
										window.close(); //close the game           
									}    
								}  

								while (window.pollEvent(e))
								{  
									if (e.type == Event::Closed) // If cross/close is clicked/pressed
									window.close(); //close the game                        	    
								}
							if(Keyboard::isKeyPressed(Keyboard::Escape))
							{
								button.stop();
								button.play();
								INSTRUCTIONS = false;
							}
								
								window.draw(Instructions_);
								window.display();
							}

						}

						else if(counter == 3)
						{
							bg_music.stop();
							monster_theme.stop();
							Game g1;
							return g1.start_game(window,name,score,bg);
							

						}

						else if(counter == 4)
						{
							bg_music.stop();
							monster_theme.stop();
							return exit_animation(window,score,"e");
						}
						

					}

					if(counter == 0)
					{
							window.draw(Pause);
					}

					else if(counter == 1)
						{
							window.draw(Resume);

						}

					else if(counter == 2)
					{
							window.draw(Instructions);

					}

					else if(counter == 3)
					{
							window.draw(Reset);

					}

					else if(counter == 4)
					{
							window.draw(EndGame);
					}

					window.display();

			}
			}
			
			//-------------------------------------------------------//

			//----------------Checking for jett flame---------------//
			if(up_pressed)
			{
				if(right_pressed)
				{
					window.draw(p->flame45);
				}

				else if(left_pressed)
				{
					window.draw(p->flame315);
				}
				else
				{
					window.draw(p->flame);
				}
			}

			//------------------------------------------------------//

			//----------------------------------------------------//
			//---------------Shaking Invaders-------------------------//

			if(timer - shake_time > 0.5)
			{
				shake_cooldown = false;
			}

			if(updateinvaders && !shake_cooldown)
			{
				shake_invaders(window);
				shake_cooldown = true;
				shake_time = timer;
			}
			//--------------------------------------------------------//

			//------------Displaying Score/Name/Level---------------------------//
				text.setString("Score: " + std::to_string(score));
				text2.setString("Level: " + std::to_string(level));
				text3.setString(name);
				coin.setString(std::to_string(coin_count));

				if(bg != "")
				{
					if(bg == "Gold")
					window.draw(Gold);

					else if (bg == "Silver")
					window.draw(Silver);

					else if (bg == "Bronze")
					window.draw(Bronze);
				}

				window.draw(coin);
				window.draw (Cn);
				window.draw(text);
				window.draw(text2);
				window.draw(text3);
				

			//-----------------------------------------------------------------//

			//--------------DISPLAYS HEALTH HEARTS IN TOP LEFT CORNER-----------//
			display_healths(window , life);

			//-------------------Managing the player's ship bullets fired-------------------//
			if(timer - previous_bullet_time >= 0.7 ) //after a delay of 0.7 sec the shoot_cooldown will turn false
				shoot_cooldown = false;
			
			if(!shoot_cooldown && (space_bar_pressed || p->Powerup) && !monster_active && !dragon_active)
			{
				bullet_sound.stop();
			 	bullet_sound.play();
				p->fire(up_pressed , down_pressed , left_pressed , right_pressed);
				shoot_cooldown = true;
				previous_bullet_time = timer;
				
			}
			
			if( p-> bullets_count )
			{
				p->update_fire();
				
			}
			//--------------------------------------------------------------------------------//
		

			//----------------- Managing invader formations------------------------------------//
		
			if (level == 1 && phase == 1 && triangle_formation && !monster_active && !dragon_active )
			{
					call_triangle_formation(window);
					p->sprite.setPosition(340,700);
					triangle_formation = false;
					alpha_bomb_time = 3;
					beta_bomb_time = 3;
					gamma_bomb_time = 3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ( (level == 1 && phase == 2 && rectangle_formation && !monster_active && !dragon_active)) 
			{	
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_rectangle_formation(window);
					p->sprite.setPosition(340,700);
					rectangle_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 1 && phase == 3 && cross_formation&& !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_cross_formation(window);
					p->sprite.setPosition(340,700);
					cross_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 2 && phase == 1 && diamond_formation&& !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_diamond_formation(window);
					p->sprite.setPosition(340,700);
					diamond_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 2 && phase == 2 && heart_formation&& !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_heart_formation(window);
					p->sprite.setPosition(340,700);
					heart_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 2 && phase == 3 && circle_formation&& !monster_active && !dragon_active) )
			{	
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_circle_formation(window);
					p->sprite.setPosition(340,700);
					circle_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 3 && phase == 2 && triangle_filled_formation && !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_triangle_filled_formation(window);
					p->sprite.setPosition(340,700);
					triangle_filled_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 3 && phase == 1 && rectangle_filled_formation&& !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_rectangle_filled_formation(window);
					p->sprite.setPosition(340,700);
					rectangle_filled_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 3 && phase == 3 && cross_filled_formation&& !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_cross_filled_formation(window);
					p->sprite.setPosition(340,700);
					cross_filled_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 3 && phase == 4 && diamond_filled_formation&& !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_diamond_filled_formation(window);
					p->sprite.setPosition(340,700);
					diamond_filled_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 3 && phase == 5 && heart_filled_formation && !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_heart_filled_formation(window);
					p->sprite.setPosition(340,700);
					heart_filled_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}

			else if ((level == 3 && phase == 6 && circle_filled_formation && !monster_active && !dragon_active))
			{
					if(p->bullets_count)
					delete [] p->bullets;
					p->bullets_count = p->addon_count = 0;
					p->fire_ball = false;
					phase_change_animation(window);
					call_circle_filled_formation(window);
					p->sprite.setPosition(340,700);
					circle_filled_formation = false;
					alpha_bomb_time = timer + 3;
					beta_bomb_time = timer + 3;
					gamma_bomb_time = timer +3;
					alpha_alive = alpha_count;
					beta_alive = beta_count;
					gamma_alive = gamma_count;
					updateinvaders = true;
			}
	

			//--------------------------------Levels and Phase Management---------------------//S

			if(alpha_count == 0 && beta_count == 0 && gamma_count == 0 && !monster_active && !dragon_active)
			{
				
				if(level == 1 || level == 2)
				{
					if(phase < 3)
					{
						phase++;
					}

					else if(phase == 3)
					{
						level++;
						phase = 1;
					}
				}

				else
				{
					phase++;
				}

				if(level == 1)
				{	
					if(phase == 1)
					l1p1 = true;

					else if(phase == 2)
					l1p2 = true;

					else if(phase == 3)
					l1p3 = true;
				}

				else if(level == 2)
				{
					if(phase == 1)
					l2p1 = true;

					else if(phase == 2)
					l2p2 = true;

					else if(phase == 3)
					l2p3 = true;

				}

				else if(level == 3)
				{
					
					if(phase == 1)
					l3p1 = true;

					else if(phase == 2)
					l3p2 = true;

					else if(phase == 3)
					l3p3 = true;

					else if(phase == 4)
					l3p4 = true;

					else if(phase == 5)
					l3p5 = true;

					else if(phase == 6)
					l3p6 = true;

				}
			}
			//-------------------------------------------------------------------------------//



			//-----------------------------Dragon's Implementation-------------------------//



				if(timer >= dragon_spawn_time && !dragon_active &&!monster_active )
				{
					//cout<<"DRAGON CALLED\n";
					bg_music.pause();
					monster_theme.play();
					monster_theme.setLoop(true);	
					dragon_active = true;
					clear_all_invaders();
					dragon_animation(window);
					dragon_duration = timer;
					

					if(level == 1)
				{
					if ( phase == 1)
					triangle_formation = true;

					else if( phase == 2)
					rectangle_formation = true;

					else if(phase == 3)
					cross_formation = true;
				}

					else if(level == 2)
				{
					if ( phase == 1)
					diamond_formation = true;

					else if( phase == 2)
					heart_formation = true;

					else if(phase == 3)
					circle_formation = true;

				}

					else if(level == 3)
				{
					if ( phase == 1)
					rectangle_filled_formation = true;

					else if( phase == 2)
					triangle_filled_formation = true;

					else if(phase == 3)
					cross_filled_formation = true;

					else if( phase == 4)
					diamond_filled_formation = true;

					else if(phase == 5)
					heart_filled_formation = true;

					else if( phase == 6)
					circle_filled_formation = true;

				}
				}

				if(timer - dragon_spawn_time > 5 && dragon_survived)
				{
					dragon_spawn_time = timer + dragon_delay;
					dragon->sprite.setPosition(1000,1000);
					dragon->Blaze.setPosition(1000,1000);
					monster_theme.stop();
					monster_theme.setLoop(false);
					bg_music.play();
					bg_music.setLoop(true);	
					dragon_survived = false;
					dragon_active = false;
					score+=50;
					//cout<<"SCORE INCREMENETED\n";
				}


				if(timer - dragon_duration <= 6)
				{
					string direct = "";
					dragon_survived = true;
					if(timer - dragon_duration >= 2)
					{
						if(p->sprite.getPosition().x > 200 && p->sprite.getPosition().x < 450)
						{
							dragon->setDirection("c");
							direct = "c";
						}

						else if(p->sprite.getPosition().x > 0 && p->sprite.getPosition().x <= 200)
						{
							dragon->setDirection("l");
							direct = "l";
						}

						else if(p->sprite.getPosition().x >=  450 && p->sprite.getPosition().x <= 780)
						{
							dragon->setDirection("r");
							direct = "r";
						}

						dragon->fire();
						window.draw(dragon->Blaze);
					}

					window.draw(dragon->sprite);
					

					if(p->dragon_collision(direct))
					{

						if(direct == "c")
						p->sprite.setPosition(200,700);

						else
						p->sprite.setPosition(340,700);

						life_decrement_cooldown = timer;
					}
		
				
				}
				else
				{
					dragon_active = false;
				}






			

			//-----------------------------------------------------------------------------------//
		
		//----------------------------------- MONSTER CALL -------------------------------------------//	
			if(timer >= monster_spawn_time && !dragon_active &&!monster_active )
			{
				//cout<<"Monster called\n";
				
				monster_active = true;
				updateinvaders = false;
				bg_music.pause();
				monster_theme.play();
				monster_theme.setLoop(true);
				monster_animation(window);
				monster->sprite.setPosition(340,15);
				clear_all_invaders();
				previous_monster_time = timer;
				monster_remove_time = timer;
				invaders_cleared= true;

				if(level == 1)
				{
					if ( phase == 1)
					triangle_formation = true;

					else if( phase == 2)
					rectangle_formation = true;

					else if(phase == 3)
					cross_formation = true;
				}

				else if(level == 2)
				{
					if ( phase == 1)
					diamond_formation = true;

					else if( phase == 2)
					heart_formation = true;

					else if(phase == 3)
					circle_formation = true;

				}

				else if(level == 3)
				{
					if ( phase == 1)
					cross_filled_formation = true;

					else if( phase == 2)
					rectangle_filled_formation = true;

					else if(phase == 3)
					triangle_filled_formation = true;

					else if( phase == 4)
					diamond_filled_formation = true;

					else if(phase == 5)
					heart_filled_formation = true;

					else if( phase == 6)
					circle_filled_formation = true;

				}

			}

			if(timer > monster_spawn_time + 20 && monster_survived)
			{
				bg_music.play();
				bg_music.setLoop(true);
				score+=40;	
				invaders_cleared = false;
				monster_survived = false;
				monster_spawn_time = monster_delay + timer ;
				monster_theme.stop();
				monster_theme.setLoop(false);
				monster_active = false;
				monster->sprite.setPosition(1000,1000);
				monster->Lightning.setPosition(1000,1000);
			}

			if(timer - monster_remove_time <= 20)
			{
				if(monster_active)
				{
					monster_survived = true;
					window.draw(monster->sprite);
					monster->move();
					if(timer - previous_monster_time >= 4)
					{
						lightning_draw_time = timer;
						previous_monster_time = timer;
					}

					if (timer -  lightning_draw_time <= 2)
					{
						monster->fire();
						window.draw(monster->Lightning);

					}
					
					else
					{
						monster->Lightning.setPosition(1000,1000);
					}
					
				}
			}

			//---------------------------------------------------------------------------//
			
			//-----------------IF AY INVADER EXISTS ON SCREEN ONLY THEN UPDATE WILL BE CALLED------------//
			if(updateinvaders)
				update_invaders();

			
			//-------------------------------------------------------------------------------//

			//-------------------------------------ADDONS------------------------------------//

											//--LIVE ADDON--//	
				if(timer >=previous_live_timer && !live->active &&!danger->active &&!fire->active && !powerup->active)
				{
					live->launch();
					previous_live_timer = live_power_delay + timer;
				}

				if(live->active)
				{
					live->move();
					if(p->detect_collisions(live->sprite.getPosition().x ,live->sprite.getPosition().y , true ))
					{
						life++;
						live->sprite.setPosition(1000,1000);
						live->active = false;

					}

					window.draw(live->sprite);
				}

											//--DANGER ADDON--//
				if(timer >=previous_danger_timer && !danger->active &&!monster_active &&!dragon_active &&!live->active &&!fire->active && !powerup->active)
				{
					danger->launch();
					previous_danger_timer = danger_power_delay + timer;
				}

				if(timer - danger_warning <= 2)
				{
					danger_sign.setString("You Just Hit the Danger Sign!");
					window.draw(danger_sign);
				}

				if(danger->active)
				{
					danger->move(score);

					if(p->detect_collisions(danger->sprite.getPosition().x ,danger->sprite.getPosition().y , false ) && !p->Powerup && !invincibility)
					{
						danger_warning = timer;
						life--;
						danger->sprite.setPosition(1000,1000);
						danger->active = false;
						player_collision = true;

					}

					window.draw(danger->sprite);
				}

										//--FIREBALL ADDON--//
				if(timer >=previous_fireball_timer && !fire->active &&!monster_active &&!dragon_active &&!live->active &&!danger->active && !powerup->active)
				{
					fire->launch();
					previous_fireball_timer = fireball_power_delay + timer;
					fire->active = true;
				}

				if(timer - fire_powerup_time >= 3)
				{
					p->fire_ball = false;
					fire_powerup = false;
				}

				if(fire_powerup&& !monster_active && !dragon_active)
				{
					fireball.setString("FireBall Activated!");
					window.draw(fireball);
				}

				if(fire->active)
				{

					fire->move();
					if(p->detect_collisions(fire->sprite.getPosition().x ,fire->sprite.getPosition().y , true ))
					{
						fire->sprite.setPosition(1000,1000);
						fire->active = false;
						fire_powerup_time = timer;
						p->fire_ball = true;
						fire_powerup = true;
					}

					window.draw(fire->sprite);
				}
											//--POWERUP ADDON--//
				if(timer >=previous_powerup_timer && !powerup->active &&!monster_active &&!dragon_active &&!live->active &&!fire->active && !danger->active)
				{
					powerup->launch();
					previous_powerup_timer = powerup_delay + timer;
					powerup->active = true;
				}

				if(timer - powerup_time >= 5)
				{
					p->Powerup = false;
					delete [] p->bullets;
					p->bullets_count =0;
					powerup_time = 10000;
				}

				else if(p->Powerup)
				{
					invincible.setString("You are INVINCIBLE for " + std::to_string(int(5-(timer - powerup_time))) + "secs");
					window.draw(invincible);
				}

				if(powerup->active)
				{
					powerup->move();
					if(p->detect_collisions(powerup->sprite.getPosition().x ,powerup->sprite.getPosition().y , true ))
					{
						powerup->sprite.setPosition(1000,1000);
						powerup->active = false;
						powerup_time = timer;
						p->Powerup = true;
					}

					window.draw(powerup->sprite);
				}


											//-- COIN ADDON--//
				if(timer >=previous_coin_timer && !c->active &&!danger->active &&!fire->active && !powerup->active)
				{
					c->launch();
					previous_coin_timer = coin_delay + timer;
				}

				if(c->active)
				{
					c->move();
					if(p->detect_collisions(c->sprite.getPosition().x ,c->sprite.getPosition().y , true ))
					{
						coin_count++;
						score+=20;
						c->sprite.setPosition(1000,1000);
						c->sp2.setPosition(1000,1000);
						c->sp3.setPosition(1000,1000);
						c->sp4.setPosition(1000,1000);
						c->sp5.setPosition(1000,1000);
						c->sp6.setPosition(1000,1000);
						c->active = false;

					}

					if(c->one)
					{
						window.draw(c->sprite);
					}

					else if(c->two)
					{
						window.draw(c->sp2);
					}

					else if(c->three)
					{
						window.draw(c->sp3);
					}

					else if(c->four)
					{
						window.draw(c->sp4);
					}

					else if(c->five)
					{
						window.draw(c->sp5);
					}

					else if(c->six)
					{
						window.draw(c->sp6);
					}

				}

				if(coin_count == 3)
				{
					coin_count = 0;
					invincibility= true;
					invincible_timer = timer;
				}

				if(timer - invincible_timer >= 5 && invincibility )
				{
					invincibility = false;
				}

				else if(invincibility)
				{
					invincible.setString("You are invincible for "+ to_string(int(5 - (timer - invincible_timer))) + " secs");
					window.draw(invincible);
				}

			//---------------------------------------------------------------------------------//

			// ------------------------- DETECTTING PLAYER COLLISIONS--------------------------//

				//-- WITH INVADER'S SPRITES
				for(int i=0 ; i<alpha_count ; i++)
				{
					if(p->detect_collisions(alpha[i].sprite.getPosition().x , alpha[i].sprite.getPosition().y , false))
					{
						p->sprite.setPosition(340,700);
						life--;
					}
				}

				for(int i=0 ; i<beta_count ; i++)
				{
					if(p->detect_collisions(beta[i].sprite.getPosition().x , beta[i].sprite.getPosition().y , false))
					{
						p->sprite.setPosition(340,700);
						life--;
					}
				}

				for(int i=0 ; i<gamma_count ; i++)
				{
					if(p->detect_collisions(gamma[i].sprite.getPosition().x , gamma[i].sprite.getPosition().y , false))
					{
						p->sprite.setPosition(340,700);
						life--;
					}
				}
				//-------------------------------------------------------------------------------//


				//------------------------Bomb speeds update wrt levels------------------------//
				for(int i=0 ; i < alpha_count ; i++)
				{
					for(int j=0 ; j < alpha[i].num_bombs ; j++)
					{
						if(level == 2)
						{
							alpha[i].bombs[j].speed = 0.125f;
						}

						else if (level ==3)
						{
							alpha[i].bombs[j].speed = 0.15f;
						}
					}
				}

				for(int i=0 ; i < beta_count ; i++)
				{
					for(int j=0 ; j < beta[i].num_bombs ; j++)
					{
						if(level == 2)
						{
							beta[i].bombs[j].speed = 0.125f;
						}

						else if (level ==3)
						{
							beta[i].bombs[j].speed = 0.15f;
						}
					}
				}

				for(int i=0 ; i < gamma_count ; i++)
				{
					for(int j=0 ; j < gamma[i].num_bombs ; j++)
					{
						if(level == 2)
						{
							gamma[i].bombs[j].speed = 0.125f;
						}

						else if (level ==3)
						{
							gamma[i].bombs[j].speed = 0.15f;
						}
					}
				}

				if(level == 2)
				{
					alpha_bomb_delay = 6.5f;
					beta_bomb_delay = 4.5f;
					gamma_bomb_delay =  3.5f;
				}

				else if ( level == 3)
				{
					alpha_bomb_delay = 6.0f;
					beta_bomb_delay = 4.0f;
					gamma_bomb_delay =  3.0f;
				}

			//--------------------------------------------------------------//


			//--------------INVADERS BOMB DROPPING AND PLAYER COLLISIONS WITH BOMBS-------------//
			
								//--ALPHA--//
			for(int i=0 ; i < alpha_count ; i++)
			{
				bool reset_time = false;
				if(timer - alpha_bomb_time >= alpha_bomb_delay  )
				{
					alpha[i].bomb();
					reset_time = true;
				}
				
				alpha[i].update_bomb();

				for(int j=0 ; j < alpha[i].num_bombs ; j++)
				{
						window.draw(alpha[i].bombs[j].sprite);
						
					if(!p->Powerup && !invincibility)
					{
						if(p->detect_collisions(alpha[i].bombs[j].sprite.getPosition().x ,alpha[i].bombs[j].sprite.getPosition().y , false ))
						{
							life--;
							player_collision = true;
							alpha[i].bombs[j].sprite.setPosition(1000,1000);
							break;	
						}
					}
				}
					if(i == alpha_count - 1 && reset_time)
					alpha_bomb_time = timer;
			}
			

							//--BETA--//
			
				for(int i=0 ; i < beta_count ; i++)
				{
					bool reset_time = false;
			
				if(timer - beta_bomb_time >= beta_bomb_delay )
				{
					beta[i].bomb();
					reset_time = true;	
				}
				
				beta[i].update_bomb();

				for(int j=0 ; j < beta[i].num_bombs ; j++)
				{
						window.draw(beta[i].bombs[j].sprite);
						
					if(!p->Powerup && !invincibility)
					{
						if(p->detect_collisions(beta[i].bombs[j].sprite.getPosition().x ,beta[i].bombs[j].sprite.getPosition().y , false ))
						{
							life--;
							player_collision = true;
							beta[i].bombs[j].sprite.setPosition(1000,1000);
							break;	
						}
					}
				}
				
				if(i == beta_count - 1 && reset_time)
					beta_bomb_time = timer;
			}
									//--GAMMA--//
			
				
				for(int i=0 ; i < gamma_count ; i++)
				{
					bool reset_time = false;
					
				if(timer - gamma_bomb_time >= gamma_bomb_delay )
				{
					gamma[i].bomb();
					reset_time = true;
				}
				
				gamma[i].update_bomb();

					//std::cout<<gamma[i].num_bombs<< "\n";
				for(int j=0 ; j < gamma[i].num_bombs ; j++)
				{
						window.draw(gamma[i].bombs[j].sprite);
						
					if(!p->Powerup && !invincibility)
					{
						if(p->detect_collisions(gamma[i].bombs[j].sprite.getPosition().x ,gamma[i].bombs[j].sprite.getPosition().y , false))
						{
							life--;
							player_collision = true;
							//player_kill_clock.restart();
							gamma[i].bombs[j].sprite.setPosition(1000,1000);
							break;	
						}
					}
				}
				
					if(i == gamma_count - 1 && reset_time)
					gamma_bomb_time = timer;
				}
				
				if(monster->sprite.getPosition().x > p->sprite.getPosition().x)
				X_monster = 3000;

				else
				X_monster = 0;

				if(timer - life_decrement_cooldown >= 1.0f)
				{
					life--;
					life_decrement_cooldown = 1000;
				}

				if(!p->Powerup && !invincibility)
				{
					if(p->detect_collision(monster ->Lightning.getPosition().x + X_monster))
					{
						life_decrement_cooldown = timer;
						monster->Lightning.setScale(1,1.1);
						player_collision = true;
						monster_colided = true;
					}

					else
					{
						monster->Lightning.setScale(1,1.8);
					}
				}
				
	
			
				if(player_collision)
				{
					player_destroy_time = 0;
					
					if(!dragon_active)
					player_lock_time = 0;
				}
				
				
				if(player_destroy_time <= 0.3)
				{
					player_collision = false;
					player_destroy_time += time;
					

					if(monster_colided)
					{
						p->kill_sprite.setScale(0.3,0.3);
					}

					window.draw(p->kill_sprite);
				
				}
				
				else
				{
					p->sprite.setTexture(p->tex);
					
					p->sprite.setScale(0.75,0.75);
				
				}
				
				if(player_lock_time <= 0.75)
				{
					player_lock_time += time;
					p->black_color();
					p->sprite.setPosition(340,700);
					p->sprite.setScale(0.75,0.75);
				
				}
			//-----------------------------------------------------------------------------------//
			
			//---------------------------------DRAWING INVADER SPRITES---------------------------//
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			//----------------------------------------------------------------------------------//
			
			
			// ------------------------------ Drawing Player's Bullet sprites-------------------------//
			for(int i=0 ; i < p->bullets_count ; i++)
			{
				if(p->bullets[i].sprite.getPosition().y < 0 || p->bullets[i].sprite.getPosition().x < 0 || p->bullets[i].sprite.getPosition().x > 780  ) 
				continue;

				window.draw(p->bullets[i].sprite);
			}
			//---------------------------------------------------------------------------------------//
		
			//--------------------------- Detecting Invader's collisions----------------------------//
			for(int i=0 ; i< p->bullets_count ; i++)
			{
				invader_collision = check_invader_collision(p->bullets[i].sprite.getPosition().x , p->bullets[i].sprite.getPosition().y , x, y , score ,level );
				if(invader_collision)
				{
					pop.stop();
					pop.play();
					invader_collision = false;
					time_explosion = 0;
					sp.setTexture(t);
					sp.setPosition(x - 25  , y - 25 );
					sp.setScale(0.08,0.08);

					if(!p->fire_ball)
					p->bullets[i].sprite.setPosition(1000,1000);

				break;
				}
			}
			if(time_explosion <= 0.8)
			{
				window.draw(sp);
				time_explosion += time;
			}

			//------------------------------------------------------------------------------------------//

			window.display();  //Displying all the sprite
			

			if(level == 3 && phase == 7) // IF MAXIMUM LEVELS REACHED THE GAME ENDS
			{
				bg_music.stop();
				return exit_animation(window , score , "w");
			}
			

	    }
		bg_music.stop();
		return exit_animation(window , score , "l");
	
	}
	
	void starting_animation(RenderWindow &window)
	{
    const float countdownTime = 1.1f; 
    Clock clk;
    float t = 0.0f;
    Sprite Ready, Three, Two, One, Go;
    Texture ready, three, two, one, go;
	Music count_down , ready_sound;

	count_down.openFromFile("sounds/countdown.wav"); 
	ready_sound.openFromFile("sounds/ready.wav");
	count_down.setVolume(150.0f);
	ready_sound.setVolume(150.0f);

    ready.loadFromFile("img/PNG/getready.png");
    three.loadFromFile("img/PNG/3.png");
    two.loadFromFile("img/PNG/2.png");
    one.loadFromFile("img/PNG/1.png");
    go.loadFromFile("img/PNG/letsgo.png");

    Ready.setTexture(ready); Three.setTexture(three); Two.setTexture(two); One.setTexture(one); Go.setTexture(go);

    // set the initial position and scale of the sprites
    Ready.setPosition(340.0f, 340.0f);
    Three.setPosition(340.0f, 340.0f);
    Two.setPosition(340.0f, 340.0f);
    One.setPosition(340.0f, 340.0f);
    Go.setPosition(340.0f, 340.0f);

    // target scale of the sprites after the animation
    float targetScale = 0.5f;

	ready_sound.play();
    while (t <= countdownTime )
    {
        float currentScale = 2.0f - (t / countdownTime) * 1.5f;
        float currentPositionX = 240.0f - (currentScale - 0.5f) * Ready.getTextureRect().width / 2.0f;
        float currentPositionY = 340.0f - (currentScale - 0.5f) * Ready.getTextureRect().height / 2.0f;

        window.clear();
        window.draw(background);

        Ready.setPosition(currentPositionX, currentPositionY);
        Ready.setScale(currentScale, currentScale);
        window.draw(Ready);
        window.display();

        t = clk.getElapsedTime().asSeconds();
	}
	count_down.setVolume(150.0f);
	count_down.play();
    t = 0.0f;
    while (t <= countdownTime)
    {
        float currentScale = 2.0f - (t / countdownTime) * 1.5f;
        float currentPositionX = 340.0f - (currentScale - 0.5f) * Three.getTextureRect().width / 2.0f;
        float currentPositionY = 340.0f - (currentScale - 0.5f) * Three.getTextureRect().height / 2.0f;

        window.clear();
        window.draw(background);

        Three.setPosition(currentPositionX, currentPositionY);
        Three.setScale(currentScale, currentScale);
        window.draw(Three);
        window.display();

        t = clk.getElapsedTime().asSeconds() - countdownTime;
    }

	t = 0.0f;
    while (t <= countdownTime)
    {
        float currentScale = 2.0f - (t / countdownTime) * 1.5f;
        float currentPositionX = 340.0f - (currentScale - 0.5f) * Three.getTextureRect().width / 2.0f;
        float currentPositionY = 340.0f - (currentScale - 0.5f) * Three.getTextureRect().height / 2.0f;

        window.clear();
        window.draw(background);

        Two.setPosition(currentPositionX, currentPositionY);
        Two.setScale(currentScale, currentScale);
        window.draw(Two);
        window.display();

        t = clk.getElapsedTime().asSeconds() -  (2 * countdownTime);
    }

	t = 0.0f;
    while (t <= countdownTime)
    {
        float currentScale = 2.0f - (t / countdownTime) * 1.5f;
        float currentPositionX = 450.0f - (currentScale - 0.5f) * Three.getTextureRect().width / 2.0f;
        float currentPositionY = 340.0f - (currentScale - 0.5f) * Three.getTextureRect().height / 2.0f;

        window.clear();
        window.draw(background);

        One.setPosition(currentPositionX, currentPositionY);
        One.setScale(currentScale, currentScale);
        window.draw(One);
        window.display();

        t = clk.getElapsedTime().asSeconds() -  (3 * countdownTime);
    }
	bg_music.play();
	bg_music.setLoop(true);
	t = 0.0f;
    while (t <= countdownTime - 0.1)
    {
        float currentScale = 2.0f - (t / countdownTime) * 1.5f;
        float currentPositionX = 220.0f - (currentScale - 0.5f) * Three.getTextureRect().width / 2.0f;
        float currentPositionY = 340.0f - (currentScale - 0.5f) * Three.getTextureRect().height / 2.0f;

        window.clear();
        window.draw(background);

        Go.setPosition(currentPositionX, currentPositionY);
        Go.setScale(currentScale, currentScale);
        window.draw(Go);
        window.display();

        t = clk.getElapsedTime().asSeconds() -  (4 * countdownTime);
    }
	count_down.stop();
}

	void phase_change_animation(RenderWindow &window)
	{
		
		float ax = 210.0f , bx = 590.0f;
		float ay = 530.0f, by = 290.0f;

		bool A ,B;
		A = B =false;

		Sprite M1 , M2;
		Texture m1,m2;

		m1.loadFromFile("img/dragon.png");
		m2.loadFromFile("img/dragon1.png");

		M1.setTexture(m1);
		M2.setTexture(m2);

		M1.setPosition(0,530);
		M2.setPosition(780,290);

		M1.setScale(1,1);
		M2.setScale(1,1);

		M1.setRotation(-90);
		M2.setRotation(90);


		Sprite bg;
		Texture bgtex;
		bgtex.loadFromFile("img/animation/animation_background.jpg");
		bg.setTexture(bgtex);
		bg.setScale(0.4,0.4);
	

		while(!(A && B))
		{
			if(std::round(M1.getPosition().x) == ax && std::round(M1.getPosition().y) == ay)
			{
				A = true;
			}

			else
			{
				if(M1.getPosition().x  <  ax)
				{
					M1.move(0.25,0);
				}

				else if( M1.getPosition().x > ax)
				{
					M1.move(-0.25,0);
				}

				if(M1.getPosition().y  <  ay)
				{
					M1.move(0,0.25);
				}

				else if( M1.getPosition().y > ay)
				{
					M1.move(0,-0.25);
				}
			}

			if(std::round(M2.getPosition().x )== bx && std::round(M2.getPosition().y) == by)
			{
				B = true;
			}

			else
			{
				if(M2.getPosition().x  <  bx)
				{
					M2.move(0.25,0);
				}

				else if( M2.getPosition().x > bx)
				{
					M2.move(-0.25,0);
				}

				if(M2.getPosition().y  <  by)
				{
					M2.move(0,0.25);
				}

				else if( M2.getPosition().y > by)
				{
					M2.move(0,-0.25);
				}
			}

			window.clear();
			window.draw(background);
			window.draw(M1);
			window.draw(M2);
			window.display();

		}

	Clock clock;
	Music explode;
	explode.openFromFile("sounds/explosion.wav");

	float x = 35 , y = 50;

	Texture explosionTexture;
	explosionTexture.loadFromFile("img/EXPLOSION.png");

	int frameWidth = explosionTexture.getSize().x / 8;
	int frameHeight = explosionTexture.getSize().y / 6;

	Sprite explosionSprite(explosionTexture);

	explosionSprite.setPosition(x, y);
	explosionSprite.setScale(2.5, 2.5);

	int currentFrame = 0;

	float frameRate = 0.04f;
	explode.stop();
	explode.play();

		while (currentFrame < 42) {
			window.clear();

			explosionSprite.setTextureRect(sf::IntRect((currentFrame % 6) * frameWidth, (currentFrame / 6) * frameHeight, frameWidth, frameHeight));

			window.draw(background);
			window.draw(explosionSprite);
			window.display();

			sf::Time elapsedTime = clock.getElapsedTime();
			if (elapsedTime.asSeconds() > frameRate) {
				currentFrame++;
				clock.restart();
			}
		}
		
		Sprite  level_no , phase_no;
		clock.restart();
		float t_time = clock.getElapsedTime().asSeconds();
		level_no.setPosition(610,100);
		phase_no.setPosition(610,400);
		bg.setScale(0.6,0.6);
		p->sprite.setPosition(340,500);
		p->sprite.setTexture(p->tex);

		while(clock.getElapsedTime().asSeconds() - t_time <= 0.75)
		{
			window.clear();
			window.draw(background);

			if(p->sprite.getPosition().y <= 720)
			{
				p->sprite.move(0,0.23);

				window.draw(p->sprite);
			}

			if(level == 1)
			{
				level_no.setTexture(one);
			}

			else if(level == 2)
			{
				level_no.setTexture(two);
			}

			else if(level == 3)
			{
				level_no.setTexture(three);

			}

			if(phase == 1)
			{
				phase_no.setTexture(one);
			}

			else if(phase == 2)
			{
				phase_no.setTexture(two);

			}

			else if(phase == 3)
			{
				phase_no.setTexture(three);

			}
			else if(phase == 4)
			{
				phase_no.setTexture(four);
			}

			else if(phase == 5)
			{
				phase_no.setTexture(five);

			}
			else if(phase == 6)
			{
				phase_no.setTexture(six);

			}	

			LVL.setPosition(15,100);
			PHS.setPosition(15,400);			
			window.draw(LVL);
			window.draw(PHS);
			window.draw(level_no);
			window.draw(phase_no);
			window.display();
		}




		float color = 255;
		p->sprite.setTexture(p->tex);

		while(color >= 0)
        {

            window.clear();

			LVL.setColor(Color(255,255,255,color));
			PHS.setColor(Color(255,255,255,color));
			level_no.setColor(Color(255,255,255,color));
			phase_no.setColor(Color(255,255,255,color));

			window.draw(background);
            window.draw(LVL);
			window.draw(PHS);
			window.draw(level_no);
			window.draw(phase_no);

            color -= 0.2;

            window.draw(p->sprite);
            window.display();
        }

		LVL.setColor(Color(255,255,255,255));
		PHS.setColor(Color(255,255,255,255));


}

	void call_rectangle_formation(RenderWindow &window)
	{
		updateinvaders = false;
		clear_all_invaders();

		float a0x = 340.0f, a1x = 580.0f,  a2x = 580.0f , a3x = 100.0f , a4x = 100.0f, b0x = 340.0f , b1x = 580.0f , b2x = 100.0f , g0x = 480.0f ,g1x = 200.0f , g2x = 200.0f ,g3x = 480.0f;
		float a0y = 250.0f, a1y = 250.0f, a2y = 100.0f , a3y = 250.0f , a4y  = 100.0f, b0y = 100.0f , b1y = 180.0f , b2y = 180.0f , g0y = 100.0f ,g1y = 100.0f , g2y = 250.0f , g3y = 250.0f;

		bool A0 ,A1 , A2 , A3 , A4 , B0 , B1 , B2 , G0 , G1  , G2 , G3;
		A0  = A1 = A2 = A3 = A4 =  B0 = B1 = B2 = G0 = G1 = G2 =  G3 = false;
	
		alpha = new Alpha [5];
		beta = new Beta [3];
		gamma = new Gamma [4];		
		
		alpha_count = 5;
		beta_count = 3;
		gamma_count = 4;

		/*alpha[0].sprite.setPosition(340,250);
		alpha[1].sprite.setPosition(480,250);
		
		beta[0].sprite.setPosition(340,100);
		beta[1].sprite.setPosition(480,180);
		beta[2].sprite.setPosition(200,180);
		
		gamma[0].sprite.setPosition(480,100);
		gamma[1].sprite.setPosition(200,100);
		gamma[2].sprite.setPosition(200,250);*/



		alpha[0].sprite.setPosition(0,780);
		alpha[1].sprite.setPosition(0,780);
		alpha[2].sprite.setPosition(0,780);
		alpha[3].sprite.setPosition(780,0);
		alpha[4].sprite.setPosition(780,0);
		
		beta[0].sprite.setPosition(0,780);
		beta[1].sprite.setPosition(0,780);
		beta[2].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(780,0);
		gamma[1].sprite.setPosition(780,0);
		gamma[2].sprite.setPosition(780,0);
		gamma[2].sprite.setPosition(0,780);

		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);

		while(!(A0 && A1 && A3 && A2 && A4 && B0 && B1 && B2 && G0 && G1 && G2 && G3))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}


			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}


			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}
		///////////////////////////////////////////////////////////////////////

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}
			window.draw(p->sprite);
			window.display();

		}
		p->sprite.setPosition(340,700);
	
	}
	
	void call_triangle_formation(RenderWindow &window )
	{
		updateinvaders = false;
		float a0x = 190.0f, a1x = 340.0f , a2x = 290.0f , a3x = 390.0f , a4x = 490.0f , b0x = 270.0f , b1x = 420.0f ,g0x = 480.0f ,g1x = 220.0f ;
		float a0y = 80.0f, a1y = 300.0f, a2y = 80.0f , a3y = 80.0f , a4y = 80.0f, b0y = 225.0f , b1y = 225.0f ,g0y = 150.0f ,g1y = 150.0f;

		bool A0 ,A1 , A2 , A3 ,A4, B0 , B1 , G0 , G1 ;
		A0  = A1 = A2 = A3 = A4 = B0 = B1 = G0 = G1 = false;

		alpha = new Alpha [5];
		beta = new Beta [2];
		gamma = new Gamma [2];
		
		alpha_count = 5;
		beta_count = 2;
		gamma_count = 2;
		
		alpha[0].sprite.setPosition(0,780);
		alpha[1].sprite.setPosition(0,780);
		alpha[2].sprite.setPosition(0,780);
		alpha[3].sprite.setPosition(780,0);
		alpha[4].sprite.setPosition(780,0);
				
		beta[0].sprite.setPosition(0,780);
		beta[1].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(780,0);
		gamma[1].sprite.setPosition(780,0);

		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);

		while(!(A0 && A1 && A2 && A3 && A4 && B0 && B1 && G0 && G1))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}

			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}


			////////////////////////////////////////////////////////////////////////////////////////

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}
		///////////////////////////////////////////////////////////////////////

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}
			window.draw(p->sprite);
			window.display();

		}
	
		
	}
	
	void call_cross_formation(RenderWindow &window)
	{
	
	updateinvaders = false;
	clear_all_invaders();

	float a0x = 340.0f, b0x = 255.0f , b1x = 410.0f , b2x = 410.0f , b3x  = 255.0f ,g0x = 490.0f ,g1x = 190.0f , g2x = 190.0f , g3x = 490.0f;
	float a0y = 200.0f, b0y = 240.0f , b1y = 150.0f , b2y = 240.0f , b3y = 150.0f ,g0y = 100.0f ,g1y = 295.0f , g2y = 100.0f , g3y = 295.0f;

	bool A0 , B0 , B1 , B2 , B3 , G0 , G1  , G2 ,G3;
	A0  =  B0 = B1 = B2 = B3 = G0 = G1 = G2 = G3 =false;
	
	
	alpha = new Alpha [1];
	beta = new Beta [4];
	gamma = new Gamma [4];
	
	alpha_count = 1;
	beta_count = 4;
	gamma_count = 4;
	
						
	/*			
	alpha[0].sprite.setPosition(sf::Vector2f(340,200)); // center
	
	beta[0].sprite.setPosition(sf::Vector2f(275,240)); // down left
	beta[1].sprite.setPosition(sf::Vector2f(390, 150)); // up right
	beta[2].sprite.setPosition(sf::Vector2f(390,240)); // down right
	beta[3].sprite.setPosition(sf::Vector2f(275, 150)); // up left
	
	gamma[0].sprite.setPosition(sf::Vector2f(450,110)); // up right
	gamma[1].sprite.setPosition(sf::Vector2f(230,285)); //  down left
	gamma[2].sprite.setPosition(sf::Vector2f(220,110)); // up left
	gamma[3].sprite.setPosition(sf::Vector2f(450,285));	// down right*/

	alpha[0].sprite.setPosition(0,780); // center
	
	beta[0].sprite.setPosition(0,780); // down left
	beta[1].sprite.setPosition(0,780); // up right
	beta[2].sprite.setPosition(0,780); // down right
	beta[3].sprite.setPosition(0,780); // up left
	
	gamma[0].sprite.setPosition(0,0); // up right
	gamma[1].sprite.setPosition(0,0); //  down left
	gamma[2].sprite.setPosition(0,0); // up left
	gamma[3].sprite.setPosition(0,0);	// down right*


	p->sprite.setPosition(340,700);
	p->sprite.setRotation(0);
		while(!(A0 && B0 && B1 && B2 && B3 && G0 && G1 && G2 && G3))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}


			////////////////////////////////////////////////////////////////////////////////////////

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}

			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}
		///////////////////////////////////////////////////////////////////////

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}

			window.draw(p->sprite);
			window.display();

		}



	p->sprite.setPosition(340,700);	
	}
	
	void call_circle_formation(RenderWindow &window)
	{
		clear_all_invaders();
		updateinvaders = false;
		float a0x = 340.0f, a1x = 340.0f , b0x = 250.0f , b1x = 250.0f , b2x = 430.0f, b3x = 430.0f, g0x = 480.0f ,g1x = 200.0f ;
		float a0y = 50.0f, a1y = 300.0f, b0y = 100.0f , b1y = 250.0f , b2y = 100.0f , b3y = 250.0f, g0y = 175.0f ,g1y = 175.0f;

		bool A0 ,A1  , B0 , B1 , B2 , B3 , G0 , G1 ;
		A0  = A1 = B2 = B3 = B0 = B1 = G0 = G1 = false;

		alpha = new Alpha [2];
		beta = new Beta [4];
		gamma = new Gamma [2];
		
		alpha_count = 2;
		beta_count = 4;
		gamma_count = 2;
		
		alpha[0].sprite.setPosition(0,780); //done center up
		alpha[1].sprite.setPosition(780,0);
				
		beta[0].sprite.setPosition(0,780); // 
		beta[1].sprite.setPosition(780,0);
		beta[2].sprite.setPosition(0,780);
		beta[3].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(0,780); //done  center down
		gamma[1].sprite.setPosition(780,0);

		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);

		while(!(A0 && A1 && B0 && B1 && B2 && B3 &&  G0 && G1 ))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}


			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			window.draw(p->sprite);
			window.display();
		}
	}

	void call_diamond_formation(RenderWindow &window)
	{
		clear_all_invaders();
		updateinvaders = false;
		float a0x = 340.0f, a1x = 340.0f , b0x = 240.0f , b1x = 240.0f , b2x = 440.0f, b3x = 440.0f, g0x = 530.0f ,g1x = 150.0f ;
		float a0y = 40.0f, a1y = 310.0f, b0y = 110.0f , b1y = 250.0f , b2y = 110.0f , b3y = 250.0f, g0y = 175.0f ,g1y = 175.0f;

		bool A0 ,A1  , B0 , B1 , B2 , B3 , G0 , G1 ;
		A0  = A1 = B2 = B3 = B0 = B1 = G0 = G1 = false;

		alpha = new Alpha [2];
		beta = new Beta [4];
		gamma = new Gamma [2];
		
		alpha_count = 2;
		beta_count = 4;
		gamma_count = 2;
		
		alpha[0].sprite.setPosition(0,780); //done center up
		alpha[1].sprite.setPosition(780,0);
				
		beta[0].sprite.setPosition(0,780); // 
		beta[1].sprite.setPosition(780,0);
		beta[2].sprite.setPosition(0,780);
		beta[3].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(0,780); //done  center down
		gamma[1].sprite.setPosition(780,0);


		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);
		while(!(A0 && A1 && B0 && B1 && B2 && B3 &&  G0 && G1 ))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}


			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}
			window.draw(p->sprite);
			window.display();
		}



	}

	void call_heart_formation(RenderWindow &window)
	{
		clear_all_invaders();
		updateinvaders = false;
		float a0x = 340.0f, a1x = 450.0f , a2x = 220.0f , b0x = 185.0f , b1x = 495.0f , b2x = 337.5f, g0x = 420.0f ,g1x = 260.0f  , g2x = 280.0f , g3x = 395.0f;
		float a0y = 110.0f, a1y = 175.0f, a2y = 175.0f, b0y = 100.0f , b1y = 100.0f , b2y = 295.0f , g0y = 50.0f ,g1y = 50.0f , g2y = 240.0f, g3y = 240.0f;

		bool A0 ,A1 , A2 , B0 , B1 , B2 , G0 , G1 ,G2 ,G3;
		A0  = A1 = A2 = B2 = B0 = B1 = G0 = G1 = G2 = G3 = false;

		alpha = new Alpha [3];
		beta = new Beta [3];
		gamma = new Gamma [4];
		
		alpha_count = 3;
		beta_count = 3;
		gamma_count = 4;
		
		alpha[0].sprite.setPosition(0,780);
		alpha[1].sprite.setPosition(780,0);
		alpha[2].sprite.setPosition(0,780);
				
		beta[0].sprite.setPosition(0,780);  
		beta[1].sprite.setPosition(780,0);
		beta[2].sprite.setPosition(0,780);
		
		gamma[0].sprite.setPosition(0,780); 
		gamma[1].sprite.setPosition(780,0);
		gamma[2].sprite.setPosition(0,780);
		gamma[3].sprite.setPosition(780,0);


		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);
		while(!(A0 && A1 && A2 && B0 && B1 && B2 &&  G0 && G1 && G2 && G3))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}

			window.draw(p->sprite);
			window.display();
		}


	}

	void call_triangle_filled_formation(RenderWindow &window)
	{
		clear_all_invaders();
		updateinvaders = false;
		float a0x = 190.0f, a1x = 340.0f , a2x = 290.0f , a3x = 390.0f , a4x = 490.0f , b0x = 270.0f , b1x = 420.0f ,b2x = 400.0f , b3x = 300.0f ,g0x = 480.0f ,g1x = 220.0f , g2x = 345.0f;
		float a0y = 80.0f, a1y = 300.0f, a2y = 80.0f , a3y = 80.0f , a4y = 80.0f, b0y = 225.0f , b1y = 225.0f , b2y = 150.0f , b3y = 150.0f ,g0y = 150.0f ,g1y = 150.0f , g2y = 225.0f;

		bool A0 ,A1 , A2 , A3 ,A4, B0 , B1 , B2 , B3 ,  G0 , G1 , G2;
		A0  = A1 = A2 = A3 = A4 = B0 = B1  = B2 = B3 = G0 = G1 = G2 =  false;

		alpha = new Alpha [5];
		beta = new Beta [4];
		gamma = new Gamma [3];
		
		alpha_count = 5;
		beta_count = 4;
		gamma_count = 3;
		
		alpha[0].sprite.setPosition(0,780);
		alpha[1].sprite.setPosition(0,780);
		alpha[2].sprite.setPosition(780,0);
		alpha[3].sprite.setPosition(780,0);
		alpha[4].sprite.setPosition(0,780);
				
		beta[0].sprite.setPosition(0,780);
		beta[1].sprite.setPosition(780,0);
		beta[2].sprite.setPosition(0,780);
		beta[3].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(780,0);
		gamma[1].sprite.setPosition(0,780);
		gamma[2].sprite.setPosition(780,0);

		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);

		while(!(A0 && A1 && A2 && A3 && A4 && B0 && B1 && B2 && B3 && G0 && G1 && G2))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}

			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}


			////////////////////////////////////////////////////////////////////////////////////////

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}

			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}
		///////////////////////////////////////////////////////////////////////

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}
			window.draw(p->sprite);
			window.display();

		}
		p->sprite.setPosition(340,700);


	}

	void call_rectangle_filled_formation(RenderWindow &window)
	{
		updateinvaders = false;
		clear_all_invaders();

		float a0x = 340.0f, a1x = 580.0f,  a2x = 580.0f , a3x = 100.0f , a4x = 100.0f, a5x = 480.0f , a6x = 200.0f, b0x = 340.0f , b1x = 580.0f , b2x = 100.0f , g0x = 480.0f ,g1x = 200.0f , g2x = 200.0f ,g3x = 480.0f , g4x = 340.0f;
		float a0y = 250.0f, a1y = 250.0f, a2y = 100.0f , a3y = 250.0f , a4y  = 100.0f, a5y = 180.0f , a6y = 180.0f ,b0y = 100.0f , b1y = 180.0f , b2y = 180.0f , g0y = 100.0f ,g1y = 100.0f , g2y = 250.0f , g3y = 250.0f , g4y = 180.0f;

		bool A0 ,A1 , A2 , A3 , A4 , A5 , A6 , B0 , B1 , B2 , G0 , G1  , G2 , G3 , G4;
		A0  = A1 = A2 = A3 = A4 =  B0 = B1 = B2 = G0 = G1 = G2 =  G3 = A5 = A6 = G4 = false;
	
		alpha = new Alpha [7];
		beta = new Beta [3];
		gamma = new Gamma [5];		
		
		alpha_count = 7;
		beta_count = 3;
		gamma_count = 5;

		alpha[0].sprite.setPosition(0,780);
		alpha[1].sprite.setPosition(0,780);
		alpha[2].sprite.setPosition(0,780);
		alpha[3].sprite.setPosition(780,0);
		alpha[4].sprite.setPosition(780,0);
		alpha[5].sprite.setPosition(0,780);
		alpha[6].sprite.setPosition(780,0);
		
		beta[0].sprite.setPosition(0,780);
		beta[1].sprite.setPosition(0,780);
		beta[2].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(780,0);
		gamma[1].sprite.setPosition(0,780);
		gamma[2].sprite.setPosition(780,0);
		gamma[3].sprite.setPosition(0,780);
		gamma[4].sprite.setPosition(780,0);

		while(!(A0 && A1 && A3 && A2 && A4 && A5 && A6 && B0 && B1 && B2 && G0 && G1 && G2 && G3 && G4))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}


			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}


			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}

			if(alpha[5].sprite.getPosition().x == a5x &&  alpha[5].sprite.getPosition().y == a5y)
			A5 = true;

			else
			{
				if(alpha[5].sprite.getPosition().x  <  a5x)
				{
					alpha[5].sprite.move(0.5f,0);
				}

				else if( alpha[5].sprite.getPosition().x > a5x)
				{
					alpha[5].sprite.move(-0.5f,0);
				}

				if(alpha[5].sprite.getPosition().y  <  a5y)
				{
					alpha[5].sprite.move(0,0.5f);
				}

				else if( alpha[5].sprite.getPosition().y > a5y)
				{
					alpha[5].sprite.move(0,-0.5f);
				}
			}

			if(alpha[6].sprite.getPosition().x == a6x &&  alpha[6].sprite.getPosition().y == a6y)
			A6 = true;

			else
			{
				if(alpha[6].sprite.getPosition().x  <  a6x)
				{
					alpha[6].sprite.move(0.5f,0);
				}

				else if( alpha[6].sprite.getPosition().x > a6x)
				{
					alpha[6].sprite.move(-0.5f,0);
				}

				if(alpha[6].sprite.getPosition().y  <  a6y)
				{
					alpha[6].sprite.move(0,0.5f);
				}

				else if( alpha[6].sprite.getPosition().y > a6y)
				{
					alpha[6].sprite.move(0,-0.5f);
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}
		///////////////////////////////////////////////////////////////////////

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}

			if(gamma[4].sprite.getPosition().x == g4x &&  gamma[4].sprite.getPosition().y == g4y)
			G4 = true;

			else
			{
				if(gamma[4].sprite.getPosition().x  <  g4x)
				{
					gamma[4].sprite.move(0.5f,0);
				}

				else if( gamma[4].sprite.getPosition().x > g4x)
				{
					gamma[4].sprite.move(-0.5f,0);
				}

				if(gamma[4].sprite.getPosition().y  <  g4y)
				{
					gamma[4].sprite.move(0,0.5f);
				}

				else if( gamma[4].sprite.getPosition().y > g4y)
				{
					gamma[4].sprite.move(0,-0.5f);
				}
			}

			window.draw(p->sprite);
			window.display();

		}
		p->sprite.setPosition(340,700);


	}

	void call_cross_filled_formation(RenderWindow &window)
	{
			updateinvaders = false;
			clear_all_invaders();

	float a0x = 340.0f, a1x = 375.0f , a2x = 290.0f , a3x = 375.0f, a4x = 290.0f,b0x = 255.0f , b1x = 410.0f , b2x = 410.0f , b3x  = 255.0f ,g0x = 490.0f ,g1x = 190.0f , g2x = 190.0f , g3x = 490.0f;
	float a0y = 200.0f, a1y = 70.0f, a2y = 70.0f , a3y = 325.0f, a4y = 325.0f, b0y = 240.0f , b1y = 150.0f , b2y = 240.0f , b3y = 150.0f ,g0y = 100.0f ,g1y = 295.0f , g2y = 100.0f , g3y = 295.0f;

	bool A0 , A1 , A2 , A3 , A4, B0 , B1 , B2 , B3 , G0 , G1  , G2 ,G3;
	A0  = A1 = A2 = A3 = A4 = B0 = B1 = B2 = B3 = G0 = G1 = G2 = G3 =false;
	
	
	alpha = new Alpha [5];
	beta = new Beta [4];
	gamma = new Gamma [4];
	
	alpha_count = 5;
	beta_count = 4;
	gamma_count = 4;
	
					
	alpha[0].sprite.setPosition(0,780); // center
	alpha[1].sprite.setPosition(780,0);
	alpha[2].sprite.setPosition(0,780);
	alpha[3].sprite.setPosition(780,0);
	alpha[4].sprite.setPosition(0,780);
	
	beta[0].sprite.setPosition(0,780); // down left
	beta[1].sprite.setPosition(0,780); // up right
	beta[2].sprite.setPosition(0,780); // down right
	beta[3].sprite.setPosition(0,780); // up left
	
	gamma[0].sprite.setPosition(0,0); // up right
	gamma[1].sprite.setPosition(0,0); //  down left
	gamma[2].sprite.setPosition(0,0); // up left
	gamma[3].sprite.setPosition(0,0);	// down right*


		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);
		while(!(A0 && A1 && A2 && A3 && A4 && B0 && B1 && B2 && B3 && G0 && G1 && G2 && G3))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}


			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}


			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}


			////////////////////////////////////////////////////////////////////////////////////////

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}

			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}
		///////////////////////////////////////////////////////////////////////

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}

			window.draw(p->sprite);
			window.display();

		}



	p->sprite.setPosition(340,700);	


	}

	void call_circle_filled_formation(RenderWindow &window)
	{
		clear_all_invaders();
		updateinvaders = false;
		float a0x = 340.0f, a1x = 340.0f , a2x = 340.0f , a3x =260.0f , a4x = 420.0f , b0x = 250.0f , b1x = 250.0f , b2x = 430.0f, b3x = 430.0f, g0x = 480.0f ,g1x = 200.0f  , g2x =340.0f , g3x=340.0f;
		float a0y = 50.0f, a1y = 300.0f, a2y =175.0f , a3y =175.0f , a4y =175.0f , b0y = 100.0f , b1y = 250.0f , b2y = 100.0f , b3y = 250.0f, g0y = 175.0f ,g1y = 175.0f , g2y =110.0f , g3y =240.0f;

		bool A0 ,A1  ,A3 , A4 , A2 , B0 , B1 , B2 , B3 , G0 , G1 , G2 , G3;
		A0  = A1 = A2 = A3 = A4 = B2 = B3 = B0 = B1 = G0 = G1 = G2 = G3 = false;

		alpha = new Alpha [5];
		beta = new Beta [4];
		gamma = new Gamma [4];
		
		alpha_count = 5;
		beta_count = 4;
		gamma_count = 4;
		
		alpha[0].sprite.setPosition(0,780); //done center up
		alpha[1].sprite.setPosition(780,0);
		alpha[2].sprite.setPosition(0,780); 
		alpha[3].sprite.setPosition(780,0);
		alpha[4].sprite.setPosition(0,780); 
				
		beta[0].sprite.setPosition(0,780); // 
		beta[1].sprite.setPosition(780,0);
		beta[2].sprite.setPosition(0,780);
		beta[3].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(0,780); //done  center down
		gamma[1].sprite.setPosition(780,0);
		gamma[2].sprite.setPosition(0,780); 
		gamma[3].sprite.setPosition(780,0);


		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);
		while(!(A0 && A1 && A2 && A3 && A4 && B0 && B1 && B2 && B3 &&  G0 && G1  && G2 && G3))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}

			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}

			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}


			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}


			window.draw(p->sprite);
			window.display();
		}

	}

	void call_diamond_filled_formation(RenderWindow &window)
	{
		clear_all_invaders();
		updateinvaders = false;
		float a0x = 340.0f, a1x = 340.0f , a2x = 340.0f , a3x =240.0f , a4x = 440.0f  ,b0x = 240.0f , b1x = 240.0f , b2x = 440.0f, b3x = 440.0f, g0x = 530.0f ,g1x = 150.0f , g2x = 340.0f , g3x = 340.0f  ;
		float a0y = 40.0f, a1y = 310.0f, a2y = 175.0f , a3y= 175.0f , a4y= 175.0f ,b0y = 110.0f , b1y = 250.0f , b2y = 110.0f , b3y = 250.0f, g0y = 175.0f ,g1y = 175.0f ,  g2y =110.0f , g3y =240.0f;

		bool A0 ,A1 , A2 , A3 , A4 , B0 , B1 , B2 , B3 , G0 , G1 ,G2 ,G3 ;
		A0  = A1 = A2 = A3 = A4 = B2 = B3 = B0 = B1 = G0 = G1 = G2 = G3 = false;

		alpha = new Alpha [5];
		beta = new Beta [4];
		gamma = new Gamma [4];
		
		alpha_count = 5;
		beta_count = 4;
		gamma_count = 4;
		
		alpha[0].sprite.setPosition(0,780); //done center up
		alpha[1].sprite.setPosition(780,0);
		alpha[2].sprite.setPosition(0,780); 
		alpha[3].sprite.setPosition(780,0);
		alpha[4].sprite.setPosition(0,780); 
				
		beta[0].sprite.setPosition(0,780); // 
		beta[1].sprite.setPosition(780,0);
		beta[2].sprite.setPosition(0,780);
		beta[3].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(0,780); //done  center down
		gamma[1].sprite.setPosition(780,0);
		gamma[2].sprite.setPosition(0,780); 
		gamma[3].sprite.setPosition(780,0);

		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);
		while(!(A0 && A1 && A2 && A3 && A4 && B0 && B1 && B2 && B3 &&  G0 && G1  && G2 && G3))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
			
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}

			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}


			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}


			window.draw(p->sprite);
			window.display();
		}

	}

	void call_heart_filled_formation(RenderWindow &window)
	{	
		clear_all_invaders();
		updateinvaders = false;
		float a0x = 340.0f, a1x = 450.0f , a2x = 220.0f , a3x= 420.0f , a4x= 260.0f  , b0x = 185.0f , b1x = 495.0f , b2x = 337.5f, b3x = 340.0f , g0x = 420.0f ,g1x = 260.0f  , g2x = 280.0f , g3x = 395.0f ;
		float a0y = 110.0f, a1y = 175.0f, a2y = 175.0f, a3y = 110.0f , a4y= 110.0f ,  b0y = 100.0f , b1y = 100.0f , b2y = 295.0f , b3y =180.0f , g0y = 50.0f ,g1y = 50.0f , g2y = 240.0f, g3y = 240.0f  ;

		bool A0 ,A1 , A2 , A3 , A4, B0 , B1 , B2 , B3 ,  G0 , G1 ,G2 ,G3 ;
		A0  = A1 = A2 = A3 = A4 =B2 = B0 = B1 = B3 =  G0 = G1 = G2 = G3 = false;

		alpha = new Alpha [5];
		beta = new Beta [4];
		gamma = new Gamma [4];
		
		alpha_count = 5;
		beta_count = 4;
		gamma_count = 4;
		
		alpha[0].sprite.setPosition(0,780);
		alpha[1].sprite.setPosition(780,0);
		alpha[2].sprite.setPosition(0,780);
		alpha[3].sprite.setPosition(780,0);
		alpha[4].sprite.setPosition(0,780);
				
		beta[0].sprite.setPosition(0,780);  
		beta[1].sprite.setPosition(780,0);
		beta[2].sprite.setPosition(0,780);
		beta[3].sprite.setPosition(780,0);
		
		gamma[0].sprite.setPosition(0,780); 
		gamma[1].sprite.setPosition(780,0);
		gamma[2].sprite.setPosition(0,780);
		gamma[3].sprite.setPosition(780,0);


		p->sprite.setPosition(340,700);
		p->sprite.setRotation(0);
		while(!(A0 && A1 && A2 && A3 && A4 && B0 && B1 && B2 && B3 &&G0 && G1 && G2 && G3))
		{

			window.clear();
			window.draw(background);
			for(int i=0 ; i < alpha_count ; i++)
			{
				window.draw(alpha[i].sprite);
			}

			for(int i=0 ; i < beta_count ; i++)
			{	int k=0;
				window.draw(beta[i].sprite);
			}

			for(int i=0 ; i < gamma_count ; i++)
			{
				window.draw(gamma[i].sprite);
			}
			
			if(alpha[0].sprite.getPosition().x == a0x &&  alpha[0].sprite.getPosition().y == a0y)
			A0 = true;

			else
			{
				if(alpha[0].sprite.getPosition().x  <  a0x)
				{
					alpha[0].sprite.move(0.5,0);
				}

				else if( alpha[0].sprite.getPosition().x > a0x)
				{
					alpha[0].sprite.move(-0.5,0);
				}

				if(alpha[0].sprite.getPosition().y  <  a0y)
				{
					alpha[0].sprite.move(0,0.5);
				}

				else if( alpha[0].sprite.getPosition().y > a0y)
				{
					alpha[0].sprite.move(0,-0.5);
				}

				//std::cout<<a0x << "    "<<alpha[0].sprite.getPosition().x <<std::endl;
			}

			if(alpha[1].sprite.getPosition().x == a1x &&  alpha[1].sprite.getPosition().y == a1y)
			A1 = true;

			else
			{
				if(alpha[1].sprite.getPosition().x  <  a1x)
				{
					alpha[1].sprite.move(0.5f,0);
				}

				else if( alpha[1].sprite.getPosition().x > a1x)
				{
					alpha[1].sprite.move(-0.5f,0);
				}

				if(alpha[1].sprite.getPosition().y  <  a1y)
				{
					alpha[1].sprite.move(0,0.5f);
				}

				else if( alpha[1].sprite.getPosition().y > a1y)
				{
					alpha[1].sprite.move(0,-0.5f);
				}
			}

			if(alpha[2].sprite.getPosition().x == a2x &&  alpha[2].sprite.getPosition().y == a2y)
			A2 = true;

			else
			{
				if(alpha[2].sprite.getPosition().x  <  a2x)
				{
					alpha[2].sprite.move(0.5f,0);
				}

				else if( alpha[2].sprite.getPosition().x > a2x)
				{
					alpha[2].sprite.move(-0.5f,0);
				}

				if(alpha[2].sprite.getPosition().y  <  a2y)
				{
					alpha[2].sprite.move(0,0.5f);
				}

				else if( alpha[2].sprite.getPosition().y > a2y)
				{
					alpha[2].sprite.move(0,-0.5f);
				}
			}

			if(alpha[3].sprite.getPosition().x == a3x &&  alpha[3].sprite.getPosition().y == a3y)
			A3 = true;

			else
			{
				if(alpha[3].sprite.getPosition().x  <  a3x)
				{
					alpha[3].sprite.move(0.5f,0);
				}

				else if( alpha[3].sprite.getPosition().x > a3x)
				{
					alpha[3].sprite.move(-0.5f,0);
				}

				if(alpha[3].sprite.getPosition().y  <  a3y)
				{
					alpha[3].sprite.move(0,0.5f);
				}

				else if( alpha[3].sprite.getPosition().y > a3y)
				{
					alpha[3].sprite.move(0,-0.5f);
				}
			}

			if(alpha[4].sprite.getPosition().x == a4x &&  alpha[4].sprite.getPosition().y == a4y)
			A4 = true;

			else
			{
				if(alpha[4].sprite.getPosition().x  <  a4x)
				{
					alpha[4].sprite.move(0.5f,0);
				}

				else if( alpha[4].sprite.getPosition().x > a4x)
				{
					alpha[4].sprite.move(-0.5f,0);
				}

				if(alpha[4].sprite.getPosition().y  <  a4y)
				{
					alpha[4].sprite.move(0,0.5f);
				}

				else if( alpha[4].sprite.getPosition().y > a4y)
				{
					alpha[4].sprite.move(0,-0.5f);
				}
			}

			if(beta[0].sprite.getPosition().x == b0x &&  beta[0].sprite.getPosition().y == b0y)
			B0 = true;

			else
			{
				if(beta[0].sprite.getPosition().x  <  b0x)
				{
					beta[0].sprite.move(0.5,0);
				}

				else if( beta[0].sprite.getPosition().x > b0x)
				{
					beta[0].sprite.move(-0.5,0);
				}

				if(beta[0].sprite.getPosition().y  <  b0y)
				{
					beta[0].sprite.move(0,0.5);
				}

				else if( beta[0].sprite.getPosition().y > b0y)
				{
					beta[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(beta[1].sprite.getPosition().x == b1x &&  beta[1].sprite.getPosition().y == b1y)
			B1 = true;

			else
			{
				if(beta[1].sprite.getPosition().x  <  b1x)
				{
					beta[1].sprite.move(0.5f,0);
				}

				else if( beta[1].sprite.getPosition().x > b1x)
				{
					beta[1].sprite.move(-0.5f,0);
				}

				if(beta[1].sprite.getPosition().y  <  b1y)
				{
					beta[1].sprite.move(0,0.5f);
				}

				else if( beta[1].sprite.getPosition().y > b1y)
				{
					beta[1].sprite.move(0,-0.5f);
				}
			}

			if(beta[2].sprite.getPosition().x == b2x &&  beta[2].sprite.getPosition().y == b2y)
			B2 = true;

			else
			{
				if(beta[2].sprite.getPosition().x  <  b2x)
				{
					beta[2].sprite.move(0.5f,0);
				}

				else if( beta[2].sprite.getPosition().x > b2x)
				{
					beta[2].sprite.move(-0.5f,0);
				}

				if(beta[2].sprite.getPosition().y  <  b2y)
				{
					beta[2].sprite.move(0,0.5f);
				}

				else if( beta[2].sprite.getPosition().y > b2y)
				{
					beta[2].sprite.move(0,-0.5f);
				}
			}

			if(beta[3].sprite.getPosition().x == b3x &&  beta[3].sprite.getPosition().y == b3y)
			B3 = true;

			else
			{
				if(beta[3].sprite.getPosition().x  <  b3x)
				{
					beta[3].sprite.move(0.5f,0);
				}

				else if( beta[3].sprite.getPosition().x > b3x)
				{
					beta[3].sprite.move(-0.5f,0);
				}

				if(beta[3].sprite.getPosition().y  <  b3y)
				{
					beta[3].sprite.move(0,0.5f);
				}

				else if( beta[3].sprite.getPosition().y > b3y)
				{
					beta[3].sprite.move(0,-0.5f);
				}
			}

			if(gamma[0].sprite.getPosition().x == g0x &&  gamma[0].sprite.getPosition().y == g0y)
			G0 = true;

			else
			{
				if(gamma[0].sprite.getPosition().x  <  g0x)
				{
					gamma[0].sprite.move(0.5,0);
				}

				else if( gamma[0].sprite.getPosition().x > g0x)
				{
					gamma[0].sprite.move(-0.5,0);
				}

				if(gamma[0].sprite.getPosition().y  <  g0y)
				{
					gamma[0].sprite.move(0,0.5);
				}

				else if( gamma[0].sprite.getPosition().y > g0y)
				{
					gamma[0].sprite.move(0,-0.5);
				}

				//std::cout<<b0x << "    "<<beta[0].sprite.getPosition().x <<std::endl;
			}

			if(gamma[1].sprite.getPosition().x == g1x &&  gamma[1].sprite.getPosition().y == g1y)
			G1 = true;

			else
			{
				if(gamma[1].sprite.getPosition().x  <  g1x)
				{
					gamma[1].sprite.move(0.5f,0);
				}

				else if( gamma[1].sprite.getPosition().x > g1x)
				{
					gamma[1].sprite.move(-0.5f,0);
				}

				if(gamma[1].sprite.getPosition().y  <  g1y)
				{
					gamma[1].sprite.move(0,0.5f);
				}

				else if( gamma[1].sprite.getPosition().y > g1y)
				{
					gamma[1].sprite.move(0,-0.5f);
				}
			}

			if(gamma[2].sprite.getPosition().x == g2x &&  gamma[2].sprite.getPosition().y == g2y)
			G2 = true;

			else
			{
				if(gamma[2].sprite.getPosition().x  <  g2x)
				{
					gamma[2].sprite.move(0.5f,0);
				}

				else if( gamma[2].sprite.getPosition().x > g2x)
				{
					gamma[2].sprite.move(-0.5f,0);
				}

				if(gamma[2].sprite.getPosition().y  <  g2y)
				{
					gamma[2].sprite.move(0,0.5f);
				}

				else if( gamma[2].sprite.getPosition().y > g2y)
				{
					gamma[2].sprite.move(0,-0.5f);
				}
			}

			if(gamma[3].sprite.getPosition().x == g3x &&  gamma[3].sprite.getPosition().y == g3y)
			G3 = true;

			else
			{
				if(gamma[3].sprite.getPosition().x  <  g3x)
				{
					gamma[3].sprite.move(0.5f,0);
				}

				else if( gamma[3].sprite.getPosition().x > g3x)
				{
					gamma[3].sprite.move(-0.5f,0);
				}

				if(gamma[3].sprite.getPosition().y  <  g3y)
				{
					gamma[3].sprite.move(0,0.5f);
				}

				else if( gamma[3].sprite.getPosition().y > g3y)
				{
					gamma[3].sprite.move(0,-0.5f);
				}
			}

			window.draw(p->sprite);
			window.display();
		}


	}

	void update_invaders()
		{

			for(int i=0 ; i<alpha_count ; i++)
			{
				if(!alpha[i].bombs_active  && alpha[i].sprite.getPosition().x == 1000 && alpha[i].sprite.getPosition().y == 1000)
				{
					for(int j=i ; j<alpha_count - 1; j++)
					{
						alpha[j] = alpha[j+1];
					
					}
					alpha_count--;
					i--;
				}
			}

			for(int i=0 ; i<beta_count ; i++)
			{
				if(!beta[i].bombs_active && beta[i].sprite.getPosition().x == 1000 && beta[i].sprite.getPosition().y == 1000)
				{
					for(int j=i ; j<beta_count - 1; j++)
					{
						beta[j] = beta[j+1];
					
					}
					beta_count--;
					i--;
				}
			}

			for(int i=0 ; i<gamma_count ; i++)
			{
				if(!gamma[i].bombs_active && gamma[i].sprite.getPosition().x == 1000 && gamma[i].sprite.getPosition().y == 1000 )
				{
					for(int j=i ; j<gamma_count - 1; j++)
					{
						gamma[j] = gamma[j+1];
					
					}
					gamma_count--;
					i--;
				}
			}

		}

	void clear_all_invaders()
	{
		if(alpha_alive!=0)
		delete[] alpha;

		if(beta_alive!=0)
		delete [] beta;

		if(gamma_alive!=0)
		delete [] gamma;	
		
		alpha_count = 0 ;
		beta_count = 0;
		gamma_count = 0;
		alpha_alive = beta_alive = gamma_alive = 0;
	}	
		
	bool check_invader_collision( float bulletX , float bulletY , float &x , float&y  ,int &score , int level)
		{
			
			for(int i =0 ; i < alpha_count ; i++)
			{
				if(alpha[i].sprite.getPosition().y > 780)
				continue;
				
				if(alpha[i].detect_collisions(bulletX , bulletY) == true)
				{
					x = alpha[i].sprite.getPosition().x ;
					y =  alpha[i].sprite.getPosition().y ;
					
					//std::cout<<"collision true alpha \n"<<alpha[i].sprite.getPosition().x<<" "<<alpha[i].sprite.getPosition().y<<"\n" << bulletX << " "<<bulletY<<"\n"
					alpha[i].sprite.setPosition(1000,1000);
					score += (10*level);
					return true;
				}	
			}
			
			for(int i =0 ; i < beta_count ; i++)
			{
				if(beta[i].sprite.getPosition().y > 780)
				continue;
				
				if(beta[i].detect_collisions(bulletX , bulletY) == true)
				{
					x = beta[i].sprite.getPosition().x ;
					y = beta[i].sprite.getPosition().y ;
					//std::cout<<"collision true beta \n"<<beta[i].sprite.getPosition().x<<" "<<beta[i].sprite.getPosition().y<<"\n"<< bulletX << " "<<bulletY<<"\n";
					beta[i].sprite.setPosition(1000,1000);
					score += (20*level);
					return true;
				}	
			}
			
			for(int i =0 ; i < gamma_count ; i++)
			{
				if(gamma[i].sprite.getPosition().y > 780)
				continue;
				
				if(gamma[i].detect_collisions(bulletX , bulletY) == true)
				{
					x = gamma[i].sprite.getPosition().x ;
					y = gamma[i].sprite.getPosition().y ;
					score += (30*level);
					
					//std::cout<<"collision true gamma \n"<<gamma[i].sprite.getPosition().x<<" "<<gamma[i].sprite.getPosition().y<<"\n"<< bulletX << " "<<bulletY<<"\n";
					gamma[i].sprite.setPosition(1000,1000);
					return true;
				}	
			}
			
			return false;	
		}

	void display_healths(RenderWindow& window, int life)
	{
		Sprite *sprites;

		if ( sizeof(sprites) / sizeof(Sprite) != life )
		{
			sprites = new Sprite [life];
			float x = 20;
			for (int i = 0; i < life; i++)
			{
				sprites[i].setTexture(health);
				sprites[i].setPosition(x, 5);
				sprites[i].setScale(0.08f, 0.08f);
				x+=40;
			}

		}

		for (int i = 0; i < life; i++)
		{
			window.draw(sprites[i]);
		}
	}

	void monster_animation(RenderWindow &window)
	{
		bool destination = false;
		float dx = 360.0f, dy = 50.0f;

		monster->sprite.setPosition(0,780);

		while(!destination)
		{	
			window.clear();
			if(std::round(monster->sprite.getPosition().x) == dx &&  std::round(monster->sprite.getPosition().y )== dy)
				destination = true;

			else
			{

				if(monster->sprite.getPosition().x  <  dx)
				{
					monster->sprite.move(0.2,0);
				}

				else if( monster->sprite.getPosition().x > dx)
				{
					monster->sprite.move(-0.2,0);
				}

				if(monster->sprite.getPosition().y  <  dy)
				{
					monster->sprite.move(0,0.2);
				}

				else if( monster->sprite.getPosition().y > dy)
				{
					monster->sprite.move(0,-0.2);
				}

			}
			window.draw(background);
			window.draw(monster->sprite);
			window.display();

		}

	}

	void dragon_animation(RenderWindow &window)
	{
		bool destination = false;
		float dx = 250 , dy = 50;

		dragon->sprite.setPosition(780,780);

		while(!destination)
		{	
			window.clear();
			if(dragon->sprite.getPosition().x == dx &&  dragon->sprite.getPosition().y == dy)
				destination = true;

			else
			{
				if(dragon->sprite.getPosition().x > dx)
				dragon->sprite.setRotation(135);

				else
				dragon->sprite.setRotation(225);

				if(dragon->sprite.getPosition().x  <  dx)
				{
					dragon->sprite.move(0.5,0);
				}

				else if( dragon->sprite.getPosition().x > dx)
				{
					dragon->sprite.move(-0.5,0);
				}

				if(dragon->sprite.getPosition().y  <  dy)
				{
					dragon->sprite.move(0,0.5);
				}

				else if( dragon->sprite.getPosition().y > dy)
				{
					dragon->sprite.move(0,-0.5);
				}

			}
			window.draw(background);
			window.draw(dragon->sprite);
			window.display();

		}
		dragon->sprite.setRotation(0);
	}

	void shake_invaders(RenderWindow &window)
	{
		static bool right = true;
		static bool left = false;

		for(int i=0 ; i < alpha_count ; i++)
		{
			if(right)
			{
				alpha[i].sprite.move(2,0);
			}

			else if(left)
			{
				alpha[i].sprite.move(-2,0);
			}
		}

		for(int i=0 ; i < beta_count ; i++)
		{
			if(right)
			{
				beta[i].sprite.move(2,0);
			}

			else if(left)
			{
				beta[i].sprite.move(-2,0);
			}
		}

		for(int i=0 ; i < gamma_count ; i++)
		{
			if(right)
			{
				gamma[i].sprite.move(2,0);
			}

			else if(left)
			{
				gamma[i].sprite.move(-2,0);
			}
		}

		if(right)
		{
			right = false;
			left = true;
		}

		else
		{
			right = true;
			left = false;
		}

	}

	void the_boys(RenderWindow &window)
	{
		float x  = 230 , y = 300;
		bool reached = false;

		Sprite sp , bgg;
		Texture texx , texx2 , texx3;

		texx.loadFromFile("img/PNG/theboys2.png");
		texx2.loadFromFile("img/PNG/theboys.png");
		texx3.loadFromFile("img/PNG/punit.png");
		sp.setTexture(texx);
		bgg.setTexture(texx3);
		bgg.setScale(3,2);

		sp.setPosition(340 , 800);
		sp.setScale(0.5 , 0.5);
		Music bones;
		bones.openFromFile("sounds/bones.wav");

		bones.play();
		while(!reached)
		{
			window.clear();
			window.draw(bgg);
			
			if(round(sp.getPosition().x )== x &&  round(sp.getPosition().y) == y)
				reached = true;

				else
				{
					if(sp.getPosition().x  <  x)
					{
						sp.move(0.07,0);
					}

					else if(sp.getPosition().x > x)
					{
						sp.move(-0.07,0);
					}

					if(sp.getPosition().y  <  y)
					{
						sp.move(0,0.07);
					}

					else if( sp.getPosition().y > y)
					{
						sp.move(0,-0.07);
					}


				}
				sp.rotate(0.4);
				window.draw(sp);
				window.display();
		}	

		Clock clock;

		float T = clock.getElapsedTime().asSeconds();

		sp.setTexture(texx2);
		sp.setRotation(0);
		while(clock.getElapsedTime().asSeconds() - T <= 9)
		{
			window.clear();
			window.draw(bgg);
			window.draw(sp);
			window.display();

		}
	}

	void exit_animation(RenderWindow &window , int score , std::string type)
	{


		bg_music.stop();
		monster_theme.stop();

		Clock clk2;
		float t2;

		Sprite title , SCORE , exit , nums;
		Texture tex_title , Score_tex , exit_tex , num_tex;


		Score_tex.loadFromFile("img/animation/score.png");
		exit_tex.loadFromFile("img/animation/exit.png");

		SCORE.setTexture(Score_tex);
		exit.setTexture(exit_tex);

		SCORE.setPosition(40 , 350);
		SCORE.setScale(0.5,0.5);
		exit.setPosition(10,550);
		exit.setScale(0.45,0.45);

		t2 = clk2.getElapsedTime().asSeconds();

		p->sprite.setPosition(340,700);

		Music m;
		m.openFromFile("sounds/gameover.wav");
		m.play();

		while(clk2.getElapsedTime().asSeconds()- t2 < 2.5f)
		{
			window.clear();
			window.draw(background);
			window.draw(p->sprite);

			p->sprite.move(0,-0.25);

			if(monster->sprite.getPosition().y < 780 && monster->sprite.getPosition().y > 0)
			{
				monster->sprite.move(0.2f,0);
				window.draw(monster->sprite);
			}

			else if (dragon->sprite.getPosition().y < 780 && dragon->sprite.getPosition().y > 0)
			{
				dragon->sprite.move(0.2f,0);
				window.draw(dragon->sprite);
			}

			else
			{
				for(int i=0 ; i < alpha_count ; i++)
				{
					alpha[i].sprite.move(0.2f,0.0f);
					window.draw(alpha[i].sprite);
				}

				for(int i=0 ; i < beta_count ; i++)
				{
					beta[i].sprite.move(0.2f,0.0f);
					window.draw(beta[i].sprite);
				}

				for(int i=0 ; i < gamma_count ; i++)
				{
					gamma[i].sprite.move(0.2f,0.0f);
					window.draw(gamma[i].sprite);
				}
			}

			window.display();

		}
		m.stop();


		if(type == "w")
		{
			tex_title.loadFromFile("img/animation/won.png");
			title.setTexture(tex_title);
			title.setPosition(70,50);
			title.setScale(0.65,0.65);
		}

		else if(type == "l")
		{
			tex_title.loadFromFile("img/animation/die.png");
			title.setTexture(tex_title);
			title.setPosition(70,50);
			title.setScale(0.65,0.65);
		}

		else if (type == "e")
		{
			tex_title.loadFromFile("img/animation/over.png");
			title.setTexture(tex_title);
			title.setPosition(40,50);
			title.setScale(0.65,0.65);
		}

		

		int score2 = score;
		int size = 0 , remainder;
		while((score2/=10) >0)
		{
			size++;
		}
		size++;


		Texture tex[size];
		Sprite sp[size];

		for(int i= size -1 ; i>=0 ; i--)
		{	
			remainder = score % 10;
			score /=10;

			if(remainder == 1)
			{
				tex[i].loadFromFile("img/animation/one.png");
			}

			else if(remainder == 2)
			{
				tex[i].loadFromFile("img/animation/two.png");
			}

			else if(remainder == 3)
			{
				tex[i].loadFromFile("img/animation/three.png");
			}

			else if(remainder == 4)
			{
				tex[i].loadFromFile("img/animation/four.png");
			}

			else if(remainder == 5)
			{
				tex[i].loadFromFile("img/animation/five.png");
			}

			else if(remainder == 6)
			{
				tex[i].loadFromFile("img/animation/six.png");
			}

			else if(remainder == 7)
			{
				tex[i].loadFromFile("img/animation/seven.png");
			}

			else if(remainder == 8)
			{
				tex[i].loadFromFile("img/animation/eight.png");
			}

			else if(remainder == 9)
			{
				tex[i].loadFromFile("img/animation/nine.png");
			}

			else if(remainder == 0)
			{
				tex[i].loadFromFile("img/animation/zero.png");
			}

			sp[i].setTexture(tex[i]);
		}

		float x = 450;
		for(int i =0 ; i <size ; i++)
		{
			sp[i].setScale(0.4,0.4);
			sp[i].setPosition(SCORE.getPosition().x + x , SCORE.getPosition().y + 10);
			x +=53;
		}

		clk2.restart();
		t2 = clk2.getElapsedTime().asSeconds();

		//countdown 340 650 
		//score 40 350
		//exit 10 550 
		// title 70 50  , 40 50 
		
		Sprite Countdown[5];
		Texture countdown [5];
		countdown[0].loadFromFile("img/animation/five.png");
		countdown[1].loadFromFile("img/animation/four.png");
		countdown[2].loadFromFile("img/animation/three.png");
		countdown[3].loadFromFile("img/animation/two.png");
		countdown[4].loadFromFile("img/animation/one.png");

		for(int i=0 ; i <5 ; i++)
		{
			Countdown[i].setTexture(countdown[i]);
			Countdown[i].setScale(0.70,0.70);
			Countdown[i].setPosition(340,650);
		}
		

		

		while(clk2.getElapsedTime().asSeconds() - t2 <=5)
		{
			window.clear();
			window.draw(background);
			window.draw(title);
			window.draw(SCORE);
			window.draw(exit);
			for(int i=0 ; i < size ; i++)
			{
				window.draw(sp[i]);
			}

			if(clk2.getElapsedTime().asSeconds() - t2 <=5 && clk2.getElapsedTime().asSeconds() - t2 > 4 )
			window.draw(Countdown[4]);

			else if (clk2.getElapsedTime().asSeconds() - t2 <=4 && clk2.getElapsedTime().asSeconds() - t2 > 3 )
			window.draw(Countdown[3]);

			else if (clk2.getElapsedTime().asSeconds() - t2 <=3 && clk2.getElapsedTime().asSeconds() - t2 > 2 )
			window.draw(Countdown[2]);

			else if (clk2.getElapsedTime().asSeconds() - t2 <=2 && clk2.getElapsedTime().asSeconds() - t2 > 1 )
			window.draw(Countdown[1]);

			else if (clk2.getElapsedTime().asSeconds() - t2 <=1 && clk2.getElapsedTime().asSeconds() - t2 > 0 )
			window.draw(Countdown[0]);	

			window.display();
		}



	}

};

			
