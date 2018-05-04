#ifndef PLAYER_H
#define PLAYER_H

#include "hopgame.h"
#include "gameobject.h"
#include <cmath>

class hopgame::player : public hopgame::gameobject {
	private:
		sf::RectangleShape player_shape;
		bool jumpStarted = false;
		int ticksSinceJumpStart = 0;
	public:
		player(sf::Color pc) {
			setPos(PLAYER_X_POS, GROUND_Y_POS-PLAYER_HEIGHT);
			setSize(PLAYER_WIDTH, PLAYER_HEIGHT);
			setVel(0, 0);
			setColor(pc);
			player_shape = sf::RectangleShape(getSize());
			player_shape.setFillColor(pc);
		};
		float jumpFormula(int ticks) {
			return GROUND_Y_POS-PLAYER_HEIGHT-(-1.0/5.7 * pow((float)ticks-20.0f, 2.0f) + MAX_JUMP_HEIGHT);
		};
		void tick() {
			if (isPlaying) {
				if (KEY_JUMP && !jumpStarted) {
					jumpStarted = true;
				}

				// do a jump
				if (jumpStarted) {
					ticksSinceJumpStart++;
					setPos(PLAYER_X_POS, jumpFormula(ticksSinceJumpStart));
					
					if (getPos().y >= GROUND_Y_POS - PLAYER_HEIGHT) {
						jumpStarted = false;
						ticksSinceJumpStart = 0;
					}
				}
			} else {
				setVel(0, 0);
			}
		};
		void draw(sf::RenderWindow& window) {
			player_shape.setPosition(getPos());
			window.draw(player_shape);
		};
};

#endif
