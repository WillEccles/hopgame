#include "hopgame.h"
#include "gameobject.h"
#include "player.h"
#include "obstacle.h"

const static float TICK_TIME = 0.0166666667f;

void draw(sf::RenderWindow& window) {
	window.clear(sf::Color::White);

	window.draw(ground);

	for (auto& obj : game_objects)
		obj->draw(window);

	window.display();
}

bool tick(sf::Time elapsed) {
	if (elapsed.asSeconds() < TICK_TIME) return false;

	if (ticksTillObstacle == 0) {
		hopgame::gameobject* ob = new hopgame::obstacle(smallObstacleSize, sf::Color::Black);
		addGameObject(ob);
		ticksTillObstacle = 60;
	} else {
		ticksTillObstacle--;
	}

	if (obstacleSpeed < MAX_SPEED) {
		obstacleSpeed *= ACCELERATION;
	}

	for (auto it = game_objects.begin(); it != game_objects.end(); ) {
		if ((*it)->garbage()) {
			delete (*it);
			it = game_objects.erase(it);
		} else {
			(*it)->tick();
			it++;
		}
	}

	return true;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hop Game");
	_player = new hopgame::player(sf::Color::Black);
	addGameObject(_player);
	ground.setFillColor(sf::Color::Black);
	ground.setPosition(0.0f, GROUND_Y_POS);

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time elapsed = clock.getElapsedTime();
		if (tick(elapsed)) {
			// draw in here, since this makes sure it only draws at 60fps
			draw(window);
			clock.restart();
		}
	}

	return 0;
}
