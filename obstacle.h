#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "hopgame.h"
#include "gameobject.h"

class hopgame::obstacle : public hopgame::gameobject {
	private:
		sf::RectangleShape obShape;
		bool pastPlayer = false;
	public:
		obstacle(sf::Vector2f size, sf::Color borderColor, bool flying = false) {
			setSize(size.x, size.y);
			setVel(obstacleSpeed, 0.0f);
			obShape = sf::RectangleShape(size);
			obShape.setOutlineColor(borderColor);
			obShape.setOutlineThickness(1.0f);
			obShape.setFillColor(sf::Color::White);
			setPos(WIDTH, GROUND_Y_POS - size.y);
			if (flying)
				setPos(getPos().x, getPos().y - FLYING_OBSTACLE_ELEVATION);
		};
		void tick() {
			if (gamestate != PLAYING) return;

			setPos(getPos().x - getVel().x, getPos().y);

			// if the object is past the player, increment the score (rather than the old way of incrementing whenever an object went off the screen)
			if (!pastPlayer && getPos().x + getSize().x < PLAYER_X_POS) {
				pastPlayer = true;
				score++;
				scoreText.setString("Score: " + std::to_string(score));
			}

			if (getPos().x + getSize().x <= 0.0)
				setGarbage(true);
		};
		void draw(sf::RenderWindow& window) {
			obShape.setPosition(getPos());
			window.draw(obShape);
		};
};

#endif
