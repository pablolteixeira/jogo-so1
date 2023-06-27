#include "input.h"
#include "thread/traits.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <map>
#include "thread/thread.h"
#include "window.h"

__BEGIN_API

Semaphore* Input::key_event_queue_mutex = nullptr;
	
Input::~Input() {
	delete key_event_queue_mutex;
};


void Input::runInput() {
	while (mainWindow->getIsRunning()) {
		handleEvents();	
		Thread::yield();
	}
}

// TODO: processamento de evemntos de tecla no Window.h
void Input::handleEvents() {
	sf::Event ev;

	while (window.pollEvent(ev)) {
		switch (ev.type) {
			case sf::Event::Closed:
				window.close();
				mainWindow->stopRunning();
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
	key_event_queue_mutex->p();
    if (!key_event_queue.empty()) {
        key = key_event_queue.front();
        key_event_queue.pop();
		key_event_queue_mutex->v();
        return true;
    }
	key_event_queue_mutex->v();
    return false;
}

__END_API
