#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec; 
typedef std::map <std::string, EntityVec> EntityMap;

class EntityManager
{
    EntityVec m_entities;
    EntityVec m_toAdd;
    EntityMap m_entityMap;
    // Number of entities ever added
    size_t m_totalEntities = 0;

public:
    EntityManager();
    std::shared_ptr<Entity> addEntity (const std::string& tag);
    EntityVec& getEntities();
    EntityVec& getEntities(const std::string& tag);
    void update();
};

