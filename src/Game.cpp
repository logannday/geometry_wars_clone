#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
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
        switch(event.type)
        {
            case (sf::Event::MouseButtonPressed):
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    Vec2 mouseVec = {(float)event.mouseButton.x, (float)event.mouseButton.y};
                    sSpawnBullet(mouseVec);
                }
                break;
            default:
                break;
        }
    };
    // player movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_player->cInput->right = true;
    } else {
        m_player->cInput->right = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_player->cInput->left = true;
    } else {
        m_player->cInput->left = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_player->cInput->up = true;
    } else {
        m_player->cInput->up = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_player->cInput->down = true;
    } else {
        m_player->cInput->down = false;
    }
}

void Game::sMovement()
{
    //Player Movement
    // m_player->cTransform->velocity = {0, 0};
    Vec2 &playerVel= m_player->cTransform->velocity;
    Vec2 &playerPos= m_player->cTransform->pos;
    m_player->cTransform->velocity = {0, 0};

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

    sf::Vector2u size = m_window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    // Enemy Wall Collision Handling
    for (auto& e : m_entities.getEntities())
    {
        // Hackey solution for skipping the players
        if(e->tag().compare("enemy") != 0)
        {
            continue;
        }

        float x = e->cShape->circle.getPosition().x;
        float y = e->cShape->circle.getPosition().y;
        Vec2& velocity = e->cTransform->velocity;
        int radius = e->cShape->circle.getRadius();
        int playerRadius = m_player->cShape->circle.getRadius();

        // Player Enemy Collisions
        if (m_player->cTransform->pos.distance(e->cTransform->pos) < radius + playerRadius)
        {
            m_player->destroy();
            sSpawnPlayer();
        }

        // Bullet Collisions
        for (auto& bullet : m_entities.getEntities())
        {
            if (bullet->tag().compare("bullet") != 0) { continue; }
            if(bullet->cTransform->pos.distance(e->cTransform->pos) < radius + playerRadius)
            {
                e->destroy();
                bullet->destroy();
            }
        }

        if (x - radius <= 0 || x >= width - radius)
        {
            e->cTransform->velocity.x *= -1.0f;
        }
        if (y <= 0 + radius || y >= height - radius)
        {
            e->cTransform->velocity.y *= -1.0f;
        }
    }

    for (auto& e : m_entities.getEntities())
    {
        Vec2& position = e->cTransform->pos;
        Vec2& velocity = e->cTransform->velocity;
        position += velocity;
        e->cShape->circle.setPosition(position.x, position.y);
        e->cShape->circle.setRotation(e->cShape->circle.getRotation() + e->cTransform->angle);
    }
}

void Game::sLifetimes()
{
    // Hackey and disgusting
    try {
        for (auto& e : m_entities.getEntities("bullet"))
        {
            // if (e->tag().compare("bullet") != 0) 
            // {
            //     continue;
            // }
            
            std::cerr << e->tag();
            if (e->cLifespan->remaining-- <= 0)
            {
                e->destroy();
            }
        }
    } catch(...) {
    }
}

void Game::sSpawnPlayer()
{
    auto entity = m_entities.addEntity("player");
    std::cout << "entities.size: " << m_entities.getEntities().size();
    // TODO: figure out if passing in local variable references 
    // could be problematic here
    Vec2 position = {m_window.getSize().x / 2.0f, m_window.getSize().y  / 2.0f};
    Vec2 velocity = {0.0f, 0.0f};
    entity->cTransform = std::make_shared<CTransform>(position, velocity, 1.0f);
    entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(25, 0, 0), 4.0f);

    entity->cInput = std::make_shared<CInput>();

    m_player = entity;
}

void Game::sSpawnEnemy()
{
    if (m_currentFrame - m_lastEnemySpawnTime < 5000) { return; }
    m_lastEnemySpawnTime = m_currentFrame;
    auto entity = m_entities.addEntity("enemy");
    sf::Vector2u size = m_window.getSize();
    /* initialize random seed: */
    srand (time(NULL));
    /* generate secret number between 0 and window dimensions : */
    // TODO: change this to make sure they don't spawn partially off screen
    int xPosition = rand() % m_window.getSize().x;
    int yPosition = rand() % m_window.getSize().y;
    int numSides = rand() % 8;
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    Vec2 position = {(float) xPosition, (float) yPosition};
    Vec2 velocity = {0.05f, 0.05f};
    entity->cTransform = std::make_shared<CTransform>(position, velocity, 0.05f);
    entity->cShape = std::make_shared<CShape>(32.0f, numSides, sf::Color(r, g, b), sf::Color(25, 0, 0), 4.0f);
    entity->cInput = std::make_shared<CInput>();
}

void Game::sSpawnBullet(Vec2 & mousePosition)
{
    auto bullet = m_entities.addEntity("bullet");
    bullet->cLifespan = std::make_shared<CLifespan>(900);

    Vec2 &playerPosition = m_player->cTransform->pos;
    Vec2 bulletVelocity = mousePosition - playerPosition;
    bulletVelocity.normalize();
    bulletVelocity = bulletVelocity * 0.5f;

    bullet->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos, bulletVelocity, 0.05f);
    bullet->cShape = std::make_shared<CShape>(10.0f, 8, sf::Color(50, 50, 10), sf::Color(50, 50, 50), 4.0f);
    bullet->cInput = std::make_shared<CInput>();
}

void Game::run()
{
    sSpawnPlayer();
    while (m_running) 
    {
        m_currentFrame++;
        sUserInput();
        sSpawnEnemy();
        // Vec2 vec = {100, 100};
        // sSpawnBullet(vec);
        sMovement();
        sLifetimes();
        m_entities.update();
        sRender();
        m_entities.printMap();
        // TODO: implement other functions
    }
}
