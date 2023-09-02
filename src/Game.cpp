#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Components.h"
#include "Vec2.h"
#include <memory>


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
    m_window.clear();
    
    for(auto& e : m_entities.getEntities())
    {
        m_window.draw(e->cShape->circle);
    }

    m_window.display();
}

void Game::sUserInput()
{
    sf::Event event;

    while(m_window.pollEvent(event))
    {
        // player movement
        switch(event.type) 
        {
            case sf::Event::KeyPressed:
                break;
        }
    
    };
}

void Game::sSpawnPlayer()
{
    auto entity = m_entities.addEntity("player");
    std::cout << "entities.size: " << m_entities.getEntities().size();
    Vec2 v1 = {200.0f, 200.0f};
    Vec2 v2 = {2.0f, 2.0f};
    entity->cTransform = std::make_shared<CTransform>(v1, v2, 1.0f);
    // entity->cTransform = std::make_shared<CTransform>
    //    (Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 1.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(25, 0, 0), 4.0f);
    m_player = entity;
}

void Game::run()
{
    sSpawnPlayer();
    std::cout << "hello?";
    while (m_running) 
    {
        sUserInput();
        m_entities.update();
        sRender();
        // Todo: implement other functions
    }
}


