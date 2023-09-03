Naive Game Engine
-----------------
- for educational and recreational purposes
- based on lecture series from Dave Churchill
- Can only display one scene
Todo:
[x] Finish entity manager 
[x] Implement Spawn Bullet
[x] Implement Spawn Enemy
[ ] Fix getEntities
[ ] Bullet Lifetimes
[ ] Make it impossible for player entities to leave the window
[ ] Implement Collisions

Notes:
- Set origin of the circle to the middleo

    setOrigin(radius, radius)

- Use DrawCircle to draw various types of shapes by expressing
  number of sides
- Set point count sets num sides
sf::Circleshape triangle(59.f, numsides);

- Generating shapes: x = random(0 + radius, W- radius)


