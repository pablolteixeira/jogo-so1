#include "game.h"
#include "thread/traits.h"
#include <SFML/System/Time.hpp>
#include "thread/system.h"

__USING_API

int main() {
	System::init(&Game::run);
	return 0;
}
