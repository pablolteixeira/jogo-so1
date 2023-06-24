#ifndef window_h
#define window_h

#include <iostream>
#include <png.h>
#include <SFML/Graphics.hpp>
#include "game.h"

class Window
{
public:
    Window(Game& game): game(game) {
        load_and_bind_textures();
    }

    void run();

    void draw_texture(unsigned int texture, int length, int height, float angle);

	//static std::tuple<sf::Texture, sf::Sprite> getShipAssets() {
	//	return std::make_tuple(space_ship_tex, space_ship_sprite);
	//}

	//static std::tuple<sf::Texture, sf::Sprite> getEnemyShipAssets() {
	//	return std::make_tuple(enemy_ship_tex, enemy_ship_sprite);
	//}

	//static std::tuple<sf::Texture, sf::Sprite> getShotAssets() {
	//	return std::make_tuple(shot_tex, shot_sprite);
	//}

private:
    void load_and_bind_textures();


private:
	Game& game;

    // Maze Texture
    static sf::Texture maze_tex;
    static sf::Sprite maze_sprite;
    
    //Shot texture
    static sf::Texture shot_tex;
    static sf::Sprite shot_sprite;
    
    //Space ship texture
    static sf::Texture space_ship_tex;
    static sf::Sprite space_ship_sprite;

    //Enemy space ship texture
    static sf::Texture enemy_ship_tex;
    static sf::Sprite enemy_ship_sprite;
};

#endif
