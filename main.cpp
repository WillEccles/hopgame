#include "hopgame.h"
#include "gameobject.h"
#include "player.h"
#include "obstacle.h"

const static float TICK_TIME = 0.0166666667f;

void draw(sf::RenderWindow& window) {
	window.clear(sf::Color::White);

	window.draw(ground);
	window.draw(scoreText);
	
	_player->draw(window);

	for (auto& ob : obstacles)
		ob->draw(window);

	window.display();
}

bool tick(sf::Time elapsed) {
	if (elapsed.asSeconds() < TICK_TIME) return false;

	if (ticksTillObstacle == 0) {
		hopgame::obstacle* ob = new hopgame::obstacle(smallObstacleSize, sf::Color::Black);
		addObstacle(ob);
		ticksTillObstacle = 60;
	} else {
		ticksTillObstacle--;
	}

	if (obstacleSpeed < MAX_SPEED) {
		obstacleSpeed *= ACCELERATION;
	}

	// always tick the player before doing the other game objects
	_player->tick();

	for (auto it = obstacles.begin(); it != obstacles.end(); ) {
		if ((*it)->garbage()) {
			delete (*it);
			it = obstacles.erase(it);
			score++;
			scoreText.setString(std::to_string(score));
		} else {
			(*it)->tick();
			if ((*it)->collidesWith(_player)) {
				// this means the player has died
				// for now just make it do a debug thing
				(*it)->setRed();
			}
			it++;
		}
	}

	return true;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hop Game");
	_player = new hopgame::player(sf::Color::Black);
	ground.setFillColor(sf::Color::Black);
	ground.setPosition(0.0f, GROUND_Y_POS);

	if (!scoreFont.loadFromFile("OperatorMono-Medium.otf")) {
		return 69;
	}

	scoreText.setPosition(10.0f, 1.0f);
	scoreText.setFont(scoreFont);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setString(std::to_string(score));

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
