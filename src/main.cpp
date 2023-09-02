#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cassert>
#include "Game.h"
#include "Vec2.h"
#include "Components.h"
#include "EntityManager.h"
#include "Entity.h"

void testVec();
void testComponents();
void testManager();
void testGame();

int main(int argc, char * argv[])
{
    //testVec();
    //testComponents();
    //testManager();
    //testGame();

    Game myGame("todo: Config");
    myGame.run();
    return 0;
}

void testVec()
{
    Vec2 v1(1,1);
    Vec2 v2(1,1);
    Vec2 v3(2,2);
    Vec2 v4(2,1);
    
    assert(v1 == v2);         // Test Equals
    assert(!(v1 == v3)); 
    assert(v1 != v4);         // Test Not Equals
    assert(!(v1 != v2)); 
    assert((v1 + v2) == v3);  // Test add
    assert((v3 - v1) == v2);  // Test Subtract
    assert((v1 * 2) == v3);   // Test Scalar Multiplication
    assert(sqrt(2) - v1.length() <= 0.01);
    // Maybe test normalize here??
}

void testComponents()
{
    Vec2 v1(1,1);
    Vec2 v2(2,2);
    CTransform trans(v1, v2, 3.14f);
     std::cout << trans.pos.x << " " << trans.velocity.y << "\n";
    CCollision col(1.1);
    // std::cout << "radius: " << col.radius << "\n";
}

void testManager()
{
    EntityManager em;
    em.addEntity("Boss");
    em.addEntity("Peen");
    em.addEntity("Penus");
    em.addEntity("Swag");
    em.update();
    em.print();
    std::cout << "\n";
    auto entities = em.getEntities();
    for (auto& e : entities)
    {
        e->destroy();
    }
    em.update();
    em.print();
    std::cout << "\n";
}

void testGame()
{
    Entity entity(420, "Logan");
    // entity.cInput->left;
}
