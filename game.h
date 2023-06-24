#ifndef game_h
#define game_h

#include <SFML/System/Clock.hpp>
#include <vector>
#include "game_objects/collision_handler.h"
#include "game_objects/enemy_spaceship.h"
#include "game_objects/player_spaceship.h"
#include "game_objects/shot.h"
#include "game_objects/spaceship.h"
#include "screen/score_panel.h"

class Game {
public:
	Game();
    void run();
	static std::vector<GameObject*> getGameObjects() { return game_objects; };
    static bool checkCollision(GameObject& obj1, GameObject& obj2);
	static bool isRunning() { return is_running; } ;
	static PlayerSpaceship *player_ship;
	static void end() { printf("JOGO ACABOU\n"); } 
    void update(float dt);
    void draw();
	sf::Clock *clock;

private:
    void handleEvents();

    sf::RenderWindow window;
	CollisionHandler *collision_handler;
    std::vector<EnemySpaceship*> enemy_ships;
    std::vector<Shot*> shots;
    ScorePanel *score_panel;
	static std::vector<GameObject*> game_objects;
	static bool is_running;
};

#endif

