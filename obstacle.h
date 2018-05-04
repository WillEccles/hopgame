#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "hopgame.h"
#include "gameobject.h"

class hopgame::obstacle : public hopgame::gameobject {
	private:
		sf::RectangleShape obShape;
	public:
		obstacle(sf::Vector2f size, sf::Color borderColor) {
			setSize(size.x, size.y);
			setVel(obstacleSpeed, 0.0f);
			obShape = sf::RectangleShape(size);
			obShape.setOutlineColor(borderColor);
			obShape.setOutlineThickness(1.0f);
			obShape.setFillColor(sf::Color::White);
			setPos(WIDTH, GROUND_Y_POS - size.y);
		};
		void setRed() {
			obShape.setFillColor(sf::Color::Red);
		};
		void tick() {
			setPos(getPos().x - obstacleSpeed, getPos().y);

			if (getPos().x + OBSTACLE_WIDTH <= 0.0)
				setGarbage(true);
		};
		void draw(sf::RenderWindow& window) {
			obShape.setPosition(getPos());
			window.draw(obShape);
		};
};

#endif
