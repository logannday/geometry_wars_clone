#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "EntityManager.h"

class Game
{
    sf::RenderWindow m_window;
    bool m_running;
    bool m_paused;
    EntityManager m_entities;
    std::shared_ptr<Entity> m_player;

    void init(std::string s);
    void sRender();
    void sUserInput();
    void sSpawnPlayer();
    void handleKey(sf::Event event);

public:
    Game(std::string s);
    void run(); 
};
