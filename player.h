#ifndef PLAYER_H
#define PLAYER_H

#include "hopgame.h"
#include "gameobject.h"

class hopgame::player : public hopgame::gameobject {
	private:
		sf::RectangleShape player_shape;
		bool jumpStarted = false;
		bool hitMaxHeight = false;
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
		void tick() {
			if (isPlaying) {
				if (KEY_JUMP && !jumpStarted) {
					jumpStarted = true;
				}

				// do a jump
				if (jumpStarted) {
					float coefficient = 1.0f - 0.03f * (float)ticksSinceJumpStart;
					if (coefficient <= 0.1f)
						coefficient = 0.1f;

					ticksSinceJumpStart++;
					if (!hitMaxHeight) {
						// make the little guy go higher
						setPos(PLAYER_X_POS, getPos().y + INITIAL_JUMP_VELOCITY * coefficient);

						// after doing any jumping stuff, see if he has hit max height
						if (getPos().y + PLAYER_HEIGHT <= GROUND_Y_POS - MAX_JUMP_HEIGHT) {
							hitMaxHeight = true;
							ticksSinceJumpStart = 0;
						}
					} else {
						// it's time to make the little man go down
						setPos(PLAYER_X_POS, getPos().y - INITIAL_JUMP_VELOCITY * coefficient);

						// see if he has hit the ground now
						if (getPos().y + PLAYER_HEIGHT >= GROUND_Y_POS) {
							setPos(PLAYER_X_POS, GROUND_Y_POS - PLAYER_HEIGHT);
							jumpStarted = false;
							hitMaxHeight = false;
							ticksSinceJumpStart = 0;
						}
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
