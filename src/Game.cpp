#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


Game::Game(std::string s)
{
    init(s);
}

void Game::init(std::string s)
{
    m_paused = false;
    m_running = true;
    m_window.create(sf::VideoMode(800,800), "Elite game");
}

void Game::sRender()
{
    sf::CircleShape circle(50.0f);
    m_window.clear();
    m_window.draw(circle);
    m_window.display();
}

void Game::run()
{
    while (m_running) 
    {
        sRender();
        // Todo: implement other functions
    }
}


