Geometry Wars Clone from Scratch
--------------------------------
### Languages
- C++

### Libraries
- Sfml


### Notes
- For educational and recreational purposes
- Inspiration drawn from lecture series from [Dave Churchill's COMP4300 class](https://www.youtube.com/watch?v=S7lXSihz0ac&list=PL_xRyXins848nDj2v-TJYahzvsXW9sVV)
- This game is in progress! I'm still ironing out some bugs
#### Todo:
[x] Finish entity manager 
[x] Implement Spawn Bullet
[x] Implement Spawn Enemy
[x] Implement Collisions
[x] Wasd movement
[x] Fix getEntities
    - Idea: Maybe this has to do with reference lifetimes
    - Works in the main test, but not in the actual program
    - Size of getEntities("bullet") is 0, but there does appear to be
      a bullet key in the map  
    - Look at later videos to figure out what he did
[x] Bullet Lifetimes
[x] Bullet Fading
[x] Make it impossible for player entities to leave the window

