#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace sf;
using namespace std;

class Menu
{
public:
    Sprite menu , Instructions  , Instructions_, HighScore ,  HighScore_ ,LoadGame , EndGame , Start , EndGame1 , EndGame2 , EndGame3 , Background;
    Texture menu_ , instructions , instructions_ , highscore , highscore_ ,loadgame , endgame , start,  endgame1 , endgame2 , endgame3 , background;
    bool MENU ,HIGHSCORE , INSTRUCTIONS , ENDGAME;
    int counter; // to keep the track of up and down arrow keys
    Font font;

    Menu()
    {
        menu_.loadFromFile("img/menu/main_menu.png");
        instructions.loadFromFile("img/menu/instructions.png");
        highscore.loadFromFile("img/menu/highscores.png");
        loadgame.loadFromFile("img/menu/loadgame.png");
        endgame.loadFromFile("img/menu/endgame.png");
        start.loadFromFile("img/menu/start.png");
        instructions_.loadFromFile("img/menu/instruction_.png");
        highscore_.loadFromFile("img/menu/highscores_.png");
        endgame1.loadFromFile("img/menu/gameover.png");
        endgame2.loadFromFile("img/menu/gameover1.png");
        endgame3.loadFromFile("img/menu/gameover2.png");
        font.loadFromFile("3D.ttf");
        background.loadFromFile("img/cartoon_galaxy.jpg");

        menu.setTexture(menu_);
        Instructions.setTexture(instructions);
        HighScore.setTexture(highscore);
        LoadGame.setTexture(loadgame);
        EndGame.setTexture(endgame);
        Start.setTexture(start);
        HighScore_.setTexture(highscore_);
        Instructions_.setTexture(instructions_);
        EndGame1.setTexture(endgame1);
        EndGame2.setTexture(endgame2);
        EndGame3.setTexture(endgame3);
        Background.setTexture(background);

        menu.setScale(0.6,0.6);
        Instructions.setScale(0.6,0.6);
        HighScore.setScale(0.6,0.6);
        LoadGame.setScale(0.6,0.6);
        EndGame.setScale(0.6,0.6);
        Start.setScale(0.6,0.6);
        HighScore_.setScale(0.65,0.58);
        Instructions_.setScale(0.55,0.58);
        EndGame1.setScale(0.6,0.6);
        EndGame2.setScale(0.6,0.6);
        EndGame3.setScale(0.6,0.6);
        Background.setScale(0.6,0.6);

        MENU = true;
        HIGHSCORE = INSTRUCTIONS = ENDGAME = false;
        counter = 0;
    }

    void display_menu()
    {
        Clock clk;
        float  time;
        Event e;
        Music music , bg_music;
        int score = 0;

        music.openFromFile("sounds/button.wav");
        bg_music.openFromFile("sounds/menu.wav");
        music.setVolume(150.f);
        bg_music.setVolume(60.0f);
        bg_music.play();

        RenderWindow window(VideoMode(780, 780), "Game Menu");

        while(window.isOpen())
        {
            while (window.pollEvent(e))
            {  
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                {
                    window.close(); //close the game  
                    bg_music.stop();
                }
                                     	    
            }

            //------------------------ Managaing arrow key presses and sound wrt it -------------------------------------//

           if (clk.getElapsedTime().asSeconds() - time >=0.15 &&  Keyboard::isKeyPressed(Keyboard::Up)) 
           {
                music.stop();
                music.play();
                if(counter == 1)
                counter = 5;

                else
                    counter--;

                time = clk.getElapsedTime().asSeconds();
           }

           else if (clk.getElapsedTime().asSeconds() - time >=0.15 && Keyboard::isKeyPressed(Keyboard::Down))
           {
                music.stop();
                music.play();
                if(counter == 5)
                counter = 1;

                else
                    counter++;
                
                time = clk.getElapsedTime().asSeconds();
           }
           //-----------------------------------------------------------------------------------------------//

           if(Keyboard::isKeyPressed(Keyboard::Enter))
           {
                music.stop();
                music.play();
                if(counter == 1)
                {
                    Font font;
                        if (!font.loadFromFile("3D.ttf"))
                        {
                            cout << "Error loading font file" << endl;
                        }
                        Text text;
                        text.setFont(font);
                        text.setFillColor(Color::White);
                        text.setCharacterSize(40);
                        text.setPosition(70, 300);
                        text.setString("Enter your name: ");

                        string playerName = "";
                        bool isEnteringName = true;

                        while (isEnteringName)
                        {
                            while (window.pollEvent(e))
                            {
                                if (e.type == Event::Closed)
                                {
                                    window.close();
                                    isEnteringName = false;
                                    return;
                                }
                                else if (e.type == Event::TextEntered)
                                {
                                    if (e.text.unicode >= 32 && e.text.unicode < 128)
                                    {
                                        playerName += static_cast<char>(e.text.unicode);
                                        text.setString("Enter your name: " + playerName);
                                    }
                                    else if (e.text.unicode == 8 && playerName.size() > 0)
                                    {
                                        playerName.pop_back();
                                        text.setString("Enter your name: " + playerName);
                                    }
                                    else if (e.text.unicode == 13 && playerName.size() > 0)
                                    {
                                        isEnteringName = false;
                                    }
                                }
                            }

                            window.clear();
                            window.draw(Background);
                            window.draw(text);
                            window.display();
                         }
                    bg_music.stop();

                    ifstream infile1("scores.txt");
                    string line1 ,name1 ,bg;
                    bg = "";
                    int comma_pos;
                    
                    int index = 0;

                    while(getline(infile1, line1))
                    {   
                        index++;

                        comma_pos = line1.find(",");
                        name1 = line1.substr(0, comma_pos);

                        if(name1 == playerName)
                        {
                            if(index == 1)
                            {
                                bg = "Gold";
                                break;
                            }

                            else if(index == 2)
                            {
                                 bg = "Silver";
                                 break;
                            }

                            else if (index == 3)
                            {
                                 bg = "Bronze";
                                 break;
                            }
                        }
                    }
                    infile1.close();

                    start_game(window ,playerName , score , bg);
                    bg_music.play();
                    bg_music.setLoop(true);

                    ofstream score_file;
                    score_file.open("scores.txt", ios::app);
                    score_file << playerName << "," << score << endl;
                    score_file.close();

                    // Read existing entries from file and store in arrays
                    ifstream infile("scores.txt");
                    string name[100], line;
                    int scores[100], i = 0;
                    while (getline(infile, line)) {
                        int comma_pos = line.find(",");
                        name[i] = line.substr(0, comma_pos);
                        string score_str = line.substr(comma_pos + 1);
                        int score = stoi(score_str);
                        scores[i] = score;
                        i++;
                    }
                    infile.close();

                    // Sort scores in ascending order using bubble sort
                    for (int j = 0; j < i - 1; j++) {
                        for (int k = 0; k < i - j - 1; k++) {
                            if (scores[k] < scores[k + 1]) 
                            {
                                int temp = scores[k];
                                string temp1 = name[k];
                                scores[k] = scores[k + 1];
                                name[k] = name [k+1];
                                scores[k + 1] = temp;
                                name[k+1] = temp1;
                            }
                        }
                    }

                    // Writing sorted entries back to file
                    score_file.open("scores.txt");
                    for (int j = 0; j < i; j++) 
                    {
                        score_file << name[j] << "," << scores[j] << endl;
                    }
                    score_file.close();    
                }

                else if(counter == 2)
                {

                    window.clear();
                    INSTRUCTIONS = true;

                    while(INSTRUCTIONS)
                    {
                        while (window.pollEvent(e))
                        {  
                            if (e.type == Event::Closed) 
                            {
                                window.close(); 
                                bg_music.stop();
                            }                       	    
                        }
                      if(Keyboard::isKeyPressed(Keyboard::Escape))
                      {
                        music.stop();
                        music.play();
                        INSTRUCTIONS = false;
                      }
                        
                        window.draw(Instructions_);
                        window.display();
                    }

                }

                else if(counter == 3)
                {

                    window.clear();
                    HIGHSCORE= true;

                    Font font;
                    font.loadFromFile("3D.ttf");
                    Text scores[5] , names [5] , heading;

                    Sprite Badges[3];
                    Texture badges[3];

                    badges[0].loadFromFile("img/PNG/badges/gold.png");
                    badges[1].loadFromFile("img/PNG/badges/silver.png");
                    badges[2].loadFromFile("img/PNG/badges/bronze.png");
                    

                    Badges[0].setTexture(badges[0]);
                    Badges[1].setTexture(badges[1]);
                    Badges[2].setTexture(badges[2]);

                    for(int i=0 ; i < 3 ; i++)
                    Badges[i].setScale(0.2,0.2);

                    ifstream infile("scores.txt");
                    string line , name , score;
                    int comma_pos;
                    
                    int index = 0;
                    float y = 200;
                    while(getline(infile, line) && index < 5)
                    {   
                        comma_pos = line.find(",");
                        name = line.substr(0, comma_pos);
                        score = line.substr(comma_pos + 1);

                        scores[index].setFont(font);
                        scores[index].setCharacterSize(70);
                        scores[index].setFillColor(sf::Color(0, 0, 128)); // light purple
                        scores[index].setOutlineColor(sf::Color(175, 64, 175));
                        scores[index].setOutlineThickness(2);
                        scores[index].setString(score);

                        names[index].setFont(font);
                        names[index].setCharacterSize(70);
                        names[index].setFillColor(sf::Color(0, 191, 255));  // light purple
                        names[index].setOutlineColor(sf::Color(128, 0, 128));
                        names[index].setOutlineThickness(2);
                        names[index].setString(to_string(index+1) + ". " + name);

                        scores[index].setPosition(400, y);
                        names[index].setPosition(30, y);

                        index++;
                        y+= 100;
                    }
                    infile.close();


                    int badge_index = 0; 

                    if(index >= 3)
                    {
                        badge_index = 3;
                    }

                    else
                    {
                        badge_index = index;
                    }

                     y = 200;

                     for(int i=0 ; i<badge_index ; i++)
                     {
                        Badges[i].setPosition(600,y);
                        y+=100;
                     }

                    while(HIGHSCORE)
                    {   
                            window.clear();
                            while (window.pollEvent(e))
                            {  
                                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                                {
                                    window.close(); //close the game  
                                    bg_music.stop();
                                    return;
                                }                     	    
                            }
                            if(Keyboard::isKeyPressed(Keyboard::Escape))
                            {
                                music.stop();
                                music.play();
                                HIGHSCORE = false;
                            }
                                
                                window.draw(HighScore_);

                                for (int j = 0; j < index; j++) 
                                {
                                    window.draw(scores[j]);
                                    window.draw(names[j]);
                                }

                                for(int j=0 ; j<badge_index ; j++)
                                window.draw(Badges[j]);

                                window.display();
                    }

                }
                else if ( counter == 5)
                {

                    window.close();
                }

           }

           if(counter == 0)
           {
                window.clear();
                window.draw(menu);
           }

           else if(counter == 1)
            {
                window.clear();
                window.draw(Start);

            }

           else if(counter == 2)
           {
                window.clear();
                window.draw(Instructions);

           }

            else if(counter == 3)
           {
                window.clear();
                window.draw(HighScore);

           }

           else if(counter == 4)
           {
                window.clear();
                window.draw(LoadGame);
           }

           else if(counter == 5)
           {
                window.clear();
                window.draw(EndGame);

           }

            window.display();

        }
        bg_music.stop();
        
        
    }
    void start_game(RenderWindow& window , string &name,  int &score , string &bg)
    {
        Game g;
        g.start_game(window , name , score , bg);
    }

    


};
