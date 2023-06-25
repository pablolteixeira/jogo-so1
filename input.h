#ifndef input_h
#define input_h

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <queue>
#include "thread/list.h"

class Input {
public:
	Input();
	~Input();
    void pushEvent(const sf::Event::KeyEvent& event);
    bool tryPopKey(sf::Keyboard::Key& key);
	std::queue<sf::Keyboard::Key> key_event_queue;

private:
};

#endif
