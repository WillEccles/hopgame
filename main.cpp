#include "hopgame.h"
#include "gameobject.h"
#include "player.h"
#include "obstacle.h"

const static float TICK_TIME = 0.0166666667f;

void draw(sf::RenderWindow& window) {
	window.clear(sf::Color::White);

	if (gamestate == PLAYING) {
		window.draw(ground);
		window.draw(scoreText);
		
		_player->draw(window);

		for (auto& ob : obstacles)
			ob->draw(window);
	} else if (gamestate == PAUSED) {
	} else if (gamestate == OVER) {
		window.draw(gameOverText);
		window.draw(gameOverSubtitle);
	}

	window.display();
}

void gameOver() {
	gamestate = OVER;
	gameOverSubtitle.setString("Score: " + std::to_string(score));
	centerText(gameOverSubtitle);
	centerTextVertical(gameOverSubtitle, gameOverText.getLocalBounds().height+7.0f);
}

bool tick(sf::Time elapsed) {
	if (elapsed.asSeconds() < TICK_TIME) return false;

	if (KEY_RESTART) {
		// restart the game
		score = 0;
		obstacleSpeed = SPEED;
		ticks = 0;
		obstacles.clear();
		delete _player;
		_player = new hopgame::player(sf::Color::Black);
		scoreText.setString("Score: 0");
		gamestate = PLAYING;
	}

	if (ticks == 60) {
		hopgame::obstacle* ob = new hopgame::obstacle(smallObstacleSize, sf::Color::Black);
		addObstacle(ob);
	} else if (ticks == 120) {
		// add a flying obstacle
		hopgame::obstacle* ob = new hopgame::obstacle(flyingObstacleSize, sf::Color::Black, true);
		addObstacle(ob);
		ticks = 0;
	}

	ticks++;

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
			scoreText.setString("Score: " + std::to_string(score));
		} else {
			(*it)->tick();
			if ((*it)->collidesWith(_player)) {
				gameOver();
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

	if (!scoreFont.loadFromFile(FONT)) {
		return 69;
	}

	scoreText.setPosition(10.0f, 1.0f);
	scoreText.setFont(scoreFont);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setString("Score: " + std::to_string(score));

	gameOverText.setFont(scoreFont);
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over!");
	centerText(gameOverText);
	
	gameOverSubtitle.setFont(scoreFont);
	gameOverSubtitle.setCharacterSize(30);
	gameOverSubtitle.setFillColor(sf::Color::Black);

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
