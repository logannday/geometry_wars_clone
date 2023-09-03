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
    unsigned long m_currentFrame;
    unsigned long m_lastEnemySpawnTime = 0;

    void init(std::string s);
    void sRender();
    void sUserInput();
    void sSpawnPlayer();
    void sMovement();
    void HandleKey(sf::Event event);
    //TODO: 
    void sSpawnEnemy();
    void sSpawnBullet(Vec2 & mousePosition);
        
public:
    Game(std::string s);
    void run(); 
};
