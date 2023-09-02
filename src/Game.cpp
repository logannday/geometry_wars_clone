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

            // add velocity to position
            // Vec2 &velocity = m_player->cTransform->velocity;
            // Vec2 &position = m_player->cTransform->pos;
            // position.x += velocity.x;
            // position.y += velocity.y;
void Game::sUserInput()
{
    sf::Event event;

    while(m_window.pollEvent(event))
    {
        // player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            std::cout << "working";
            m_player->cInput->right = true;
        } else {
            m_player->cInput->right = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_player->cInput->left = true;
        } else {
            m_player->cInput->left = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_player->cInput->up = true;
        } else {
            m_player->cInput->up = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_player->cInput->down = true;
        } else {
            m_player->cInput->down = false;
        }
    };
}

void Game::sMovement()
{
    //Player Movement
    // m_player->cTransform->velocity = {0, 0};
    Vec2 &playerVel= m_player->cTransform->velocity;
    Vec2 &playerPos= m_player->cTransform->pos;
    for (auto& e : m_entities.getEntities())
    {
        e->cTransform->velocity = {0, 0};
    }

    // Player Horizontal Movement
    // TODO: Make it impossible to leave the window
    if(m_player->cInput->right)
    {
        playerVel.x = 0.1;
    }
    else if(m_player->cInput->left)
    {
        playerVel.x = -0.1;
    }
    else if(m_player->cInput->left && m_player->cInput->left)
    {
        playerVel.x = -0.1;
    }

    // Player Vertical Movement
    if(m_player->cInput->down)
    {
        playerVel.y = 0.1;
    }
    else if(m_player->cInput->up)
    {
        playerVel.y = -0.1f;
    }
    else if(m_player->cInput->down && m_player->cInput->up)
    {
        playerVel.y = 0.0f;
    }

    // float playerX = m_player->cShape->circle.getPosition().x;

    // playerPos += playerVel;
    // m_player->cShape->circle.setPosition(
    //         playerPos.x, playerPos.y);
    for (auto& e : m_entities.getEntities())
    {
        Vec2& position = e->cTransform->pos;
        Vec2& velocity = e->cTransform->velocity;
        position += velocity;
        e->cShape->circle.setPosition(position.x, position.y);
    }
}


void Game::sSpawnPlayer()
{
    auto entity = m_entities.addEntity("player");
    std::cout << "entities.size: " << m_entities.getEntities().size();
    sf::Vector2u size = m_window.getSize();
    // TODO: figure out if passing in local variable references 
    // could be problematic here
    unsigned int windowWidth = size.x;
    unsigned int windowHeight = size.y;
    Vec2 position = {windowWidth / 2.0f, windowHeight / 2.0f};
    Vec2 velocity = {0.0f, 0.0f};
    entity->cTransform = std::make_shared<CTransform>(position, velocity, 1.0f);
    // entity->cTransform = std::make_shared<CTransform>
    //    (Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 1.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(25, 0, 0), 4.0f);

    entity->cInput = std::make_shared<CInput>();

    m_player = entity;
}

void Game::run()
{
    sSpawnPlayer();
    std::cout << "hello?";
    while (m_running) 
    {
        sUserInput();
        sMovement();
        m_entities.update();
        sRender();
        // TODO: implement other functions
    }
}


