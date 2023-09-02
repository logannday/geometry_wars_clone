#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager() {};

std::shared_ptr<Entity> EntityManager::addEntity (const std::string& tag)
{
    auto e = std::make_shared<Entity>(m_totalEntities++, tag);
    m_toAdd.push_back(e);
    m_entityMap[tag].push_back(e);
    return e;
}

void EntityManager::update()
{
    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        // Remember, e is a shared pointer to an entity
        // Functions can be accessed with arrow operator
        m_entityMap[e->tag()].push_back(e);
    }
    
    removeDeadEntities(m_entities);

    // TODO: test this
    for (auto& [tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }

    m_toAdd.clear();
}

void EntityManager::print()
{
    for (auto& e : m_entities)
    {
        std::cout << e->m_tag << " ";
    } 
}

void EntityManager::removeDeadEntities(EntityVec & vec)
{
    auto newEnd = std::remove_if(vec.begin(), vec.end(),
           [](std::shared_ptr<Entity> e) { return !(e->isActive()); }
           );
    vec.erase(newEnd, vec.end());
}

EntityVec& EntityManager::getEntities()
{
    return m_entities;
}

EntityVec& EntityManager::getEntities(const std::string& tag)
{
    for (auto& [key, entityVec] : m_entityMap)
    {
        if(key.compare(tag) == 0)
        {
            return entityVec;
        }
    }
    std::cerr << "Entity NOT FOUND BOI during getEntities(" << tag;
    exit(1);
}
