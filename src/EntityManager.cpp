#include "EntityManager.h"

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
}
