#include "game.h"
#include "thread/traits.h"
#include <SFML/System/Time.hpp>
#include "thread/system.h"

__USING_API

int main() {
	System::init(&Game::run);
	std::cout << "after init\n" << std::flush;
	return 0;
}
