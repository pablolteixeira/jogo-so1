#ifndef game_object_h
#define game_object_h

#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject();
    void draw(sf::RenderWindow &window);
    void update(float dt);
	sf::Sprite getSprite() { return sprite; };
	virtual void die() { isAlive = false; };
	bool isAlive = true;

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;
    void loadTexture(std::string filename);
};

#endif
