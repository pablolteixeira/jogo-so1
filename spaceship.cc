
#include "spaceship.h"
#include <SFML/Graphics.hpp>
#include "shot.h"

void Spaceship::fire() {
	Shot shot = Shot(position_x + width/2, position_y);
	
}
