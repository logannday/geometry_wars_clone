#include <memory>
#include <string>
#include "Components.h"

class Entity
{
    friend class EntityManager;
    
    bool        m_active   = true;
    size_t      m_id       = 0;
    std::string m_tag      = "default";

public:
    Entity(const size_t id, const std::string& tag);
    // conponent pointers
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> Shape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> Score;
    std::shared_ptr<CLifespan> cLifespan;

    // private member access functions bool isActive() const;
    bool isactive() const;
    const std::string & tag() const;
    const size_t id() const;
    void destroy ();
};
