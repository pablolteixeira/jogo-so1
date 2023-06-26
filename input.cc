#include "input.h"
#include "thread/traits.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <map>
#include "thread/thread.h"

__BEGIN_API

Semaphore* Input::key_event_queue_mutex = nullptr;
	
Input::~Input() {
	delete key_event_queue_mutex;
};


void Input::runInput() {
	// FIXME: while(true) should be while(game is running)
	while (true) {
		handleEvents();	
		Thread::yield();
	}
}

// TODO: processamento de evemntos de tecla no Window.h
void Input::handleEvents() {
	sf::Event ev;

	while (window.pollEvent(ev)) {
		std::cout << "\n\n\n\n\n\nWINDOW POLL!\n\n\n" << std::flush;
		switch (ev.type) {
			case sf::Event::Closed:
				// FIXME: handle this better. End game;
				window.close();
				break;
			case sf::Event::KeyPressed:
				pushEvent(ev.key);
				break;
			default:
				break;
		}
	}
}

void Input::pushEvent(const sf::Event::KeyEvent& event) {
    if (event.code == sf::Keyboard::Up || event.code == sf::Keyboard::Down ||
        event.code == sf::Keyboard::Left || event.code == sf::Keyboard::Right ||
        event.code == sf::Keyboard::P || event.code == sf::Keyboard::Q ||
        event.code == sf::Keyboard::R || event.code == sf::Keyboard::Space) 
    {
		key_event_queue_mutex->p();
        key_event_queue.push(event.code);
		key_event_queue_mutex->v();
    }
}

bool Input::tryPopKey(sf::Keyboard::Key& key) {
	std::cout << "try pop key\n" << std::flush;
	key_event_queue_mutex->p();
	std::cout << "semaphore issue?\n" << std::flush;
    if (!key_event_queue.empty()) {
		std::cout << "key not empty\n" << std::flush;
        key = key_event_queue.front();
        key_event_queue.pop();
		key_event_queue_mutex->v();
        return true;
    }
	std::cout << "key ISSSSSS empty\n" << std::flush;
	
	key_event_queue_mutex->v();
    return false;
}

__END_API
