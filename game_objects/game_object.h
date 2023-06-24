#ifndef game_object_h
#define game_object_h

#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject();
    void draw(sf::RenderWindow &window);
    void update(float dt);
	virtual void die() { isAlive = false; };
	bool isAlive = true;
    sf::Sprite sprite;

protected:
    sf::Texture texture;
    sf::Vector2f position;
    void loadTexture(std::string filename);
};

#endif
