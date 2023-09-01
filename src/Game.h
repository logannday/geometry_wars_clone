#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
    sf::RenderWindow m_window;
    bool m_running;
    bool m_paused;
    //Todo: EM, 

    void init(std::string s);
    void sRender();

public:
    Game(std::string s);
    void run(); 
};
