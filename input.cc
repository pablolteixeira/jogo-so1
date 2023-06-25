#include "input.h"
#include <map>

Input::Input() {};
Input::~Input() {};

void Input::pushEvent(const sf::Event::KeyEvent& event) {
    if (event.code == sf::Keyboard::Up || event.code == sf::Keyboard::Down ||
        event.code == sf::Keyboard::Left || event.code == sf::Keyboard::Right ||
        event.code == sf::Keyboard::P || event.code == sf::Keyboard::Q ||
        event.code == sf::Keyboard::R || event.code == sf::Keyboard::Space) {
		printf("should've pushed to key event queue\n");
        key_event_queue.push(event.code);
    }
}

std::map<sf::Keyboard::Key, std::string> keyMapplayer2 = {
	{sf::Keyboard::Unknown, "Unknown"},
    {sf::Keyboard::A, "A"},
    {sf::Keyboard::B, "B"},
    {sf::Keyboard::Up, "Up"},
    {sf::Keyboard::Down, "Down"},
    {sf::Keyboard::Left, "Left"},
    {sf::Keyboard::Right, "Right"},
    {sf::Keyboard::Space, "Space"},
    {sf::Keyboard::P, "P"},
    {sf::Keyboard::Q, "Q"},
    {sf::Keyboard::R, "R"},
    //...
};

bool Input::tryPopKey(sf::Keyboard::Key& key) {
	printf("\n\nis input empty? %d\n", key_event_queue.empty());

    if (!key_event_queue.empty()) {
        key = key_event_queue.front();
        key_event_queue.pop();
		if (keyMapplayer2.find(key) != keyMapplayer2.end()) {
			printf("Key name: %s\n", keyMapplayer2[key].c_str());
		} else {
			printf("Key name: Unknown\n");
		}
        return true;
    }
    return false;
}
