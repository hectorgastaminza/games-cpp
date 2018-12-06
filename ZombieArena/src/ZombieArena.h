#ifndef SRC_ZOMBIE_ARENA_H_
#define SRC_ZOMBIE_ARENA_H_

#include "Zombie.h"

using namespace sf;

int createBackground(VertexArray& rVA, IntRect arena);
Zombie* createHorde(int numZombies, IntRect arena);

#endif
