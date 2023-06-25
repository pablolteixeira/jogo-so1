#include "input.h"
#include <map>

Input::Input() {};
Input::~Input() {};

void Input::pushEvent(const sf::Event::KeyEvent& event) {
    if (event.code == sf::Keyboard::Up || event.code == sf::Keyboard::Down ||
        event.code == sf::Keyboard::Left || event.code == sf::Keyboard::Right ||
        event.code == sf::Keyboard::P || event.code == sf::Keyboard::Q ||
        event.code == sf::Keyboard::R || event.code == sf::Keyboard::Space) 
    {
        key_event_queue.push(event.code);
    }
}

bool Input::tryPopKey(sf::Keyboard::Key& key) {
    if (!key_event_queue.empty()) {
        key = key_event_queue.front();
        key_event_queue.pop();
        return true;
    }
    return false;
}
