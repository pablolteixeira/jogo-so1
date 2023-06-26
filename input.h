#ifndef input_h
#define input_h

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <queue>
#include "thread/list.h"
#include "thread/traits.h"
#include "thread/semaphore.h"

__BEGIN_API

class Input {
public:
	Input(sf::RenderWindow& window) : window(window) {
		key_event_queue_mutex = new Semaphore();
	};
	~Input();

	void runInput();
    void pushEvent(const sf::Event::KeyEvent& event);
    bool tryPopKey(sf::Keyboard::Key& key);
	void handleEvents();

	std::queue<sf::Keyboard::Key> key_event_queue;

private:
	static Semaphore *key_event_queue_mutex;
	sf::RenderWindow& window;
};

__END_API

#endif
