#ifndef game_h
#define game_h

#include <vector>
#include "enemy_spaceship.h"
#include "game_object.h"
#include "shot.h"
#include "spaceship.h"
#include "score_panel.h"

class Game {
public:
	Game();
    void run();
	static std::vector<GameObject>& getGameObjects() { return game_objects; };
    static bool checkCollision(GameObject& obj1, GameObject& obj2);
	static bool isRunning() { return is_running; } ;

private:
    void handleEvents();
    void update(float dt);
    void draw();

    sf::RenderWindow window;
    Spaceship player_ship;
    std::vector<EnemySpaceship> enemy_ships;
    std::vector<Shot> shots;
    ScorePanel score_panel;
	static std::vector<GameObject> game_objects;
	static bool is_running;
};

#endif

